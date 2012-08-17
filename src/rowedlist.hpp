#ifndef ROWEDLIST_H
#define ROWEDLIST_H

#include <QColor>
#include <QFont>
#include <QFontMetrics>
#include <QWidget>
#include <QStringList>
#include <QPair>
#include <QPen>

class RowedList : public QWidget
{
	Q_OBJECT
public:
	RowedList(QWidget *parent = 0);
	QFont font() { return curFont; }
	int rowHeight() const { return curRowHeight; }
	int headerWidth() const { return curHeaderWidth; }
	int cellWidth() const { return curCellWidth; }
	QStringList getItems() {return fullItems;}
	virtual int heightForWidth( int width ) const;
	virtual QSize sizeHint() const;
	bool missingCharacters() const {return showMissing;}

public slots:
	void clear();
	void setFont(const QFont &newFont);
	void setRowHeight(int newRowHeight);
	void setHeaderWidth(int newHeaderWidth);
	void setCellWidth(int newCellWidth);
	void setItems(const QStringList &);
	void setShowMissingCharacters(bool showMissing);

signals:
	void characterSelected(const QString &);
	void characterHovered(const QChar &);
protected:
	void mousePressEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);
private:
	QFont curFont;
	QFont curHeaderFont;
	int curCount;
	int curRowHeight;
	int curCellWidth;
	int curHeaderWidth;
	bool showMissing;
	QStringList headers;
	QStringList items;
	QStringList fullItems;
	QStringList newItems;
	int numberOfCols;
	int numberOfRows;
	QPair<int,int> lastKey;
	int getActualRow(int i);
	int getActualCol(int i,int j,int i2);
	void res(int);
	QString lastHeader;
	QPen pen;
	QPen pen1;
};
#endif

