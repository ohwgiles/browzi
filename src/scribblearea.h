/// scribblearea.h
/// This file is part of Plain Hanzi Editor (PHE):
/// http://qt-apps.org/content/show.php/PHE+-+Plain+Hanzi+Editor?content=100586
/// It is used in Browzi under the terms of the GPL, under which PHE is released.
/// Plain Hanzi Editor appears to be Copyright 2009 Alex Novichkov.
/// Specific copyright and licensing details were unforthcoming at the
/// time of this file's inclusion in Browzi.
/// Modifications to this file from its original are Copyright 2012 Oliver Giles
#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

#include <QColor>
#include <QPoint>
#include <QFrame>

#include "writtencharacter.h"
#include "writtenpoint.h"
#include "writtenstroke.h"

class ScribbleArea : public QFrame
{
    Q_OBJECT
signals:
    void strokeAdded();
public:
   ScribbleArea(QWidget *parent = 0);
    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);
    QSize sizeHint() const;
    QColor penColor() const { return myPenColor; }
    int penWidth() const { return myPenWidth; }

    WrittenCharacter getCharacter() {return inputCharacter;}

public slots:
    void clear();
    void undo();
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
private:
    bool scribbling;
    int myPenWidth;
    QColor myPenColor;

    WrittenCharacter inputCharacter;
    WrittenStroke currentStroke;
    WrittenPoint previousPoint;
};

#endif
