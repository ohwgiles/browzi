#include "searchenglish.hpp"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QTreeWidget>
#include <QHeaderView>

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

	QTreeWidget* candidates = new QTreeWidget(this);
	candidates->setColumnCount(3);
	candidates->setObjectName(QString::fromUtf8("en_results"));
	candidates->setColumnCount(3);
//	candidates->horizontalHeader()->setStretchLastSection(true);

	vtLayout->addWidget(candidates);
}
