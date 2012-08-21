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
