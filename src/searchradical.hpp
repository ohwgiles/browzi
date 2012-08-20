#ifndef SEARCHRADICAL_HPP
#define SEARCHRADICAL_HPP

#include "searchpanel.hpp"

class RowedList;
class QScrollArea;

class SearchRadical : public SearchPanel {
	Q_OBJECT
public:
	SearchRadical(QWidget* parent);
	virtual ~SearchRadical();
private:
	RowedList* listRadicals;
	RowedList* listCandidates;

private slots:
	void radicalChosen(QString);
	void disambiguated(QString);
};

#endif // SEARCHRADICAL_HPP
