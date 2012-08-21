#include <QtGui>

#include "scribblearea.h"

ScribbleArea::ScribbleArea(QWidget *parent)
    : QFrame(parent)
{
    setAttribute(Qt::WA_StaticContents);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    scribbling = false;
    myPenWidth = 3;
    myPenColor = Qt::black;
}

QSize ScribbleArea::sizeHint() const
{
    return QSize(200,200);
}

void ScribbleArea::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
}

void ScribbleArea::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}

void ScribbleArea::clear()
{
    inputCharacter.clear();
    currentStroke.clear();
    update();
}

void ScribbleArea::undo()
{
	if(!inputCharacter.getStrokeList().isEmpty()) {
	  inputCharacter.clearLastStroke();
	}
	update();
}

void ScribbleArea::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        scribbling = true;
        previousPoint = WrittenPoint(e->x(), e->y());
    }
}

void ScribbleArea::mouseMoveEvent(QMouseEvent *e)
{
    if ((e->buttons() & Qt::LeftButton) && scribbling) {
        WrittenPoint nextPoint(e->x(), e->y());
		if (previousPoint.getX()>=0 && previousPoint.distance(nextPoint) >= 5.0) {
		    double pointX = previousPoint.getX();
            double pointY = previousPoint.getY();
  		    if(currentStroke.getPointList().isEmpty()) {
				currentStroke.addPoint(previousPoint);
			}

			currentStroke.addPoint(nextPoint);
			pointX = nextPoint.getX();
            pointY = nextPoint.getY();
			previousPoint = nextPoint;
		}
    }
    update();
}

void ScribbleArea::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton && scribbling) {
        mouseMoveEvent(e);

        if (!currentStroke.getPointList().isEmpty()) {
			inputCharacter.addStroke(currentStroke);
			previousPoint = WrittenPoint();
			currentStroke.clear();
			emit strokeAdded();
		}

        scribbling = false;
        update();
    }

}

void ScribbleArea::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);
    QRectF rect(0,0,width(),height());
    painter.drawRect(rect);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    if (!currentStroke.getPointList().isEmpty()) {
		QListIterator<WrittenPoint> pointIter(currentStroke.getPointList());
    	WrittenPoint previousPoint = (WrittenPoint)pointIter.next();
    	while(pointIter.hasNext()) {
    		WrittenPoint nextPoint = (WrittenPoint)pointIter.next();
    		painter.drawLine(previousPoint.getX(), previousPoint.getY(), nextPoint.getX(), nextPoint.getY());
    		previousPoint = nextPoint;
    	}
	}
    
    QList<WrittenStroke> list=inputCharacter.getStrokeList();
    
	for (int i=0; i<list.count();i++) {
	    WrittenStroke nextStroke=list.at(i);
		QListIterator<WrittenPoint> pointIter(nextStroke.getPointList());
	    WrittenPoint previousPoint = (WrittenPoint)pointIter.next();
    	while(pointIter.hasNext()) {
    		WrittenPoint nextPoint = (WrittenPoint)pointIter.next();
    		painter.drawLine(previousPoint.getX(), previousPoint.getY(), nextPoint.getX(), nextPoint.getY());
    		previousPoint = nextPoint;
    	}
	}
}

