#pragma once
#include <QAbstractItemModel>
#include <core/json/Node.h>

class TreeModel : public QAbstractItemModel {
	Q_OBJECT
public:
	explicit TreeModel(QObject* parent = nullptr);

	QVariant data(const QModelIndex& index, int role) const override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
	QModelIndex parent(const QModelIndex& index) const override;
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	void setRoot(std::unique_ptr<Node>&& root);
private:
	void setupModelData(const QStringList& lines, Node* parent);

	std::unique_ptr<Node> rootNode;
};