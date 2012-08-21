#include "searchpinyin.hpp"
#include "rowedlist.hpp"
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLineEdit>
#include <QLabel>
#include "unihan.hpp"

SearchPinyin::SearchPinyin()
{
	QVBoxLayout* vtLayout = new QVBoxLayout(this);

	QLabel* pinyinLabel = new QLabel(this);
	pinyinLabel->setText("Pinyin:");
	vtLayout->addWidget(pinyinLabel);

	QLineEdit* pinyin = new QLineEdit(this);
	vtLayout->addWidget(pinyin);

	QLabel* disambiguateLabel = new QLabel(this);
	disambiguateLabel->setText("Disambiguate:");
	disambiguateLabel->setObjectName(QString::fromUtf8("label"));
	vtLayout->addWidget(disambiguateLabel);

	QScrollArea* candidatesScrollArea = new QScrollArea(this);
	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(candidatesScrollArea->sizePolicy().hasHeightForWidth());
	candidatesScrollArea->setSizePolicy(sizePolicy);
	candidatesScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	candidatesScrollArea->setWidgetResizable(true);

	candidates = new RowedList(candidatesScrollArea);
	candidatesScrollArea->setWidget(candidates);
	candidatesScrollArea->setWidgetResizable(true);

	vtLayout->addWidget(candidatesScrollArea);

	connect(pinyin, SIGNAL(textEdited(QString)), this, SLOT(searchTermChanged(QString)));
	connect(candidates, SIGNAL(characterSelected(QString)), this, SLOT(disambiguated(QString)));
}

void SearchPinyin::searchTermChanged(QString s) {
	candidates->clear();
	if(s.isEmpty()) return;

	char first,last;
	if(s.at(s.length()-1).isNumber()) {
		first = last = s.at(s.length()-1).toAscii();
		s.chop(1);
	} else {
		first = '1';
		last = '5';
	}

	QStringList cnd;
	do {
		QString query = "select utf8 from utf8Table join \
				kMandarinTable on kMandarinTable.code = utf8Table.code \
				where kMandarinTable.kMandarin = \"" + s.toUpper() + first + "\"";
		SQL_Result* res = unihanSql_get_sql_result(query.toAscii().constData());
		QString hanzi = s + first + "|";
		for(int i = 0; i < res->resultList->len; ++i) {
			hanzi.append(QString::fromUtf8(stringList_index(res->resultList, i)));
		}
		sql_result_free(res, true);
		cnd << hanzi;
	} while(first++ != last);

	candidates->setItems(cnd);
}
