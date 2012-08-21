#ifndef SEARCHENGLISH_HPP
#define SEARCHENGLISH_HPP
#include "searchpanel.hpp"
class QTreeWidget;
class QTreeWidgetItem;
class SearchEnglish : public SearchPanel
{
	Q_OBJECT
public:
	SearchEnglish();

private slots:
	void searchTermModified(QString);
	void entrySelected(QTreeWidgetItem*,QTreeWidgetItem*);

private:
	QTreeWidget* candidates;
};

#endif // SEARCHENGLISH_HPP
