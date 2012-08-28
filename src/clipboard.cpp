#include "clipboard.hpp"
#include "rowedlist.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include <QApplication>
#include <QClipboard>

Clipboard::Clipboard()
{
	QVBoxLayout* vtLayout = new QVBoxLayout(this);
	QLabel* clipboardLabel = new QLabel(this);
	clipboardLabel->setText("Clipboard Contents:");
	vtLayout->addWidget(clipboardLabel);

	QScrollArea* clipboardScrollArea = new QScrollArea(this);
	QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(clipboardScrollArea->sizePolicy().hasHeightForWidth());
	clipboardScrollArea->setSizePolicy(sizePolicy);
	clipboardScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	clipboardScrollArea->setWidgetResizable(true);

	clipboard = new RowedList(font(), false, clipboardScrollArea);
	clipboardScrollArea->setWidget(clipboard);
	clipboardScrollArea->setWidgetResizable(true);

	vtLayout->addWidget(clipboardScrollArea);

	connect(clipboard, SIGNAL(characterSelected(QString)), this, SLOT(disambiguated(QString)));
	connect(QApplication::clipboard(), SIGNAL(dataChanged()), this, SLOT(newClipboardText()));
	newClipboardText();
}

void Clipboard::newClipboardText() {
	QString contents = "|" + QApplication::clipboard()->text();
	QStringList l;
	l << contents;
	clipboard->setItems(l);
}

void Clipboard::setChineseFont(const QFont & f) {
	clipboard->setFont(f);
}
