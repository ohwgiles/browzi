#ifndef PINYIN_HPP
#define PINYIN_HPP
/**************************************************************************
 *
 *  pinyin.hpp
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

#include <QString>

class PinyinConvertor {
public:
	enum Mode { PINYIN_ACCENTED=0, PINYIN_NUMBERED };
	static void setAccented() { mode = PINYIN_ACCENTED; }
	static void setNumbered() { mode = PINYIN_NUMBERED; }
protected:
	QString convert(QString s);
private:
	QString numberedToAccented(QString p);
	QString accentedToNumbered(QString p);
	static Mode mode;
	static const QString ACCENTS;
public:
	static Mode getMode() { return mode; }
};


#endif // PINYIN_HPP
