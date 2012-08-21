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

#include "searchradical.hpp"
#include "searchstrokecount.hpp"
#include "searchdraw.hpp"
#include "searchpinyin.hpp"
#include "searchenglish.hpp"
#include "rowedlist.h"

#include "characterdisplaypanel.hpp"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
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
	SearchDraw* searchByDraw = new SearchDraw();
	tabWidget->addTab(searchByDraw, "Draw");
	SearchPinyin* searchPinyin = new SearchPinyin();
	tabWidget->addTab(searchPinyin, "Pinyin");
	SearchEnglish* searchEnglish = new SearchEnglish();
	tabWidget->addTab(searchEnglish, "English");
	hzLayout->addWidget(tabWidget);

	// vtLayout contains the character panel, plus a spacer and about button
	QVBoxLayout* vtLayout = new QVBoxLayout();

	displayPanel = new CharacterDisplayPanel();
	vtLayout->addWidget(displayPanel);

	QSpacerItem* verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
	vtLayout->addItem(verticalSpacer);

	// The about button (flush right)
	QHBoxLayout* aboutButtonLayout = new QHBoxLayout();
	QSpacerItem* aboutButtonSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	aboutButtonLayout->addItem(aboutButtonSpacer);
	QPushButton* aboutButton = new QPushButton(mainPanel);
	aboutButton->setText("About Browzi");
	aboutButtonLayout->addWidget(aboutButton);
	vtLayout->addLayout(aboutButtonLayout);

	hzLayout->addLayout(vtLayout);

	setCentralWidget(mainPanel);

	// Connect notifications
	connect(searchByRadical, SIGNAL(showCharacter(uint)), displayPanel, SLOT(setCharacter(uint)));
	connect(searchByStrokeCount, SIGNAL(showCharacter(uint)), displayPanel, SLOT(setCharacter(uint)));
	connect(searchByDraw, SIGNAL(showCharacter(uint)), displayPanel, SLOT(setCharacter(uint)));
	connect(searchPinyin, SIGNAL(showCharacter(uint)), displayPanel, SLOT(setCharacter(uint)));
	connect(searchEnglish, SIGNAL(showCharacter(uint)), displayPanel, SLOT(setCharacter(uint)));

	connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));
}

void MainWindow::tabChanged(int i) {
	SearchPanel* panel = static_cast<SearchPanel*>(tabWidget->widget(i));
	displayPanel->setCharacter(panel->lastChar());
}

MainWindow::~MainWindow()
{
	delete displayPanel;
}
