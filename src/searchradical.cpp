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
#include <sqlite3.h>

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

	listRadicals  = new RowedList(font(), true, radicalScrollArea);
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

	stmtExtraStrokes = createStatement(
				"select additionalStrokeCount from\
				kRSUnicodeTable where radicalIndex = ?\
				group by additionalStrokeCount;");
	stmtCandidates = createStatement(
				"select utf8 from utf8Table\
				inner join kRSUnicodeTable on kRSUnicodeTable.code=utf8Table.code\
				where kRSUnicodeTable.radicalIndex = ? and\
				krsUnicodeTable.additionalStrokeCount = ?;");
}

void SearchRadical::radicalChosen(QString s) {
	// get radical number from string
	uint radicalNumber = s.toUcs4()[0] - 0x2f00 + 1;
	listCandidates->clear();

	// First, get the number of possible additional strokes
	QList<uint> extraStrokes;
	{
		sqlite3_bind_int(stmtExtraStrokes, 1, radicalNumber);
		while(sqlite3_step(stmtExtraStrokes) == SQLITE_ROW) {
			extraStrokes.append(sqlite3_column_int(stmtExtraStrokes,0));
		}
		sqlite3_reset(stmtExtraStrokes);
		qSort(extraStrokes);
	}

	// Now for each possible number of extra strokes, assemble the list of candidates
	QStringList candidates;
	candidates.clear();
	{
		foreach(uint s, extraStrokes) {
			sqlite3_bind_int(stmtCandidates, 1, radicalNumber);
			sqlite3_bind_int(stmtCandidates, 2, s);

			QString chars = QString::number(s) + "|";
			while(sqlite3_step(stmtCandidates) == SQLITE_ROW) {
				chars.append(QString::fromUtf8((const char*)sqlite3_column_text(stmtCandidates,0)));
			}
			sqlite3_reset(stmtCandidates);
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
