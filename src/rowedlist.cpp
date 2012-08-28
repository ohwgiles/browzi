/// rowedlist.cpp
/// This file is part of Plain Hanzi Editor (PHE):
/// http://qt-apps.org/content/show.php/PHE+-+Plain+Hanzi+Editor?content=100586
/// It is used in Browzi under the terms of the GPL, under which PHE is released.
/// Plain Hanzi Editor appears to be Copyright 2009 Alex Novichkov.
/// Specific copyright and licensing details were unforthcoming at the
/// time of this file's inclusion in Browzi.
/// Modifications to this file from its original are Copyright 2012 Oliver Giles
#include <QtGui>
#include "rowedlist.h"

RowedList::RowedList(const QFont &font,bool b,QWidget *parent)
        : QWidget(parent),curFont(font),  showMissing(b) 
{
    curHeaderFont=parent->font();
    pen1.setBrush(Qt::gray);
    pen1.setStyle(Qt::DotLine);
    
    //QPen pen1(Qt::gray, 1, Qt::DotLine, Qt::SquareCap, Qt::BevelJoin);
    QVector<qreal> dashes;
    dashes << 3.0 << 1.0;
    pen1.setDashPattern(dashes);

    //определяем высоту строки согласно шрифту
    QFontMetrics fm(curFont);
    curRowHeight=fm.height()+3;
    curCellWidth=curRowHeight;
    curHeaderWidth=0;
    numberOfCols=(int)(width() / curCellWidth);
    numberOfRows=(int)(height()/curRowHeight);
    curCount=0;
    lastKey = qMakePair(-1,-1);
    lastHeader="";
    fullItems.clear();
    newItems.clear();
    QSizePolicy policy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    policy.setHeightForWidth(true);
    setSizePolicy(policy);
}

int RowedList::heightForWidth( int /*width */) const
{
    return curRowHeight*numberOfRows+3;
}


QSize RowedList::sizeHint() const
{
    int w = curHeaderWidth+3+numberOfCols*curCellWidth;
    return QSize(w,heightForWidth(w));
}

void RowedList::setShowMissingCharacters(bool showMissing)
{
    this->showMissing=showMissing;
    setItems(fullItems);
}

void RowedList::clear()
{
    QStringList l;
    setItems(l);
}

void RowedList::res(int width)
{
    numberOfCols=(width-curHeaderWidth) / curCellWidth;
    headers.clear();
    items.clear();
    if (curCount>0) {
        //int co=newItems.count();
        for (int i=0; i<curCount; i++) {
            QStringList list=newItems.at(i).split("|");
            QString header=list.at(0)+"|";
            QString s=list.at(1);
            headers.append(header);
            items.append(s.left(numberOfCols));
            s.remove(0,numberOfCols);
            while (s.length()>0) {
                headers.append("");
                items.append(s.left(numberOfCols));
                s.remove(0,numberOfCols);
            }
        }
        numberOfRows=items.count();
    }
    else numberOfRows=1;
}

void RowedList::resizeEvent(QResizeEvent *event)
{
    res(event->size().width());
    update();
}

void RowedList::setRowHeight(int newRowHeight)
{
    curRowHeight=newRowHeight;
    adjustSize();
    update();
    updateGeometry();
}

void RowedList::setCellWidth(int newCellWidth)
{
    curCellWidth=newCellWidth;
    adjustSize();
    update();
    updateGeometry();
}

void RowedList::setHeaderWidth(int newHeaderWidth)
{
    curHeaderWidth=newHeaderWidth;
    adjustSize();
    update();
    updateGeometry();
}

//меняем шрифт - проверить, чтобы все было
void RowedList::setFont(const QFont &newFont)
{
    curFont=newFont;
    QFontMetrics fm(curFont);
    curRowHeight=fm.height()+3;
    curCellWidth=curRowHeight;
	 res(size().width());
    adjustSize();
    update();
    updateGeometry();
}

