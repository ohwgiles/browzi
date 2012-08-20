#include "searchstrokecount.hpp"
#include <QSpinBox>
#include "rowedlist.hpp"
#include <QScrollArea>

#include "unihan.hpp"
#include <QLabel>
#include <QVBoxLayout>

SearchStrokeCount::SearchStrokeCount(QWidget *parent) : SearchPanel(parent) {
	QVBoxLayout* vtLayout = new QVBoxLayout(this);
	QHBoxLayout* hzLayout = new QHBoxLayout();

	QLabel* numStrokesLabel = new QLabel(this);
	numStrokesLabel->setText("Number of Strokes:");
	hzLayout->addWidget(numStrokesLabel);

	QSpinBox* numStrokes = new QSpinBox(this);
	numStrokes->setMinimum(1);
	numStrokes->setMaximum(32);
	hzLayout->addWidget(numStrokes);

	vtLayout->addLayout(hzLayout);

	QLabel* disambiguateLabel = new QLabel(this);
	disambiguateLabel->setText("Disambiguate:");
	vtLayout->addWidget(disambiguateLabel);

	QScrollArea* candidatesScrollArea = new QScrollArea(this);
	candidatesScrollArea->setObjectName(QString::fromUtf8("sc_sw"));
	candidatesScrollArea->setWidgetResizable(true);
	vtLayout->addWidget(candidatesScrollArea);

	candidates = new RowedList(candidatesScrollArea);
	candidatesScrollArea->setWidget(candidates);
	candidatesScrollArea->setWidgetResizable(true);

	connect(numStrokes, SIGNAL(valueChanged(int)), this, SLOT(strokesChanged(int)));
	connect(candidates, SIGNAL(characterSelected(QString)), this, SLOT(disambiguate(QString)));

	numStrokes->setValue(1);
	strokesChanged(1);
}

void SearchStrokeCount::strokesChanged(int s) {
	QString result = "|";
	QString query = "select utf8 from utf8Table join kTotalStrokesTable on kTotalStrokesTable.code == utf8Table.code where kTotalStrokesTable.kTotalStrokes = " + QString::number(s);
	SQL_Result* res = unihanSql_get_sql_result(query.toAscii().constData());
	for(int i = 0; i < res->resultList->len; ++i) {
		result.append(QString::fromUtf8(stringList_index(res->resultList, i)));
	}
	sql_result_free(res, true);
	QStringList l;
	l << result;
	candidates->setItems(l);
}

void SearchStrokeCount::disambiguate(QString s) {
	charChosen(s.toUcs4()[0]);
}
