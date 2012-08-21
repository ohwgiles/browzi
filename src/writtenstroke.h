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

