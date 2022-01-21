#pragma once

//#include "ui.MainWindow.h"
#include <QMainWindow>
#include <core/SavefileManager.h>
#include "ui_mainWindow.h"

class MainWindow : public QMainWindow  {
	Q_OBJECT
public:
	MainWindow(QWidget* parent = nullptr);
private:
	Ui::MainWindow ui;
	SavefileManager savefileManager;

	void initializeButtons();

	void openButtonPressed();
	void saveButtonPressed();
signals:
	void contentChanged();
};