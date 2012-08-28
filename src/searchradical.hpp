#ifndef SEARCHRADICAL_HPP
#define SEARCHRADICAL_HPP
/**************************************************************************
 *
 *  searchradical.hpp
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

class RowedList;
class QScrollArea;

class SearchRadical : public SearchPanel, public DBAccessor {
	Q_OBJECT
public:
	SearchRadical(QWidget* parent);
	virtual ~SearchRadical();
private:
	RowedList* listRadicals;
	sqlite3_stmt* stmtExtraStrokes;
	RowedList* listCandidates;
	sqlite3_stmt* stmtCandidates;

private slots:
	void radicalChosen(QString);
	void setChineseFont(const QFont &);
	//void disambiguated(QString);
};

#endif // SEARCHRADICAL_HPP
