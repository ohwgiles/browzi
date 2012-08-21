#include "searchdraw.hpp"
#include "rowedlist.hpp"
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QScrollArea>
#include "scribblearea.h"

#include "strokesmatcher.h"
#include "characterdescriptor.h"

SearchDraw::SearchDraw() {
	QVBoxLayout* vtLayout = new QVBoxLayout(this);
	QHBoxLayout* hzCanvasLayout = new QHBoxLayout();

	QSpacerItem* spCanvasLeft = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	hzCanvasLayout->addItem(spCanvasLeft);

	QVBoxLayout* vtCanvasLayout = new QVBoxLayout();
	QLabel* canvasDrawLabel = new QLabel(this);
	canvasDrawLabel->setText("Draw:");
	vtCanvasLayout->addWidget(canvasDrawLabel);

	canvasDraw = new ScribbleArea(this);
	canvasDraw->setFrameStyle(QFrame::Panel);
//	canvasDraw->setMinimumSize(QSize(256, 256));
//	canvasDraw->setMaximumSize(QSize(256, 256));
//	canvasDraw->setAutoFillBackground(false);
	vtCanvasLayout->addWidget(canvasDraw);

	hzCanvasLayout->addLayout(vtCanvasLayout);

	QSpacerItem* spCanvasRight = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	hzCanvasLayout->addItem(spCanvasRight);

	vtLayout->addLayout(hzCanvasLayout);

	QLabel*disambiguateLabel = new QLabel(this);
	disambiguateLabel->setText("Disambiguate:");
	vtLayout->addWidget(disambiguateLabel);

	QScrollArea* candidatesScrollArea = new QScrollArea(this);
	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(candidatesScrollArea->sizePolicy().hasHeightForWidth());
	candidatesScrollArea->setSizePolicy(sizePolicy);
	candidatesScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	candidatesScrollArea->setWidgetResizable(true);

	candidates = new RowedList(candidatesScrollArea);
	candidatesScrollArea->setWidget(candidates);
	candidatesScrollArea->setWidgetResizable(true);

	vtLayout->addWidget(candidatesScrollArea);

	connect(canvasDraw, SIGNAL(strokeAdded()), this, SLOT(searchHandwritten()));
	connect(candidates, SIGNAL(characterSelected(QString)), this, SLOT(disambiguated(QString)));
}


void SearchDraw::searchHandwritten() {
	CharacterDescriptor descr(canvasDraw->getCharacter().buildCharacterDescriptor());
	StrokesMatcher matcher(descr,false);//noStrokeOrderCheckBox->isChecked());
	//matcher.setNumMatches(preferences->maxNumMatches());
	//matcher.setOnlyExact(preferences->onlyExact());

	QList<QChar> v=matcher.doMatching();
//	if (preferences->autoInsert() && v.count()==1) insertFromHanList(QString(v.at(0)));

	QString matches="|";
	int vlength=v.count();

	for (int i=0; i<vlength; i++)
		matches.append(v.at(i));
	QStringList items;
	items << matches;
	candidates->clear();
	candidates->setItems(items);

}
