#ifndef SEARCHSTROKECOUNT_HPP
#define SEARCHSTROKECOUNT_HPP

#include "searchpanel.hpp"

class RowedList;

class QSpinBox;
class QScrollArea;

class SearchStrokeCount : public SearchPanel
{
	Q_OBJECT
public:
	SearchStrokeCount(QWidget *parent = 0);

private:
	RowedList* candidates;
private slots:
	void strokesChanged(int);
	//void disambiguate(QString);
};

#endif // SEARCHSTROKECOUNT_HPP
