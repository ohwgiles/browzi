#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

class RowedList;
class SearchPanel;
class CharacterDisplayPanel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	
private:
	QTabWidget* tabWidget;
	CharacterDisplayPanel* displayPanel;

private slots:
	void tabChanged(int);
};

#endif // MAINWINDOW_HPP
