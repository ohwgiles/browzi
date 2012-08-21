/// writtenstroke.h
/// This file is part of Plain Hanzi Editor (PHE):
/// http://qt-apps.org/content/show.php/PHE+-+Plain+Hanzi+Editor?content=100586
/// It is used in Browzi under the terms of the GPL, under which PHE is released.
/// Plain Hanzi Editor appears to be Copyright 2009 Alex Novichkov.
/// Specific copyright and licensing details were unforthcoming at the
/// time of this file's inclusion in Browzi.
/// Modifications to this file from its original are Copyright 2012 Oliver Giles
#ifndef WRITTENSTROKE_H
#define WRITTENSTROKE_H

#include <QList>
#include "writtenpoint.h"
#include "math.h"

class WrittenStroke
{
public:
    WrittenStroke();
    QList<WrittenPoint> getPointList() { return this->pointList;}
    bool isAnalyzed() {	return this->isanalyzed;	}
    void addPoint(WrittenPoint point);
    int getType();
    void analyzeAndMark();
    void clear();
private:
    QList<WrittenPoint> pointList;
    bool isanalyzed;
};

#endif

