#include "Raw.h"

Raw::Raw(QWidget* parent) : QWidget(parent) {
	ui.setupUi(this);
}

QTreeView* Raw::getView() {
	return ui.treeView;
}

void Raw::setView(QTreeView* view) {
	ui.treeView = view;
}