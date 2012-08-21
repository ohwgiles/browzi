#ifndef SEARCHDRAW_HPP
#define SEARCHDRAW_HPP
#include "searchpanel.hpp"

class ScribbleArea;
class RowedList;

class SearchDraw : public SearchPanel {
	Q_OBJECT
public:
	SearchDraw();
private slots:
	void searchHandwritten();
private:
	ScribbleArea* canvasDraw;
	RowedList* candidates;
};

#endif // SEARCHDRAW_HPP
