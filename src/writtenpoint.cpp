/// writtenpoint.cpp
/// This file is part of Plain Hanzi Editor (PHE):
/// http://qt-apps.org/content/show.php/PHE+-+Plain+Hanzi+Editor?content=100586
/// It is used in Browzi under the terms of the GPL, under which PHE is released.
/// Plain Hanzi Editor appears to be Copyright 2009 Alex Novichkov.
/// Specific copyright and licensing details were unforthcoming at the
/// time of this file's inclusion in Browzi.
/// Modifications to this file from its original are Copyright 2012 Oliver Giles
#include "writtenpoint.h"
#include "math.h"
#include <QtGlobal>
const float Pi = 3.141592654f;

WrittenPoint::WrittenPoint()
{
    this->xc=-1;
    this->yc=-1;
    this->ispivot=false;
    this->subStrokeIndex=-1;
}

WrittenPoint::WrittenPoint(int x, int y)
    : xc(x), yc(y)
{
    this->ispivot=false;
    this->subStrokeIndex=-1;
}

int WrittenPoint::getSubStrokeIndex() {
	return this->subStrokeIndex;
}

void WrittenPoint::setX(int x)
{
    this->xc=x;
}

void WrittenPoint::setY(int y)
{
    this->yc=y;
}

int WrittenPoint::getX()
{
    return this->xc;
}

int WrittenPoint::getY()
{
    return this->yc;
}

void WrittenPoint::setSubStrokeIndex(int subStrokeIndex) {
	this->subStrokeIndex = subStrokeIndex;
}

bool WrittenPoint::isPivot() {
	return this->ispivot;
}
void WrittenPoint::setIsPivot(bool isPivot) {
	this->ispivot = isPivot;
}

double WrittenPoint::distance(WrittenPoint comparePoint)
{
    return sqrt(pow(this->xc-comparePoint.getX(), 2)+pow(this->yc-comparePoint.getY(),2));
}

double WrittenPoint::getDistanceNormalized(WrittenPoint comparePoint,
        double rightX, double leftX, double bottomY, double topY)
{
    double width = rightX - leftX;
	double height = bottomY - topY;
	double dimensionSquared = width > height ? width * width : height * height;
	double normalizer = sqrt(dimensionSquared + dimensionSquared);
	double distanceNormalized = this->distance(comparePoint) / normalizer;
	distanceNormalized = qMin(distanceNormalized, 1.0);
	return distanceNormalized;
}

double WrittenPoint::getDirection(WrittenPoint comparePoint) {
	double dx = this->xc - comparePoint.getX();
	double dy = this->yc - comparePoint.getY();

	double direction = Pi-atan2(dy,dx);
	return direction;
}
