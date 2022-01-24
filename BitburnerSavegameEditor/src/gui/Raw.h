#include "ui_Raw.h"
#include <QTreeView>


class Raw : public QWidget {
	Q_OBJECT
public:
	Raw(QWidget* parent);
	QTreeView* getView();
	void setView(QTreeView* view);
private:
	Ui::Raw ui;
};
