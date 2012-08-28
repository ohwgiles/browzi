#ifndef CLIPBOARD_HPP
#define CLIPBOARD_HPP

#include "searchpanel.hpp"

class RowedList;

class Clipboard : public SearchPanel
{
	Q_OBJECT
public:
	Clipboard();
private:
	RowedList* clipboard;
	void setChineseFont(const QFont &);
public slots:
	void newClipboardText();
};

#endif // CLIPBOARD_HPP
