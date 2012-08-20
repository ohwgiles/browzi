#include "searchdraw.hpp"
#include "rowedlist.hpp"
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>

SearchDraw::SearchDraw() {
	QVBoxLayout* vtLayout = new QVBoxLayout(this);
	QHBoxLayout* hzCanvasLayout = new QHBoxLayout();

	QSpacerItem* spCanvasLeft = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	hzCanvasLayout->addItem(spCanvasLeft);

	QVBoxLayout* vtCanvasLayout = new QVBoxLayout();
	QLabel* canvasDrawLabel = new QLabel(this);
	canvasDrawLabel->setText("Draw:");
	vtCanvasLayout->addWidget(canvasDrawLabel);

	QWidget* canvasDraw = new QWidget(this);
	canvasDraw->setMinimumSize(QSize(256, 256));
	canvasDraw->setMaximumSize(QSize(256, 256));
	canvasDraw->setAutoFillBackground(false);
	vtCanvasLayout->addWidget(canvasDraw);

	hzCanvasLayout->addLayout(vtCanvasLayout);

	QSpacerItem* spCanvasRight = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	hzCanvasLayout->addItem(spCanvasRight);

	vtLayout->addLayout(hzCanvasLayout);

	QLabel*disambiguateLabel = new QLabel(this);
	disambiguateLabel->setText("Disambiguate:");
	vtLayout->addWidget(disambiguateLabel);

	RowedList* candidates = new RowedList(this);
	vtLayout->addWidget(candidates);
}
