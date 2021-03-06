#ifndef SEARCHPINYIN_HPP
#define SEARCHPINYIN_HPP
/**************************************************************************
 *
 *  searchpinyin.hpp
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
#include "pinyin.hpp"

class RowedList;
class QLineEdit;

class SearchPinyin : public SearchPanel, public DBAccessor, public PinyinConvertor {
	Q_OBJECT
public:
	SearchPinyin();
	void refresh();
private:
	RowedList* candidates;
	sqlite3_stmt* stmt;
	QLineEdit* pinyin;
private slots:
	void searchTermChanged(QString s);
	void setChineseFont(const QFont &);
};

#endif // SEARCHPINYIN_HPP
