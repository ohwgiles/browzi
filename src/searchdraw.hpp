#ifndef SEARCHDRAW_HPP
#define SEARCHDRAW_HPP
/**************************************************************************
 *
 *  searchdraw.hpp
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

class ScribbleArea;
class RowedList;

class SearchDraw : public SearchPanel, public DBAccessor {
	Q_OBJECT
public:
	SearchDraw();
private slots:
	void searchHandwritten();
private:
	ScribbleArea* canvasDraw;
	RowedList* candidates;
	void setChineseFont(const QFont &);
};

#endif // SEARCHDRAW_HPP
