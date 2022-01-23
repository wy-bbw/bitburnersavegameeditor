#include <core/json/JsonParser.h>
#include <stack>
#include <cassert>
#include <list>

enum class State {
	START, OBJ, KEY1, KEY, KEY_END, VAL_BEGIN, VALUE, END, ERROR
};

constexpr char KEY_BEGIN = '\\';
constexpr char KEY_END = '"';
constexpr char OBJ_BEGIN = '{';
constexpr char OBJ_END = '}';
constexpr char VAL_SIGN = ':';

std::pair<State, Node*> handleStart(std::list<char>& buf, std::stack<Node*> stack, char c, Node* currentNode) {
	Node* nodeToReturn = currentNode;
	State state = State::START;
	if (c == OBJ_BEGIN) {
		Node* currentNode = new Node({ c });
		stack.push(currentNode);
		state = State::OBJ;
	}
	else {
		std::string errorString = "unexpected char '";
		errorString.push_back(c);
		errorString += "'";
		throw std::runtime_error(errorString);
	}
	return std::pair(state, nodeToReturn);
};

std::pair<State, Node*> handleObj(std::list<char>& buf, std::stack<Node*> stack, char c, Node* currentNode) {
	Node* nodeToReturn = currentNode;
	State state = State::OBJ;
	if (c == KEY_BEGIN) {
		buf.clear();
		buf.push_back(c);
		state = State::KEY1;
	}
	else if (c == OBJ_END) {
		if (stack.empty()) {
			state = State::END;
		}
		else {
			state = State::OBJ;
			nodeToReturn = stack.top();
			stack.pop();
		}
	}
	else {
		throw std::runtime_error("invalid char from obj.");
	}
	return std::pair(state, nodeToReturn);
}

std::pair<State, Node*> handleKey1(std::list<char>& buf, std::stack<Node*> stack, char c, Node* currentNode) {
	Node* nodeToReturn = currentNode;
	State state = State::KEY1;
	if (c == KEY_END) {
		buf.push_back(c);
		state = State::KEY;
	}
	else {
		throw std::runtime_error("unexpected char from Key1");
	}
	return std::pair(state, nodeToReturn);
}

std::pair<State, Node*> handleKey(std::list<char>& buf, std::stack<Node*> stack, char c, Node* currentNode) {
	Node* nodeToReturn = currentNode;
	State state = State::KEY;
	buf.push_back(c);
	if (c == KEY_BEGIN) {
		state = State::KEY_END;
	}
	return std::pair(state, nodeToReturn);
}

std::pair<State, Node*> handleKeyEnd(std::list<char>& buf, std::stack<Node*> stack, char c, Node* currentNode) {
	Node* nodeToReturn = currentNode;
	State state = State::KEY_END;
	if (c == KEY_END) {
		buf.push_back(c);
		state = State::VAL_BEGIN;
	}
	else {
		throw std::runtime_error("handleKeyEnd failed");
	}
	return std::pair(state, nodeToReturn);
}

std::pair<State, Node*> handleValBegin(std::list<char>& buf, std::stack<Node*> stack, char c, Node* currentNode) {
	Node* nodeToReturn = currentNode;
	State state = State::VAL_BEGIN;
	if (c == VAL_SIGN) {
		buf.push_back(c);
		state = State::VALUE;
	}
	else {
		throw std::runtime_error("unexpected token in ValBegin");
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
	for (std::byte b : data) {
		char c = static_cast<char>(b);
		if (state == State::START) {
			std::tie(state, currentNode) = handleStart(buf, stack, c, currentNode);
		} 
		else if (state == State::OBJ) {
			std::tie(state, currentNode) = handleObj(buf, stack, c, currentNode);
		}
		else if (state == State::KEY1) {
			std::tie(state, currentNode) = handleKey1(buf, stack, c, currentNode);
		}
		else if (state == State::KEY) {
			std::tie(state, currentNode) = handleKey(buf, stack, c, currentNode);
		}
		else if (state == State::KEY_END) {
			std::tie(state, currentNode) = handleKeyEnd(buf, stack, c, currentNode);
		}
	}
	assert(stack.empty());
	assert(state == State::END);
	assert(currentNode != nullptr);
	return std::unique_ptr<Node>(currentNode);
}