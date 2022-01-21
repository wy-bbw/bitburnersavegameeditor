
#include <QtTest>

class MainWindowTest : public QObject {
	Q_OBJECT
private slots:
	void shouldPass() {
		QVERIFY(true);
	}

	void shouldFail() {
		QVERIFY(false);
	}
};