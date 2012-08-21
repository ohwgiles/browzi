#include "searchenglish.hpp"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QTreeWidget>
#include <QHeaderView>
#include "unihan.hpp"

SearchEnglish::SearchEnglish() {
	QVBoxLayout* vtLayout = new QVBoxLayout(this);

	QLabel* englishWordLabel = new QLabel(this);
	englishWordLabel->setText("English word:");
	vtLayout->addWidget(englishWordLabel);

	QLineEdit* englishWord = new QLineEdit(this);
	vtLayout->addWidget(englishWord);

	QLabel* disambiguateLabel = new QLabel(this);
	disambiguateLabel->setText("Disambiguate:");
	vtLayout->addWidget(disambiguateLabel);

	candidates = new QTreeWidget(this);
	candidates->setColumnCount(3);
	candidates->setObjectName(QString::fromUtf8("en_results"));
	candidates->setColumnCount(3);
	candidates->header()->hide();
	candidates->setRootIsDecorated(false);
	vtLayout->addWidget(candidates);

	connect(englishWord, SIGNAL(textEdited(QString)), this, SLOT(searchTermModified(QString)));
	connect(candidates, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), this, SLOT(entrySelected(QTreeWidgetItem*,QTreeWidgetItem*)));
}

void SearchEnglish::searchTermModified(QString s) {
	candidates->clear();
	if(s.length() < 3) return;

	QString query = "select kMandarinTable.kMandarin,\
			utf8Table.utf8,\
			kDefinition\
			from kDefinitionTable \
			join kMandarinTable on kMandarinTable.code = kDefinitionTable.code \
			join utf8Table on utf8Table.code = kDefinitionTable.code \
			where kDefinition like \"%" + s.toLower() + "%\"\
			order by kMandarinTable.kMandarin";
	SQL_Result* res = unihanSql_get_sql_result(query.toAscii().constData());

	QList<QTreeWidgetItem *> items;
	for(int i = 0; i < res->resultList->len; i+=3) {
		QStringList cols;
		cols << QString::fromUtf8(stringList_index(res->resultList, i))
			  << QString::fromUtf8(stringList_index(res->resultList, i + 1))
			  << QString::fromUtf8(stringList_index(res->resultList, i + 2));
		items.append(new QTreeWidgetItem((QTreeWidget*)0, cols));
	}
	candidates->insertTopLevelItems(1, items);
	candidates->resizeColumnToContents(0);
	candidates->resizeColumnToContents(1);
	sql_result_free(res, true);
}

void SearchEnglish::entrySelected(QTreeWidgetItem* newItem,QTreeWidgetItem*) {
	disambiguated( newItem->data(1, Qt::DisplayRole).toString());
}
