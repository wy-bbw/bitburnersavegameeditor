#include <core/json/JsonParser.h>
#include <iostream>
#include <stack>
#include <cassert>
#include <list>

enum class State {
	START, OBJ, KEY1, KEY, KEY_END, VAL_BEGIN, VALUE, END, ERROR, KEY_STR, KEY_STR_ESC
};

constexpr char ESCAPE = '\\';
constexpr char QUOTATION = '"';
constexpr char OPEN_BRACE = '{';
constexpr char CLOSE_BRACE = '}';
constexpr char DOUBLE_COLON = ':';

std::pair<State, Node*> handleStart(std::list<char>& buf, std::stack<Node*> stack, char c, Node* currentNode) {
	if (c == OPEN_BRACE) {
		Node* newNode = new Node({ c });
		stack.push(currentNode);
        buf.push_back(c);
        return {State::OBJ, newNode};
	}
	else {
		std::string errorString = "unexpected char '";
		errorString.push_back(c);
		errorString += "'";
		throw std::runtime_error(errorString);
	}
};

// TODO: check this
std::pair<State, Node*> handleObj(std::list<char>& buf, std::stack<Node*> stack, char c, Node* currentNode) {
	Node* nodeToReturn = currentNode;
	State state = State::OBJ;
	if (c == ESCAPE) {
		buf.clear();
		buf.push_back(c);
		state = State::KEY1;
	}
	else if (c == QUOTATION) {
		buf.clear();
		buf.push_back(c);
		state = State::KEY_STR;

	}
	else if (c == CLOSE_BRACE) {
		if (stack.empty()) {
			state = State::END;
		}
		else {
			state = State::OBJ;
			nodeToReturn = stack.top();
			stack.pop();
		}
	} else {
		throw std::runtime_error("invalid char from obj.");
	}
	return std::pair(state, nodeToReturn);
}

std::pair<State, Node*> handleKey1(std::list<char>& buf, std::stack<Node*> stack, char c, Node* currentNode) {
	if (c == QUOTATION) {
		buf.push_back(c);
        return {State::KEY, currentNode};
	} else {
		throw std::runtime_error("unexpected char from Key1");
	}
}

std::pair<State, Node*> handleKey(std::list<char>& buf, std::stack<Node*> stack, char c, Node* currentNode) {
	buf.push_back(c);
	if (c == ESCAPE) {
        return {State::KEY_END, currentNode};
	} else {
        return {State::KEY, currentNode};
    }
}

std::pair<State, Node*> handleKeyEnd(std::list<char>& buf, std::stack<Node*> stack, char c, Node* currentNode) {
	if (c == QUOTATION) {
		buf.push_back(c);
        return {State::VAL_BEGIN, currentNode};
	}
	else {
		throw std::runtime_error("handleKeyEnd failed");
	}
}

std::pair<State, Node*> handleValBegin(std::list<char>& buf, std::stack<Node*> stack, char c, Node* currentNode) {
	if (c == DOUBLE_COLON) {
		buf.push_back(c);
        return std::pair(State::VALUE, currentNode);
	}
	else {
		throw std::runtime_error("unexpected token in ValBegin");
	}
}

std::pair<State, Node *> handleKeyStr(std::list<char>& buf, std::stack<Node*> stack, char c, Node* currentNode) {
    Node* nodeToReturn = currentNode;
    State state = State::KEY_STR;
    buf.push_back(c);
    if (c == ESCAPE) {
        state = State::KEY_STR_ESC;
    } else if (c == QUOTATION) {
        state = State::VAL_BEGIN;
    }
    return std::pair(state, nodeToReturn);
}


//std::pair<State, Node*>

// TODO: this needs proper unit testing! Trust me, it does!
std::unique_ptr<Node> json::parseData(std::vector<std::byte> data) {
	std::stack<Node*> stack;
	Node* currentNode = nullptr;
	State state = State::START;
	std::list<char> buf;
	for (auto it = data.begin(); it != data.end(); ++it ) {
		std::byte b = *it;
		char c = static_cast<char>(b);
		try {
			if (state == State::START) {
				std::tie(state, currentNode) = handleStart(buf, stack, c, currentNode);
			} else if (state == State::OBJ) {
				std::tie(state, currentNode) = handleObj(buf, stack, c, currentNode);
			} else if (state == State::KEY1) {
				std::tie(state, currentNode) = handleKey1(buf, stack, c, currentNode);
			} else if (state == State::KEY) {
				std::tie(state, currentNode) = handleKey(buf, stack, c, currentNode);
			} else if (state == State::KEY_END) {
				std::tie(state, currentNode) = handleKeyEnd(buf, stack, c, currentNode);
			} else if (state  == State::KEY_STR) {
                std::tie(state, currentNode) = handleKeyStr(buf, stack, c, currentNode);
            } else if (state == State::KEY_STR_ESC) {
                buf.push_back(c);
                state = State::KEY_STR;
            }  else if (state == State::VAL_BEGIN) {
                std::tie(state, currentNode) = handleValBegin(buf, stack, c, currentNode);
            }
            else {
                throw std::runtime_error("not implemented");
            }
		}
		catch (std::exception& e) {
			int distanceFromBegin = std::distance(data.begin(), it);
			int lowerBorder = distanceFromBegin <= 10 ? distanceFromBegin : 10;
			auto beginErrorParsing = it - lowerBorder;

			int distanceFromEnd = std::distance(it, data.end());
			int upperBorder = distanceFromEnd <= 10 ? distanceFromEnd : 10;
			auto successors = it + upperBorder;
			std::string before, after;
			for (auto ite = beginErrorParsing; ite != it; ++ite) {
				before.push_back(static_cast<char>(*ite));
			}
			for (auto ite = it + 1; ite != successors; ++ite) {
				after.push_back(static_cast<char>(*ite));
			}
			std::cerr << e.what() << std::endl;
			std::cerr << "before: " << before << std::endl;
			std::cerr << "invalid token: '" << static_cast<char>(*it) << "'" << std::endl;
			std::cerr << "after: " << after << std::endl;
			throw std::runtime_error("propagate");
		}
	}

	printPartialTree(std::cout, currentNode, 1);
	//assert(stack.empty());
	//assert(state == State::END);
	//assert(currentNode != nullptr);
	return std::unique_ptr<Node>(currentNode);
}