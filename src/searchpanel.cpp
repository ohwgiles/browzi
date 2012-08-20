#include "searchpanel.hpp"

#include "characterdisplaypanel.hpp"

SearchPanel::SearchPanel(QWidget *parent) :
	QWidget(parent),
	lastCharacter(0)
{
}

void SearchPanel::charChosen(uint c) {
	lastCharacter = c;
	emit showCharacter(c);
}
