#include <gui/TreeModel.h>

TreeModel::TreeModel(QObject* parent) : QAbstractItemModel(parent) {
	rootNode = nullptr;
}

void TreeModel::setRoot(std::unique_ptr<Node>&& root) {
	rootNode = std::move(root);
}

// TODO: check if internal pointer is valid!
QModelIndex TreeModel::index(int row, int column, const QModelIndex& parent) const {
	if (!hasIndex(row, column, parent)) {
		return QModelIndex();
	}

	Node* parentItem;
	if (!parent.isValid()) {
		parentItem = rootNode.get();
	}
	else {
		parentItem = static_cast<Node*>(parent.internalPointer());
	}
	Node* childNode = parentItem->child(row);
	if (childNode) {
		return createIndex(row, column, childNode);
	}
	return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex& index) const {
	if (!index.isValid()) {
		return QModelIndex();
	}
	Node* child = static_cast<Node*>(index.internalPointer());
	Node* parent = child->parentItem();
	if (parent == rootNode.get()) {
		return QModelIndex();
	}
	return createIndex(parent->row(), 0, parent);
}

int TreeModel::rowCount(const QModelIndex& parent) const {
	Node* parentItem;
	if (parent.column() > 0) {
		return 0;
	}
	
	if (!parent.isValid()) {
		parentItem = rootNode.get();
	}
	else {
		parentItem = static_cast<Node*>(parent.internalPointer());
	}
	return parentItem->childCount();
}

int TreeModel::columnCount(const QModelIndex& parent) const {
	if (parent.isValid()) {
		return static_cast<Node*>(parent.internalPointer())->columnCount();
	}
	return rootNode->columnCount();
}

QVariant TreeModel::data(const QModelIndex& index, int role) const {
	if (!index.isValid()) {
		return QVariant();
	}

	if (role == Qt::DisplayRole) {

	}

	if (role != Qt::DisplayPropertyRole && role != Qt::DisplayRole) {
		return QVariant();
	}

	Node* item = static_cast<Node*>(index.internalPointer());
	QVariant data = item->data(index.column());
	QString stringname = data.toString();
	return item->data(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex& index) const {
	if (!index.isValid()) {
		return Qt::NoItemFlags;
	}
	return QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
		return rootNode->data(section);
	}
	return QVariant();
}