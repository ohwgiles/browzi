#include "searchpanel.hpp"

#include "characterdisplaypanel.hpp"

SearchPanel::SearchPanel(QWidget *parent) :
	QWidget(parent),
	lastCharacter(0)
{
}

void SearchPanel::disambiguated(QString s) {
	lastCharacter = s.toUcs4()[0];
	emit showCharacter(lastCharacter);
}

