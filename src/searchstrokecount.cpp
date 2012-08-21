/**************************************************************************
 *
 *  searchstrokecount.cpp
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
#include "searchstrokecount.hpp"
#include <QSpinBox>
#include "rowedlist.h"
#include <QScrollArea>

#include "unihan.hpp"
#include <QLabel>
#include <QVBoxLayout>

SearchStrokeCount::SearchStrokeCount(QWidget *parent) : SearchPanel(parent) {
	QVBoxLayout* vtLayout = new QVBoxLayout(this);
	QHBoxLayout* hzLayout = new QHBoxLayout();

	QLabel* numStrokesLabel = new QLabel(this);
	numStrokesLabel->setText("Number of Strokes:");
	hzLayout->addWidget(numStrokesLabel);

	QSpinBox* numStrokes = new QSpinBox(this);
	numStrokes->setMinimum(1);
	numStrokes->setMaximum(32);
	hzLayout->addWidget(numStrokes);

	vtLayout->addLayout(hzLayout);

	QLabel* disambiguateLabel = new QLabel(this);
	disambiguateLabel->setText("Disambiguate:");
	vtLayout->addWidget(disambiguateLabel);

	QScrollArea* candidatesScrollArea = new QScrollArea(this);
	candidatesScrollArea->setObjectName(QString::fromUtf8("sc_sw"));
	candidatesScrollArea->setWidgetResizable(true);
	vtLayout->addWidget(candidatesScrollArea);

	candidates = new RowedList(font(), false, candidatesScrollArea);
	candidatesScrollArea->setWidget(candidates);
	candidatesScrollArea->setWidgetResizable(true);

	connect(numStrokes, SIGNAL(valueChanged(int)), this, SLOT(strokesChanged(int)));
	connect(candidates, SIGNAL(characterSelected(QString)), this, SLOT(disambiguated(QString)));

	numStrokes->setValue(1);
	strokesChanged(1);
}

void SearchStrokeCount::strokesChanged(int s) {
	QString result = "|";
	QString query = "select utf8 from utf8Table join kTotalStrokesTable on kTotalStrokesTable.code == utf8Table.code where kTotalStrokesTable.kTotalStrokes = " + QString::number(s);
	SQL_Result* res = unihanSql_get_sql_result(query.toAscii().constData());
	for(int i = 0; i < res->resultList->len; ++i) {
		result.append(QString::fromUtf8(stringList_index(res->resultList, i)));
	}
	sql_result_free(res, true);
	QStringList l;
	l << result;
	candidates->setItems(l);
}
/*
void SearchStrokeCount::disambiguate(QString s) {
	charChosen(s.toUcs4()[0]);
}*/
