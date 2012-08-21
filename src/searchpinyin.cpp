/**************************************************************************
 *
 *  searchpinyin.cpp
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
#include "searchpinyin.hpp"
#include "rowedlist.h"
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLineEdit>
#include <QLabel>
#include "unihan.hpp"

SearchPinyin::SearchPinyin()
{
	QVBoxLayout* vtLayout = new QVBoxLayout(this);

	QLabel* pinyinLabel = new QLabel(this);
	pinyinLabel->setText("Pinyin:");
	vtLayout->addWidget(pinyinLabel);

	QLineEdit* pinyin = new QLineEdit(this);
	vtLayout->addWidget(pinyin);

	QLabel* disambiguateLabel = new QLabel(this);
	disambiguateLabel->setText("Disambiguate:");
	disambiguateLabel->setObjectName(QString::fromUtf8("label"));
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

	connect(pinyin, SIGNAL(textEdited(QString)), this, SLOT(searchTermChanged(QString)));
	connect(candidates, SIGNAL(characterSelected(QString)), this, SLOT(disambiguated(QString)));
}

void SearchPinyin::searchTermChanged(QString s) {
	candidates->clear();
	if(s.isEmpty()) return;

	char first,last;
	if(s.at(s.length()-1).isNumber()) {
		first = last = s.at(s.length()-1).toAscii();
		s.chop(1);
	} else {
		first = '1';
		last = '5';
	}

	QStringList cnd;
	do {
		QString query = "select utf8 from utf8Table join \
				kMandarinTable on kMandarinTable.code = utf8Table.code \
				where kMandarinTable.kMandarin = \"" + s.toUpper() + first + "\"";
		SQL_Result* res = unihanSql_get_sql_result(query.toAscii().constData());
		QString hanzi = s + first + "|";
		for(int i = 0; i < res->resultList->len; ++i) {
			hanzi.append(QString::fromUtf8(stringList_index(res->resultList, i)));
		}
		sql_result_free(res, true);
		cnd << hanzi;
	} while(first++ != last);

	candidates->setItems(cnd);
}
