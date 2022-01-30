#include <iostream>
#include <core/json/Node.h>

Node::Node(const std::vector<QVariant>& data, Node* parent) : itemData(data), parent(parent) {
    if (parent != nullptr) {
        parent->appendChild((this));
    }
}

Node::~Node() {
	for (auto p : children) delete p;
}

void Node::appendChild(Node* node) {
	children.push_back(node);
}

Node* Node::child(unsigned int row) {
	if (row >= children.size()) {
		return nullptr;
	}
	return children[row];
}

unsigned int Node::childCount() const {
	return children.size();
}

unsigned int Node::row() const {
	if (parent) {
		const auto& parentChildren = parent->children;
		auto it = std::find(parentChildren.begin(), parentChildren.end(), this);
		return it - parentChildren.begin();
	}
	return 0;
}

unsigned int Node::columnCount() const {
	return 1;
}

Data Node::data(unsigned int column) const {
	if (column >= itemData.size()) {
		return Data();
	}
	return QVariant(itemData[column]);
}

Node* Node::parentItem() {
	return parent;
}

void Node::pushData(QVariant data) {
	itemData.push_back(data);
}

void Node::setPrimeData(Data data) {
    itemData[0] = data;
}

void printPartialTree(std::ostream& os, Node* node, int indentationlevel) {
	assert(node->itemData.size() > 0);
	std::fill_n(std::ostream_iterator<char>(os), ' ', indentationlevel);
	QString name = node->itemData.begin()->toString();
	os << name.toStdString() << std::endl;
	for (auto child : node->children) {
		printPartialTree(os, child, indentationlevel + 1);
	}
}

