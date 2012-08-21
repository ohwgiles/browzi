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

