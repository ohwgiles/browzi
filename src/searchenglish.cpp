/**************************************************************************
 *
 *  searchenglish.cpp
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
#include "searchenglish.hpp"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QTreeWidget>
#include <QHeaderView>
#include <sqlite3.h>

SearchEnglish::SearchEnglish() {
	QVBoxLayout* vtLayout = new QVBoxLayout(this);

	QLabel* englishWordLabel = new QLabel(this);
	englishWordLabel->setText("English word:");
	vtLayout->addWidget(englishWordLabel);

	QLineEdit* englishWord = new QLineEdit(this);
	vtLayout->addWidget(englishWord);

	QLabel* disambiguateLabel = new QLabel(this);
	disambiguateLabel->setText("Disambiguate:");
	vtLayout->addWidget(disambiguateLabel);

	candidates = new QTreeWidget(this);
	candidates->setColumnCount(3);
	candidates->setObjectName(QString::fromUtf8("en_results"));
	candidates->setColumnCount(3);
	candidates->header()->hide();
	candidates->setRootIsDecorated(false);
	vtLayout->addWidget(candidates);

	connect(englishWord, SIGNAL(textEdited(QString)), this, SLOT(searchTermModified(QString)));
	connect(candidates, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), this, SLOT(entrySelected(QTreeWidgetItem*,QTreeWidgetItem*)));

	stmt = createStatement(
				"select kMandarinTable.kMandarin,\
				utf8Table.utf8,\
				kDefinition\
			from kDefinitionTable \
			join kMandarinTable on kMandarinTable.code = kDefinitionTable.code \
			join utf8Table on utf8Table.code = kDefinitionTable.code \
			where kDefinition like ?\
			order by kMandarinTable.kMandarin;");
}

void SearchEnglish::searchTermModified(QString s) {
	candidates->clear();
	if(s.length() < 3) return;


	sqlite3_bind_text(stmt, 1, QString("%"+s+"%").toUtf8().constData(), -1, SQLITE_TRANSIENT);
	QList<QTreeWidgetItem *> items;
	while(sqlite3_step(stmt) == SQLITE_ROW) {
		QStringList cols;
		cols << QString::fromUtf8((const char*)sqlite3_column_text(stmt, 0))
			  << QString::fromUtf8((const char*)sqlite3_column_text(stmt, 1))
			  << QString::fromUtf8((const char*)sqlite3_column_text(stmt, 2));
		items.append(new QTreeWidgetItem((QTreeWidget*)0, cols));
	}
	sqlite3_reset(stmt);
	candidates->insertTopLevelItems(1, items);
	candidates->resizeColumnToContents(0);
	candidates->resizeColumnToContents(1);
}

void SearchEnglish::entrySelected(QTreeWidgetItem* newItem,QTreeWidgetItem*) {
	disambiguated( newItem->data(1, Qt::DisplayRole).toString());
}
void SearchEnglish::setChineseFont(const QFont & f) {
	candidates->setFont(f);
}
