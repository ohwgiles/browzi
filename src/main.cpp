#include <QApplication>
#include "mainwindow.hpp"
#include "unihan.hpp"


int main(int argc, char** argv) {
	unihanDb_open_default();
	setlocale(LC_CTYPE, "zh_CN.UTF-8");

	QApplication app(argc, argv);
	MainWindow m;
	m.show();
	app.exec();


	unihanDb_close();
}
