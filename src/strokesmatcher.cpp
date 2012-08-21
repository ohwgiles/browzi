#include "strokesmatcher.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>

StrokesMatcher::StrokesMatcher(CharacterDescriptor character,bool noStrokeOrder_)
    : inputCharacter(character), noStrokeOrder(noStrokeOrder_)
{
    initStrokesData();
    numMatches=20;
    onlyExact=false;
}

void StrokesMatcher::setNumMatches(int i)
{
  numMatches=i;
}

void StrokesMatcher::setOnlyExact(bool b)
{
  onlyExact=b;
  
}

void StrokesMatcher::initStrokesData()
{
	 QFile f("strokes.txt");
    if (f.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream in(&f);
        in.setCodec("UTF-8");
        while (!in.atEnd()) {
            QString s = in.readLine();
            int i=s.length()-1;
            if (i>0) strokesData.insert(i,s);
        }
    }
}

CharacterDescriptor StrokesMatcher::loadNextCharacterStrokeData(const QString &s)
{
    QChar c=s.at(0);
    int numStrokes=s.length()-1;
    QList<int> strokes;
    for (int i=1; i<=numStrokes;i++) {
        strokes.append(s.mid(i,1).toInt());
    }
    CharacterDescriptor descr(strokes);
    descr.setCharacter(c);
    descr.setStrokeCount(numStrokes);
    return descr;
}

QList<QChar> StrokesMatcher::doMatching()
{
    int strokeCount = inputCharacter.getStrokeCount();
    QStringList list=strokesData.values(strokeCount);
    for (int i=0; i<list.count(); i++) {
        compareTo=loadNextCharacterStrokeData(list.at(i));
        QPair<QChar,double> match = compareToNext();
        if (match.second>=0) addMatch(match);
    }
    return getMatches();
}

void StrokesMatcher::addMatch(QPair<QChar,double> match)
{
    if(matches.values().contains(match.first)) {
        double key=matches.key(match.first);
        if (match.second > key) {
            QList<QChar> list=matches.values(key);
	        matches.remove(key);
	        list.removeOne(match.first);
	        foreach(QChar hj,list) matches.insert(key,hj);
	    } else return;
	}

    if(matches.size() >= numMatches) {
        QMutableMapIterator<double, QChar> i(matches);
        i.next();
	    if (match.second > i.key()) {
	       i.remove();
	    } else return;
	}

    matches.insert(match.second,match.first);
}

QList<QChar> StrokesMatcher::getMatches()
{
    QList<QChar> list;
    QMapIterator<double, QChar> i(matches);
    i.toBack();
    int j=0;
    while (i.hasPrevious()) {
        i.previous();
        list << i.value();
        j+=1;
        if (j==numMatches) break;
    }
    return list;
}

QPair<QChar,double> StrokesMatcher::compareToNext()
{
    QChar character = compareTo.getCharacter();
    double score = 0.0;
    QList<int> inputStrokes=inputCharacter.getSubStrokes();
    QList<int> compareStrokes=compareTo.getSubStrokes();
    if (onlyExact) {
        if (inputStrokes==compareStrokes) return qMakePair(character, double(inputStrokes.count()));
        else return qMakePair(character, -1.0);
    } else
    if (!noStrokeOrder){
    	for (int i=0; i<inputStrokes.count();i++) {
    	    int inp=inputStrokes.at(i);
    	    int comp=compareStrokes.at(i);
    	    if (inp==comp) score++;
    	    else if ((inp==1 && comp==6) || (inp==6 && comp==1)) score+=0.5;
    	    else if ((inp==2 && comp==8) || (inp==8 && comp==2)) score+=0.5;
    	    else if ((inp==4 && comp==9) || (inp==9 && comp==4)) score+=0.5;
    	}
    } else {
        score+=qMin(inputStrokes.count(1)+inputStrokes.count(6),
        compareStrokes.count(1)+compareStrokes.count(6))/qMax(qMax(inputStrokes.count(1)+inputStrokes.count(6),
        compareStrokes.count(1)+compareStrokes.count(6)),1);

        score+=qMin(inputStrokes.count(2)+inputStrokes.count(8),
        compareStrokes.count(2)+compareStrokes.count(8))/qMax(qMax(inputStrokes.count(2)+inputStrokes.count(8),
        compareStrokes.count(2)+compareStrokes.count(8)),1);

        score+=qMin(inputStrokes.count(4)+inputStrokes.count(9),
        compareStrokes.count(4)+compareStrokes.count(9))/qMax(qMax(inputStrokes.count(4)+inputStrokes.count(9),
        compareStrokes.count(4)+compareStrokes.count(9)),1);

        score+=qMin(inputStrokes.count(3),compareStrokes.count(3))/qMax(qMax(inputStrokes.count(3),
        compareStrokes.count(3)),1);

        score+=qMin(inputStrokes.count(5),compareStrokes.count(5))/qMax(qMax(inputStrokes.count(5),
        compareStrokes.count(5)),1);

    }
    return qMakePair(character, score);
}

