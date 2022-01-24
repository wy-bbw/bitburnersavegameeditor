#pragma once
#include <variant>
#include <vector>
#include <string>
#include <QVariant>

using Data = QVariant;
class Node;
void printPartialTree(std::ostream& os, Node* node, int indentationlevel = 0);


class Node {
	friend void printPartialTree(std::ostream& os, Node* node, int indentationlevel);
public:
	explicit Node(const std::vector<QVariant>& name, Node* parent = nullptr);
	~Node();

	void appendChild(Node* child);
	Node* child(unsigned int row);
	Node* parentItem();
	Data data(unsigned int column) const;
	void pushData(Data data);
	unsigned int childCount() const;
	unsigned int columnCount() const;
	unsigned int row() const;
private:
	std::vector<Node*> children;
	std::vector<QVariant> itemData;
	Node* parent;
};
