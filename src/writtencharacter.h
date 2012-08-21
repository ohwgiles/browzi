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

