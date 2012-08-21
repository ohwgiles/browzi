#ifndef SEARCHPINYIN_HPP
#define SEARCHPINYIN_HPP
#include "searchpanel.hpp"

class RowedList;

class SearchPinyin : public SearchPanel
{
	Q_OBJECT
public:
	SearchPinyin();
private:
	RowedList* candidates;
private slots:
	void searchTermChanged(QString s);
};

#endif // SEARCHPINYIN_HPP
