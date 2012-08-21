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

class RowedList;

class SearchPinyin : public SearchPanel
{
	Q_OBJECT
public:
	SearchPinyin();
private:
	RowedList* candidates;
private slots:
	void searchTermChanged(QString s);
};

#endif // SEARCHPINYIN_HPP
