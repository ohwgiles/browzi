/**************************************************************************
 *
 *  searchradical.cpp
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
#include "searchradical.hpp"
#include "rowedlist.h"
#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>
#include "unihan.hpp"

SearchRadical::SearchRadical(QWidget *parent) : SearchPanel(parent) {
	QVBoxLayout* vtLayout = new QVBoxLayout(this);
	QLabel* radicalLabel = new QLabel(this);
	radicalLabel->setText("Radical:");
	vtLayout->addWidget(radicalLabel);

	QScrollArea* radicalScrollArea = new QScrollArea(this);
	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(radicalScrollArea->sizePolicy().hasHeightForWidth());
	radicalScrollArea->setSizePolicy(sizePolicy);
	radicalScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	radicalScrollArea->setWidgetResizable(true);
	vtLayout->addWidget(radicalScrollArea);

	QLabel* disambiguateLabel = new QLabel(this);
	disambiguateLabel->setText("Disambiguate:");
	vtLayout->addWidget(disambiguateLabel);

	QScrollArea* candidatesScrollArea = new QScrollArea(this);
	sizePolicy.setHeightForWidth(candidatesScrollArea->sizePolicy().hasHeightForWidth());
	candidatesScrollArea->setSizePolicy(sizePolicy);
	candidatesScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	candidatesScrollArea->setWidgetResizable(true);
	vtLayout->addWidget(candidatesScrollArea);

	listRadicals  = new RowedList(font(), false, radicalScrollArea);
	radicalScrollArea->setWidget(listRadicals);
	radicalScrollArea->setWidgetResizable(true);
	listCandidates = new RowedList(font(), false, candidatesScrollArea);
	candidatesScrollArea->setWidget(listCandidates);
	candidatesScrollArea->setWidgetResizable(true);

	QString rad = "|";
	for(int i=0; i < 214; ++i) {
		uint radical = 0x2f00 + i;
		rad += QString::fromUcs4(&radical, 1);
	}

	QStringList p;
	p << rad;
	listRadicals->setItems(p);

	connect(listRadicals, SIGNAL(characterSelected(QString)), this, SLOT(radicalChosen(QString)));
	connect(listCandidates, SIGNAL(characterSelected(QString)), this, SLOT(disambiguated(QString)));
}

void SearchRadical::radicalChosen(QString s) {
	// get radical number from string
	uint radicalNumber = s.toUcs4()[0] - 0x2f00 + 1;
	listCandidates->clear();

	// First, get the number of possible additional strokes
	QList<uint> extraStrokes;
	{
		QString query = "select additionalStrokeCount from kRSUnicodeTable where radicalIndex = " + QString::number(radicalNumber) + " group by additionalStrokeCount";
		SQL_Result* res = unihanSql_get_sql_result(query.toAscii().constData());
		for(int i = 0; i < res->resultList->len; ++i) {
			extraStrokes.append(QString(stringList_index(res->resultList, i)).toInt());
		}
		sql_result_free(res, true);
		qSort(extraStrokes);
	}

	// Now for each possible number of extra strokes, assemble the list of candidates
	QStringList candidates;
	candidates.clear();
	{
		foreach(uint s, extraStrokes) {
			QString query = "select utf8 from utf8Table inner join kRSUnicodeTable on kRSUnicodeTable.code=utf8Table.code where kRSUnicodeTable.radicalIndex = " + QString::number(radicalNumber) + " and krsUnicodeTable.additionalStrokeCount = " + QString::number(s);
			SQL_Result* res = unihanSql_get_sql_result(query.toAscii().constData());
			QString chars = QString::number(s) + "|";
			for(int i = 0; i < res->resultList->len; ++i) {
				chars.append(QString::fromUtf8(stringList_index(res->resultList, i)));
			}
			sql_result_free(res, true);
			candidates << chars;
		}
	}
	listCandidates->setItems(candidates);
}
/*
void SearchRadical::disambiguated(QString s) {
	// get char number from string
	charChosen(s.toUcs4()[0]);
}*/

SearchRadical::~SearchRadical() {
}
