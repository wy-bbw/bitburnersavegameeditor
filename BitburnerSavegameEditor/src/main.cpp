#include <QtWidgets/QApplication>
#include <core/json/Node.h>
#include "gui/MainWindow.h"

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	a.setOrganizationDomain("wy-bbw.github");
	a.setApplicationName("BitburnerSavegameEditor");

	MainWindow m;
	m.show();
	a.exec();
}