/// strokesmatcher.h
/// This file is part of Plain Hanzi Editor (PHE):
/// http://qt-apps.org/content/show.php/PHE+-+Plain+Hanzi+Editor?content=100586
/// It is used in Browzi under the terms of the GPL, under which PHE is released.
/// Plain Hanzi Editor appears to be Copyright 2009 Alex Novichkov.
/// Specific copyright and licensing details were unforthcoming at the
/// time of this file's inclusion in Browzi.
/// Modifications to this file from its original are Copyright 2012 Oliver Giles
#ifndef STROKESMATCHER_H
#define STROKESMATCHER_H

#include <QMultiHash>
#include <QMultiMap>

#include "characterdescriptor.h"

class StrokesMatcher
{
public:
    StrokesMatcher(CharacterDescriptor character,bool noStrokeOrder);
    QList<QChar> doMatching();
    void setNumMatches(int);
    void setOnlyExact(bool);
private:
    QPair<QChar,double> compareToNext();
    CharacterDescriptor inputCharacter;
	CharacterDescriptor compareTo;
    QMultiMap<double,QChar> matches;
    void addMatch(QPair<QChar,double> match);
    QList<QChar> getMatches();

    int numMatches;
    bool noStrokeOrder;
    QMultiHash<int,QString> strokesData;
    void initStrokesData();
    CharacterDescriptor loadNextCharacterStrokeData(const QString &);
    bool onlyExact;
};

#endif
