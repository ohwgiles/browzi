/**************************************************************************
 *
 *  searchdraw.cpp
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
#include "searchdraw.hpp"
#include "rowedlist.h"
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

	candidates = new RowedList(font(), false, candidatesScrollArea);
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
