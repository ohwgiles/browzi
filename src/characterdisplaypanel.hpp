#ifndef CHARACTERDISPLAYPANEL_HPP
#define CHARACTERDISPLAYPANEL_HPP
/**************************************************************************
 *
 *  characterdisplaypanel.hpp
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
#include "dbaccessor.hpp"

class QLineEdit;
class QPlainTextEdit;

class CharacterDisplayPanel : public QWidget, public DBAccessor {
	Q_OBJECT
public:
	CharacterDisplayPanel();

public slots:
	void setChineseFont(QFont f);
	void setCharacter(uint);
	void clear();

private:
	QLineEdit* rs_hz;
	QLineEdit* rs_rad;
	QLineEdit* rs_es;
	QLineEdit* rs_ts;
	QPlainTextEdit* rs_def;
	QLineEdit* rs_py;
	QLineEdit* rs_cj;
	QLineEdit* rs_hsk;
	QLineEdit* rs_fq;

	sqlite3_stmt* stmt;
	sqlite3_stmt* pinyinStmt;
};

#endif // CHARACTERDISPLAYPANEL_HPP
