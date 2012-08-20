#include "characterdisplaypanel.hpp"
#include "unihan.hpp"
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>

CharacterDisplayPanel::CharacterDisplayPanel() {
	QGridLayout* grid = new QGridLayout(this);
	// Label: Hanzi
	QLabel* lbl_hz = new QLabel(this);
	lbl_hz->setText("Hanzi:");
	lbl_hz->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
	grid->addWidget(lbl_hz, 0, 0, 1, 1);
	// Field: Hanzi
	rs_hz = new QLineEdit(this);
	rs_hz->setReadOnly(true);
	// --- increase the font size
	QFont f = rs_hz->font();
	f.setPixelSize(38);
	rs_hz->setFont(f);
	grid->addWidget(rs_hz, 0, 1, 1, 1);
	// Label: Radical
	QLabel* lbl_rad = new QLabel(this);
	lbl_rad->setText("Radical:");
	lbl_rad->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
	grid->addWidget(lbl_rad, 1, 0, 1, 1);
	// Field: Radical
	rs_rad = new QLineEdit(this);
	rs_rad->setReadOnly(true);
	grid->addWidget(rs_rad, 1, 1, 1, 1);
	// Label: Extra Strokes
	QLabel* lbl_es = new QLabel(this);
	lbl_es->setText("Extra Strokes:");
	lbl_es->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
	grid->addWidget(lbl_es, 2, 0, 1, 1);
	// Field: Extra Strokes
	rs_es = new QLineEdit(this);
	rs_es->setReadOnly(true);
	grid->addWidget(rs_es, 2, 1, 1, 1);
	// Label: Total Strokes
	QLabel* lbl_ts = new QLabel(this);
	lbl_ts->setText("Total Strokes:");
	lbl_ts->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
	grid->addWidget(lbl_ts, 3, 0, 1, 1);
	// Field: Total Strokes
	rs_ts = new QLineEdit(this);
	rs_ts->setReadOnly(true);
	grid->addWidget(rs_ts, 3, 1, 1, 1);
	// Label: Definition
	QLabel*  lbl_def = new QLabel(this);
	lbl_def->setText("Definition:");
	lbl_def->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
	grid->addWidget(lbl_def, 4, 0, 1, 1);
	// Field: Definition
	rs_def = new QLineEdit(this);
	rs_def->setReadOnly(true);
	grid->addWidget(rs_def, 4, 1, 1, 1);
	// Label: Pinyin/Mandarin
	QLabel* lbl_py = new QLabel(this);
	lbl_py->setText("Pinyin:");
	lbl_py->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
	grid->addWidget(lbl_py, 5, 0, 1, 1);
	// Field: Pinyin/Mandarin
	rs_py = new QLineEdit(this);
	rs_py->setReadOnly(true);
	grid->addWidget(rs_py, 5, 1, 1, 1);
	// Label: Cangjie
	QLabel* lbl_cj = new QLabel(this);
	lbl_cj->setText("Cangjie:");
	lbl_cj->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
	grid->addWidget(lbl_cj, 6, 0, 1, 1);
	// Field: Cangjie
	rs_cj = new QLineEdit(this);
	rs_cj->setReadOnly(true);
	grid->addWidget(rs_cj, 6, 1, 1, 1);
	// Label: HSK Level
	QLabel* lbl_hsk = new QLabel(this);
	lbl_hsk->setText("HSK Level:");
	lbl_hsk->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
	grid->addWidget(lbl_hsk, 7, 0, 1, 1);
	// Field: HSK Level
	rs_hsk = new QLineEdit(this);
	grid->addWidget(rs_hsk, 7, 1, 1, 1);
	rs_hsk->setReadOnly(true);
	// Label: Frequency
	QLabel* lbl_fq = new QLabel(this);
	lbl_fq->setText("Frequency:");
	lbl_fq->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
	grid->addWidget(lbl_fq, 8, 0, 1, 1);
	// Field: Frequency
	rs_fq = new QLineEdit(this);
	rs_fq->setReadOnly(true);
	grid->addWidget(rs_fq, 8, 1, 1, 1);
}

void CharacterDisplayPanel::clear() {
	rs_hz->clear();
	rs_rad->clear();
	rs_es->clear();
	rs_ts->clear();
	rs_def->clear();
	rs_py->clear();
	rs_cj->clear();
	rs_hsk->clear();
	rs_fq->clear();
}

void CharacterDisplayPanel::setCharacter(uint c) {
	clear();
	if(c == 0) return;

	QString hanzi =  QString::fromUcs4(&c, 1);

	QString query = "select \
			kRSUnicodeTable.radicalIndex,\
			kRSUnicodeTable.additionalStrokeCount,\
			kTotalStrokesTable.kTotalStrokes,\
			kDefinitionTable.kDefinition,\
			kMandarinTable.kMandarin,\
			kCangjieTable.kCangjie,\
			kGradeLevelTable.kGradeLevel,\
			kFrequencyTable.kFrequency\
		from utf8Table\
		left join kRSUnicodeTable on kRSUnicodeTable.code = utf8Table.code\
		left join kTotalStrokesTable on kTotalStrokesTable.code = utf8Table.code\
		left join kDefinitionTable on kDefinitionTable.code = utf8Table.code\
		left join kCangjieTable on kCangjieTable.code = utf8Table.code\
		left join kFrequencyTable on kFrequencyTable.code = utf8Table.code\
		left join kMandarinTable on kMandarinTable.code = utf8Table.code\
		left join kGradeLevelTable on kGradeLevelTable.code = utf8Table.code\
			where utf8Table.utf8 == \"" + hanzi + "\"";

	SQL_Result* res = unihanSql_get_sql_result(query.toUtf8().constData());

	//if(res->resultList->len == 8) {
		rs_hz->setText(hanzi);

		uint rad = QString(QString::fromUtf8(stringList_index(res->resultList,0))).toInt() + 0x2f00 - 1;
		rs_rad->setText(QString::fromUcs4(&rad,1));
		rs_es->setText(QString::fromUtf8(stringList_index(res->resultList,1)));
		rs_ts->setText(QString::fromUtf8(stringList_index(res->resultList,2)));
		rs_def->setText(QString::fromUtf8(stringList_index(res->resultList,3)));
		rs_py->setText(QString::fromUtf8(stringList_index(res->resultList,4)));
		rs_cj->setText(QString::fromUtf8(stringList_index(res->resultList,5)));
		rs_hsk->setText(QString::fromUtf8(stringList_index(res->resultList,6)));
		rs_fq->setText(QString::fromUtf8(stringList_index(res->resultList,7)));
	//b}

	sql_result_free(res, true);
}
