#pragma once
#include <variant>
#include <vector>
#include <string>
#include <QVariant>

using Data = QVariant
;


class Node {
public:
	explicit Node(const std::vector<Data>& data, Node* parent = nullptr);
	~Node();

	void appendChild(Node* child);
	Node* child(unsigned int row);
	Node* parentItem();
	Data data(unsigned int column) const;
	unsigned int childCount() const;
	unsigned int columnCount() const;
	unsigned int row() const;
private:
	std::vector<Node*> children;
	std::vector<Data> itemData;
	Node* parent;
};