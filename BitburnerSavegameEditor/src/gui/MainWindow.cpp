#include "MainWindow.h"

#include <QFileDialog>
#include <QStyle>
#include <QStandardPaths>
#include <list>
#include <core/ContentRepository.h>

#include <core/Node.h>

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
	
	setupRawView();
	emit contentChanged();
}

void MainWindow::saveButtonPressed() {
	std::vector<std::byte> f{ std::byte{1}, std::byte{2}, std::byte{3} };
	savefileManager.store("foo");
}

void MainWindow::setupRawView() {
	Raw* raw = new Raw(this);

	Node* node = new Node();
	ui.tabWidget->clear();
	ui.tabWidget->addTab(raw, tr("raw"));
}