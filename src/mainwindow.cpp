#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "searchradical.hpp"
#include "rowedlist.h"

#include "characterdisplaypanel.hpp"

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	rad_select  = new RowedList(ui->scrollArea);
	ui->scrollArea->setWidget(rad_select);
	ui->scrollArea->setWidgetResizable(true);
	rad_candidate = new RowedList(ui->scrollArea_2);
	ui->scrollArea_2->setWidget(rad_candidate);
	ui->scrollArea_2->setWidgetResizable(true);

}

void MainWindow::setRads() {
	SearchRadical* s = new SearchRadical(*rad_select, *rad_candidate);
	CharacterDisplayPanel* p = new CharacterDisplayPanel(*ui);
	connect(s,SIGNAL(showCharacter(uint)), p, SLOT(setCharacter(uint)));
}

MainWindow::~MainWindow()
{
	delete ui;
}
