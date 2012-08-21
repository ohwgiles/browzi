/// writtenpoint.h
/// This file is part of Plain Hanzi Editor (PHE):
/// http://qt-apps.org/content/show.php/PHE+-+Plain+Hanzi+Editor?content=100586
/// It is used in Browzi under the terms of the GPL, under which PHE is released.
/// Plain Hanzi Editor appears to be Copyright 2009 Alex Novichkov.
/// Specific copyright and licensing details were unforthcoming at the
/// time of this file's inclusion in Browzi.
/// Modifications to this file from its original are Copyright 2012 Oliver Giles
#ifndef WRITTENPOINT_H
#define WRITTENPOINT_H

class WrittenPoint
{
public:
    WrittenPoint();
    WrittenPoint(int x,int y);
    int getSubStrokeIndex();
    bool isPivot();
    double getDirection(WrittenPoint comparePoint);
    double getDistanceNormalized(WrittenPoint comparePoint,double rightX, double leftX, double bottomY, double topY);
    void setSubStrokeIndex(int);
    void setIsPivot(bool);
    double distance(WrittenPoint);
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);

private:
    int xc;
    int yc;
    int subStrokeIndex;
    bool ispivot;
};

#endif

