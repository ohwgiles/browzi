/**************************************************************************
 *
 *  pinyin.cpp
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
#include "pinyin.hpp"
#include <QDebug>

PinyinConvertor::Mode PinyinConvertor::mode = PinyinConvertor::PINYIN_ACCENTED;

const QString PinyinConvertor::ACCENTS = QString::fromUtf8("aeiouüāēīōūǖáéíóúǘǎěǐǒǔǚàèìòùǜ");

QString PinyinConvertor::convert(QString s) {
	s = s.toLower();
	if(mode == PINYIN_ACCENTED && s.right(1).at(0).isDigit())
			return numberedToAccented(s.toLower());
	if(mode == PINYIN_NUMBERED && !s.right(1).at(0).isDigit())
			return accentedToNumbered(s.toLower());
	return s;
}

QString PinyinConvertor::numberedToAccented(QString p) {
	static const char simple_vowels[] = "ae*o";
	int toneNum = p.right(1).toInt() % 5;
	p.chop(1);
	int vowelIndex;
	for(int i=0;i<4;++i) {
		vowelIndex = p.indexOf(simple_vowels[i]);
		if(vowelIndex >= 0) {
			p.replace(vowelIndex, 1, ACCENTS[6*toneNum+i]);
			return p;
		}
	}
	int hvi = 0;
	int j = 0;
	for(int i=0; i<6; ++i) {
		hvi = p.lastIndexOf(ACCENTS[i]);
		if(hvi > vowelIndex) {
			vowelIndex = hvi;
			j = i;
		}
	}
	p.replace(vowelIndex, 1, ACCENTS[6*toneNum+j]);
	return p;
}

QString PinyinConvertor::accentedToNumbered(QString p) {
	int toneNum = 5;
	for(int i=6; i< ACCENTS.length(); ++i) {
		int accentIndex = p.indexOf(ACCENTS[i]);
		if(accentIndex >= 0) {
			toneNum = i/6;
			p.replace(accentIndex, 1, ACCENTS[i%6]);
			break;
		}
	}
	p.append(QString::number(toneNum));
	return p;
}
