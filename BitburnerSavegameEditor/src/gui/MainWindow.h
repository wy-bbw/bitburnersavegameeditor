#pragma once

//#include "ui.MainWindow.h"
#include <QMainWindow>
#include "ui_mainWindow.h"

class MainWindow : public QMainWindow  {
	Q_OBJECT
public:
	MainWindow(QWidget* parent = nullptr);
private:
	Ui::MainWindow ui;
};