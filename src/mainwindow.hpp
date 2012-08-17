#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

class RowedList;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	void setRads();
	
private:
	Ui::MainWindow *ui;
	RowedList* rad_select;
	RowedList* rad_candidate;
};

#endif // MAINWINDOW_HPP