void RowedList::setItems(const QStringList &list)
{
    if (fullItems!=list) fullItems=list;
    newItems.clear();
    curCount=list.count();

    if (curCount>0) {
        QFontMetrics fm(curHeaderFont);
        QFontMetrics fm1(curFont);
        //вычисляем ширину столбца заголовков
        int w=0;
        int curw=0;
        
        for (int i=0; i<curCount; i++) {
            QString s=list.at(i);
            int pos=s.indexOf("|");
            if (!showMissing) {
                int j=pos+1;
                while (j<s.length()) {
                    if (!fm1.inFont(s.at(j))) s.remove(j,1); else j++;
                }
            }
            if (s.length()>pos+1) {
                newItems.append(s);
                curw=fm.width(s.left(pos));
                if (curw>w) w=curw;
            }
        }
        curHeaderWidth=w>0?w+5:0;
    }
    curCount=newItems.count();
    lastKey = qMakePair(-1,-1);

    update();
    adjustSize();
    updateGeometry();
}

void RowedList::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);
    QRect redrawRect = event->rect();
    painter.drawRect(redrawRect.left(),redrawRect.top(),redrawRect.width(),redrawRect.height());
    if (curCount==0) return;
    //высчитываем границы перерисовываемой области
    int beginRow = redrawRect.top()/curRowHeight;
    int endRow = qMin(redrawRect.bottom()/curRowHeight,items.count()-1);

    //вертикальная линия, отделяющая заголовки
    if (curHeaderWidth>2) {
        painter.setPen(pen1);
        painter.drawLine(curHeaderWidth,redrawRect.top(),
        curHeaderWidth,redrawRect.bottom());
    }

    QFontMetrics fm(curFont);
    //заголовки
    painter.setFont(curHeaderFont);
    QString s;
    for (int i=beginRow;i<=endRow;i++) {     
        if (!headers.at(i).isEmpty()) {
            lastHeader=headers.at(i);
            painter.setPen(pen1);
            if (i>0)
            painter.drawLine(0,i*curRowHeight,
              curHeaderWidth+numberOfCols*curCellWidth,i*curRowHeight);
        }
        painter.setPen(pen);
        painter.drawText(QRect(0,i*curRowHeight,curHeaderWidth,curRowHeight),
                         Qt::AlignCenter, lastHeader.left(lastHeader.length()-1));
    }
    //остальное
    painter.setFont(curFont);
    painter.setPen(pen);
    for (int i=beginRow;i<=endRow;i++) {
        s=items.at(i);
        int i1=getActualRow(i);
        for (int j=0; j<s.length(); ++j) {
           if (lastKey.first==i1 && lastKey.second==getActualCol(i,j,i1)) {
               painter.fillRect(curHeaderWidth+j*curCellWidth+1,i*curRowHeight+1,
                    curCellWidth-1,curRowHeight-1, QApplication::palette().highlight());
           }
           QChar c=s.at(j);
           if (!fm.inFont(c)) c=QChar(QChar::ReplacementCharacter);
           painter.drawText(QRect(curHeaderWidth+j*curCellWidth,
                   i*curRowHeight+2,curCellWidth,curRowHeight),Qt::AlignCenter, c);
        }
    }
}

void RowedList::mousePressEvent(QMouseEvent *event)
{
    int y=event->y();
    int x=event->x();
    if (x<=curHeaderWidth+1 || x>=curHeaderWidth+numberOfCols*curCellWidth ||
                y>=numberOfRows*curRowHeight || curCount==0) return;
    int i=y/curRowHeight;
    int i1=getActualRow(i);
    int j=(x-curHeaderWidth)/curCellWidth;
    QStringList list=newItems.at(i1).split("|");
    int j1=list.at(1).indexOf(items.at(i))+j;
    if (j1<list.at(1).length()) {
        if (event->button() == Qt::LeftButton) {
            lastKey=qMakePair(i1,j1);
            emit characterSelected(QString(list.at(1).at(j1)));
        } else
        if (event->button() == Qt::RightButton) {
            emit characterHovered(list.at(1).at(j1));
        } else QWidget::mousePressEvent(event);
    }
    update();
}

int RowedList::getActualRow(int i)
{
    int i1=0;
    for (int qw=0;qw<=i;++qw)
            if (!headers.at(qw).isEmpty()) i1+=1;
    return --i1;
}

int RowedList::getActualCol(int i,int j,int i1)
{
    QStringList list=newItems.at(i1).split("|");
    return list.at(1).indexOf(items.at(i))+j;
}
