#include "mainwindow.hpp"

#include "searchradical.hpp"
#include "searchstrokecount.hpp"
#include "searchdraw.hpp"
#include "searchpinyin.hpp"
#include "searchenglish.hpp"
#include "rowedlist.hpp"

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
