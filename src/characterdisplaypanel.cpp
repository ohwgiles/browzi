/**************************************************************************
 *
 *  characterdisplaypanel.cpp
 *  Copyright 2012 Oliver Giles
 *
 *  This file is part of Browzi.
 *
 *  Browzi is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Browzi is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Browzi.  If not, see <http://www.gnu.org/licenses/>.
 *
 **************************************************************************/
#include "characterdisplaypanel.hpp"
#include <QGridLayout>
#include <QLabel>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <sqlite3.h>

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
	rs_def = new QPlainTextEdit(this);
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

	stmt = createStatement(
				"select \
				kRSUnicodeTable.radicalIndex,\
				kRSUnicodeTable.additionalStrokeCount,\
				kTotalStrokesTable.kTotalStrokes,\
				kDefinitionTable.kDefinition,\
				kCangjieTable.kCangjie,\
				kGradeLevelTable.kGradeLevel,\
				kFrequencyTable.kFrequency\
			from utf8Table\
			left join kRSUnicodeTable on kRSUnicodeTable.code = utf8Table.code\
			left join kTotalStrokesTable on kTotalStrokesTable.code = utf8Table.code\
			left join kDefinitionTable on kDefinitionTable.code = utf8Table.code\
			left join kCangjieTable on kCangjieTable.code = utf8Table.code\
			left join kFrequencyTable on kFrequencyTable.code = utf8Table.code\
			left join kGradeLevelTable on kGradeLevelTable.code = utf8Table.code\
			where utf8Table.utf8 == ?;");
	pinyinStmt = createStatement(
				"select \
				kMandarin\
			from kMandarinTable\
			join utf8Table on kMandarinTable.code = utf8Table.code\
			where utf8Table.utf8 == ?;");
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
	QString hanzi = QString::fromUcs4(&c, 1);

	sqlite3_bind_text(stmt, 1, hanzi.toUtf8().constData(), -1, SQLITE_TRANSIENT);
	if(sqlite3_step(stmt) == SQLITE_ROW) {
		rs_hz->setText(hanzi);
		uint rad = sqlite3_column_int(stmt,0) + 0x2f00 - 1;
		rs_rad->setText(QString::fromUcs4(&rad,1));
		rs_es->setText(QString::fromUtf8((const char*)sqlite3_column_text(stmt,1),sqlite3_column_bytes(stmt,1)));
		rs_ts->setText(QString::fromUtf8((const char*)sqlite3_column_text(stmt,2),sqlite3_column_bytes(stmt,2)));
		rs_def->document()->setPlainText(QString::fromUtf8((const char*)sqlite3_column_text(stmt,3),sqlite3_column_bytes(stmt,3)));
		rs_cj->setText(QString::fromUtf8((const char*)sqlite3_column_text(stmt,4),sqlite3_column_bytes(stmt,4)));
		rs_hsk->setText(QString::fromUtf8((const char*)sqlite3_column_text(stmt,5),sqlite3_column_bytes(stmt,5)));
		rs_fq->setText(QString::fromUtf8((const char*)sqlite3_column_text(stmt,6),sqlite3_column_bytes(stmt,6)));
	}
	sqlite3_reset(stmt);

	sqlite3_bind_text(pinyinStmt, 1, hanzi.toUtf8().constData(), -1, SQLITE_TRANSIENT);
	QString pinyins;
	while(sqlite3_step(pinyinStmt) == SQLITE_ROW) {
		pinyins += QString::fromUtf8((const char*)sqlite3_column_text(pinyinStmt,0),sqlite3_column_bytes(pinyinStmt,0));
		pinyins += ", ";
	}
	pinyins.chop(2);
	rs_py->setText(pinyins);
	sqlite3_reset(pinyinStmt);
}
