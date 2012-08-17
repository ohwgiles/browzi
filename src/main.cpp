#include <QApplication>
#include "mainwindow.hpp"

int main(int argc, char** argv) {
	QApplication app(argc, argv);
	MainWindow m;
	m.show();
	m.setRads();
	app.exec();
}
