#ifndef SEARCHENGLISH_HPP
#define SEARCHENGLISH_HPP
/**************************************************************************
 *
 *  searchenglish.hpp
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
#include "searchpanel.hpp"
#include "dbaccessor.hpp"

class QTreeWidget;
class QTreeWidgetItem;

class SearchEnglish : public SearchPanel, public DBAccessor {
	Q_OBJECT
public:
	SearchEnglish();

private slots:
	void searchTermModified(QString);
	void entrySelected(QTreeWidgetItem*,QTreeWidgetItem*);
	void setChineseFont(const QFont &);

private:
	QTreeWidget* candidates;
	sqlite3_stmt* stmt;
};

#endif // SEARCHENGLISH_HPP
