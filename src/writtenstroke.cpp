#include "writtenpoint.h"
#include "writtenstroke.h"
#include "math.h"

#include <QtGui>
static const double PI   = 3.14159265358979323846;

WrittenStroke::WrittenStroke()
{
    pointList.clear();
    isanalyzed=false;
}

void WrittenStroke::addPoint(WrittenPoint point)
{
	this->pointList.append(point);
}

void WrittenStroke::clear()
{
    pointList.clear();
    isanalyzed=false;
}

int WrittenStroke::getType()
{
    if(!isanalyzed) {
		this->analyzeAndMark();
	}
	QList<double> directions;
	QList<double> lengths;
    int previousPoint=0;
    int co=pointList.count();
	for (int i=1; i<co;i++) {
		int nextPoint = i;
		if (pointList[nextPoint].isPivot()) {
		    double direction = pointList[previousPoint].getDirection(pointList[nextPoint]);
			double normalizedLength = pointList[previousPoint].distance(pointList[nextPoint]);
		    directions.append(direction*180/PI);
		    lengths.append(normalizedLength);
			previousPoint = nextPoint;
		}
	}

	//���������� ��� �����
	int num=directions.count();
	if (num!=lengths.count()) return 0;
	//������ - ��������������
	if (directions.at(0)>350 || directions.at(0)<30) {
	    if (num>=2) return 6;
	    else return 1;
	//������ - �������� �����
    } else if (directions.at(0)>180 && directions.at(0)<=260) {
	    if (num>=2 && lengths.at(1)>6) return 9;
	    else return 4;
	//������ - �������� ������
    } else if (directions.at(0)>=280 && directions.at(0)<=350) {
	    if (num>=2 && directions.at(1)>=30 && directions.at(1)<100
	        && lengths.at(0)<lengths.at(1)) return 5;
	    else return 3;
	//������ - ������������
    } else if (directions.at(0)>260 && directions.at(0)<280) {
	    if (num>=2 && lengths.at(1)>6) return 8;
	    else return 2;
	} else if (directions.at(0)>=30 && directions.at(0)<100) {
	    if (num>=2) return 6;
	    else return 5;
	} else return 0;
}

void WrittenStroke::analyzeAndMark()
{
    bool doneMerging=true;
    for (int i=0; i<pointList.count(); i++) {
            pointList[i].setIsPivot(true);
    }

    int num=0;
    QList<int> pivotPoints;
	for (int i=0;i<pointList.count();i++) {
	    if (pointList[i].isPivot()) {
	        num++;
	        pivotPoints << i;
	    }
	}

    bool reverse=true;

    while (doneMerging) {
        doneMerging=false;
        int colMerging=0;

        for (int i=reverse?0:1;i<=num-3;i+=2) {
            int firstPoint=pivotPoints.at(i);
            int middlePoint=pivotPoints.at(i+1);
            int secondPoint=pivotPoints.at(i+2);
            if (pointList[firstPoint].distance(pointList[middlePoint]) +
                pointList[secondPoint].distance(pointList[middlePoint]) <
                1.1 * pointList[secondPoint].distance(pointList[firstPoint]))
            {
                doneMerging=true;
                colMerging++;
                pointList[middlePoint].setIsPivot(false);
            }
        }
        reverse=!reverse;
        num-=colMerging;
        for (int j=0; j<pointList.count(); j++) {
            if (!pointList[j].isPivot()) pivotPoints.removeOne(j);
        }
    }

    for (int i=reverse?0:1;i<=num-3;i+=2) {
        int firstPoint=pivotPoints.at(i);
        int middlePoint=pivotPoints.at(i+1);
        int secondPoint=pivotPoints.at(i+2);
        if (pointList[firstPoint].distance(pointList[middlePoint]) +
            pointList[secondPoint].distance(pointList[middlePoint]) <
            1.1 * pointList[secondPoint].distance(pointList[firstPoint]))
        {
            pointList[middlePoint].setIsPivot(false);
        }
    }
	isanalyzed = true;
}

