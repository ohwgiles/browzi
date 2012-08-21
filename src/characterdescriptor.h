/// characterdescriptor.h
/// This file is part of Plain Hanzi Editor (PHE):
/// http://qt-apps.org/content/show.php/PHE+-+Plain+Hanzi+Editor?content=100586
/// It is used in Browzi under the terms of the GPL, under which PHE is released.
/// Plain Hanzi Editor appears to be Copyright 2009 Alex Novichkov.
/// Specific copyright and licensing details were unforthcoming at the
/// time of this file's inclusion in Browzi.
/// Modifications to this file from its original are Copyright 2012 Oliver Giles
#ifndef CHARACTERDESCRIPTOR_H
#define CHARACTERDESCRIPTOR_H

#include <QList>
#include <QChar>

class CharacterDescriptor
{
public:
    CharacterDescriptor(QList<int> subStrokes)
        : substrokes(subStrokes) {}
    CharacterDescriptor() {}
    QChar getCharacter() {return this->character;}
    void setCharacter(QChar character) {this->character = character;	}
    int getStrokeCount() {return this->strokeCount;}
    void setStrokeCount(int strokeCount) {this->strokeCount = strokeCount;}
	QList<int> getSubStrokes() {return this->substrokes;}
	void setSubStrokes(QList<int> subStrokes) {this->substrokes=subStrokes;}
private:
    QChar character;
	int strokeCount;
	QList<int> substrokes;
};

#endif

