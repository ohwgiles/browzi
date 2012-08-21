/// writtencharacter.h
/// This file is part of Plain Hanzi Editor (PHE):
/// http://qt-apps.org/content/show.php/PHE+-+Plain+Hanzi+Editor?content=100586
/// It is used in Browzi under the terms of the GPL, under which PHE is released.
/// Plain Hanzi Editor appears to be Copyright 2009 Alex Novichkov.
/// Specific copyright and licensing details were unforthcoming at the
/// time of this file's inclusion in Browzi.
/// Modifications to this file from its original are Copyright 2012 Oliver Giles
#ifndef WRITTENCHARACTER_H
#define WRITTENCHARACTER_H

#include <QList>

class WrittenStroke;
#include "characterdescriptor.h"

class WrittenCharacter
{
public:
    WrittenCharacter();
    QList<WrittenStroke> getStrokeList() {return this->strokeList;}
    void addStroke(WrittenStroke stroke);
    void clear();
    void analyzeAndMark();
    CharacterDescriptor buildCharacterDescriptor();
    void clearLastStroke();
private:
    QList<WrittenStroke> strokeList;
};

#endif

