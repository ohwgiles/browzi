#ifndef SEARCHPANEL_HPP
#define SEARCHPANEL_HPP
/**************************************************************************
 *
 *  searchpanel.hpp
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

#include <QWidget>
class CharacterDisplayPanel;

class SearchPanel : public QWidget {
	Q_OBJECT
public:
	SearchPanel(QWidget *parent = 0);

	//void charChosen(uint);
	uint lastChar() const { return lastCharacter; }
private:
	uint lastCharacter;

signals:
	void showCharacter(uint);
protected slots:
	void disambiguated(QString);
};

#endif // SEARCHPANEL_HPP
