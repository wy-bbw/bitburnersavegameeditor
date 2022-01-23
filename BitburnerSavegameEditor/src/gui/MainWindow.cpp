#include "MainWindow.h"

#include <cassert>
#include <QFileDialog>
#include <QStyle>
#include <QStandardPaths>
#include <list>
#include <gui/TreeModel.h>

#include <core/json/Node.h>
#include <core/base64.h>
#include <core/json/JsonParser.h>

#include "Raw.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
	ui.setupUi(this);
	initializeButtons();
	ui.tabWidget->clear();
}

void MainWindow::initializeButtons() {
	ui.actionopen->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));
	connect(ui.actionopen, &QAction::triggered, this, &MainWindow::openButtonPressed);

	ui.actionsave->setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));
	connect(ui.actionsave, &QAction::triggered, this, &MainWindow::saveButtonPressed);
}

void MainWindow::openButtonPressed() {
	QString filename = QFileDialog::getOpenFileName(this);
	if (filename.isEmpty()) {
		return;
	}
	savefileManager.load(filename.toStdString());
	ui.tabWidget->clear();
	std::vector<std::byte> decoded;

	base64::decode(savefileManager.getData().begin(), savefileManager.getData().end(), std::back_inserter(decoded));

	setupRawView(decoded);
	emit contentChanged();
}

void MainWindow::saveButtonPressed() {
	std::vector<std::byte> f{ std::byte{1}, std::byte{2}, std::byte{3} };
	savefileManager.store("foo");
}

void MainWindow::setupRawView(const std::vector<std::byte>& fileData) {
	Raw* raw = new Raw(this);

	std::unique_ptr<Node> root = json::parseData(fileData);

	TreeModel* model = new TreeModel(this);
	model->setRoot(std::move(root));

	ui.tabWidget->clear();
	ui.tabWidget->addTab(raw, tr("raw"));

	QTreeView* view = raw->getView();
	view->setModel(model);
	view->show();
}