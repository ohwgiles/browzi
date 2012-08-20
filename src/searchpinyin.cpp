#include "searchpinyin.hpp"
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>

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

	QTreeWidget* candidates = new QTreeWidget(this);/*
	QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
	__qtreewidgetitem->setText(0, QString::fromUtf8("1"));
	treeWidget->setHeaderItem(__qtreewidgetitem);*/
	vtLayout->addWidget(candidates);

}
