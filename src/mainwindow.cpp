/**************************************************************************
 *
 *  mainwindow.cpp
 *  Copyright 2012 Oliver Giles
 *
 *  This file is part of Browzi.
 *
 *  Browzi is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Browzi is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Browzi.  If not, see <http://www.gnu.org/licenses/>.
 *
 **************************************************************************/
#include "mainwindow.hpp"

#include "version.h"
#include "searchradical.hpp"
#include "searchstrokecount.hpp"
#include "searchdraw.hpp"
#include "searchpinyin.hpp"
#include "searchenglish.hpp"
#include "clipboard.hpp"
#include "rowedlist.h"

#include "characterdisplaypanel.hpp"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QIcon>
#include <QMenuBar>
#include <QFontDialog>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
	setWindowTitle("Browzi");

	QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(tr("E&xit"), this, SLOT(close()), QKeySequence(Qt::ALT | Qt::Key_F4));
	QMenu* viewMenu = menuBar()->addMenu(tr("&View"));
	viewMenu->addAction(tr("&Font..."), this, SLOT(showFontDialog()));
	QActionGroup* pinyinGroup = new QActionGroup(this);
	pa = new QAction("Accented Pinyin",this);
	pa->setCheckable(true);
	pinyinGroup->addAction(pa);
	pn = new QAction("Numbered Pinyin",this);
	pn->setCheckable(true);
	pinyinGroup->addAction(pn);
	connect(pinyinGroup, SIGNAL(triggered(QAction*)), this, SLOT(pinyinDisplayChanged(QAction*)));
	viewMenu->addSeparator();
	viewMenu->addAction(pa);
	viewMenu->addAction(pn);

	QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(tr("Visit &Website"), this, SLOT(goToWebsite()));
	helpMenu->addAction(tr("&About Browzi"), this, SLOT(showAboutBox()));

	// Holds all the sub-widgets
	QWidget* mainPanel = new QWidget(this);
	// hzLayout has the tabs in the left, the character display in the right
	QHBoxLayout* hzLayout = new QHBoxLayout(mainPanel);

	// Set up the search tab
	tabWidget = new QTabWidget(mainPanel);
	// Add tabs to the widget
	SearchRadical* searchByRadical = new SearchRadical(mainPanel);
	tabWidget->addTab(searchByRadical, QString("Radical"));
	SearchStrokeCount* searchByStrokeCount = new SearchStrokeCount();
	tabWidget->addTab(searchByStrokeCount, QString("Stroke Count"));
	SearchDraw* searchByDraw = new SearchDraw(tabWidget);
	tabWidget->addTab(searchByDraw, "Draw");
	SearchPinyin* searchPinyin = new SearchPinyin();
	tabWidget->addTab(searchPinyin, "Pinyin");
	SearchEnglish* searchEnglish = new SearchEnglish();
	tabWidget->addTab(searchEnglish, "English");
	Clipboard* clipboard = new Clipboard();
	tabWidget->addTab(clipboard, "Clipboard");

	hzLayout->addWidget(tabWidget);
	hzLayout->setStretchFactor(tabWidget, 2);

	// vtLayout contains the character panel, plus a spacer and about button
	QVBoxLayout* vtLayout = new QVBoxLayout();

	displayPanel = new CharacterDisplayPanel();
	vtLayout->addWidget(displayPanel);

	QSpacerItem* verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
	vtLayout->addItem(verticalSpacer);

	hzLayout->addLayout(vtLayout);
	hzLayout->setStretchFactor(vtLayout, 1);

	setCentralWidget(mainPanel);

	// Connect notifications
	connect(searchByRadical, SIGNAL(showCharacter(uint)), displayPanel, SLOT(setCharacter(uint)));
	connect(searchByStrokeCount, SIGNAL(showCharacter(uint)), displayPanel, SLOT(setCharacter(uint)));
	connect(searchByDraw, SIGNAL(showCharacter(uint)), displayPanel, SLOT(setCharacter(uint)));
	connect(searchPinyin, SIGNAL(showCharacter(uint)), displayPanel, SLOT(setCharacter(uint)));
	connect(searchEnglish, SIGNAL(showCharacter(uint)), displayPanel, SLOT(setCharacter(uint)));
	connect(clipboard, SIGNAL(showCharacter(uint)), displayPanel, SLOT(setCharacter(uint)));

	connect(this, SIGNAL(updateChineseFont(QFont)), searchByDraw, SLOT(setChineseFont(QFont)));
	connect(this, SIGNAL(updateChineseFont(QFont)), searchByRadical, SLOT(setChineseFont(QFont)));
	connect(this, SIGNAL(updateChineseFont(QFont)), searchByStrokeCount, SLOT(setChineseFont(QFont)));
	connect(this, SIGNAL(updateChineseFont(QFont)), searchPinyin, SLOT(setChineseFont(QFont)));
	connect(this, SIGNAL(updateChineseFont(QFont)), searchEnglish, SLOT(setChineseFont(QFont)));
	connect(this, SIGNAL(updateChineseFont(QFont)), clipboard, SLOT(setChineseFont(QFont)));
	connect(this, SIGNAL(updateChineseFont(QFont)), displayPanel, SLOT(setChineseFont(QFont)));

	connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));

	QSettings s("Browzi", "Browzi");
	setGeometry(QRect(s.value("pos", QPoint(200,100)).toPoint(), s.value("size",QSize(600,400)).toSize()));

	lastFont = QFont(s.value("font","unifont").toString(), 12);
	emit updateChineseFont(lastFont);

	PinyinConvertor::Mode m = PinyinConvertor::Mode(s.value("pinyin", 0).toInt());
	if(m == PinyinConvertor::PINYIN_ACCENTED) {
		pa->setChecked(true);
		PinyinConvertor::setAccented();
	}
	if(m == PinyinConvertor::PINYIN_NUMBERED) {
		pn->setChecked(true);
		PinyinConvertor::setNumbered();
	}
}

void MainWindow::tabChanged(int i) {
	SearchPanel* panel = static_cast<SearchPanel*>(tabWidget->widget(i));
	displayPanel->setCharacter(panel->lastChar());
}

void MainWindow::showFontDialog() {
	bool ok;
	QFont f = QFontDialog::getFont(&ok, lastFont, this, tr("Select a font"));
	if(ok) {
		lastFont = f;
		emit updateChineseFont(lastFont);
	}
}

void MainWindow::pinyinDisplayChanged(QAction * a) {
	if(a == pa) PinyinConvertor::setAccented();
	if(a == pn) PinyinConvertor::setNumbered();
	SearchPanel* panel = static_cast<SearchPanel*>(tabWidget->currentWidget());
	panel->refresh();
	displayPanel->setCharacter(panel->lastChar());
}

void MainWindow::goToWebsite() {
	QDesktopServices::openUrl(QUrl("http://ohwgiles.github.com/browzi/"));
}

void MainWindow::closeEvent(QCloseEvent *) {
	// save the font and window geometry for next time
	QSettings s("Browzi","Browzi");
	s.setValue("font",lastFont.toString());
	s.setValue("size",size());
	s.setValue("pos",pos());
	s.setValue("pinyin", PinyinConvertor::getMode());
}

void MainWindow::showAboutBox() {
	QMessageBox::about(this, tr("About Browzi"), tr(
			"Browzi version " BROWZI_VERSION "\n\n"
			"Chinese Hanzi Browser (Unihan database)\n\n"
			"Copyright 2012 Oliver Giles\n"
			"http://ohwgiles.github.com/browzi/"));
}

MainWindow::~MainWindow()
{
	delete displayPanel;
}
