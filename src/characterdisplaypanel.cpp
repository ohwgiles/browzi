#include "characterdisplaypanel.hpp"
#include "ui_mainwindow.h"
extern "C" {
#include <libUnihan/Unihan.h>
}
CharacterDisplayPanel::CharacterDisplayPanel(Ui::MainWindow& ui) : ui(ui)
{
}

void CharacterDisplayPanel::clear() {
	ui.rs_rad->clear();
	ui.rs_es->clear();
	ui.rs_ts->clear();
	ui.rs_def->clear();
	ui.rs_py->clear();
	ui.rs_cj->clear();
	ui.rs_hsk->clear();
	ui.rs_fq->clear();
}

void CharacterDisplayPanel::setCharacter(uint c) {
	clear();

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

	ui.rs_hz->setText(hanzi);

	uint rad = QString(stringList_index(res->resultList,0)).toInt() + 0x2f00 - 1;
	ui.rs_rad->setText(QString::fromUcs4(&rad,1));
	ui.rs_es->setText(stringList_index(res->resultList,1));
	ui.rs_ts->setText(stringList_index(res->resultList,2));
	ui.rs_def->setText(stringList_index(res->resultList,3));
	ui.rs_py->setText(stringList_index(res->resultList,4));
	ui.rs_cj->setText(stringList_index(res->resultList,5));
	ui.rs_hsk->setText(stringList_index(res->resultList,6));
	ui.rs_fq->setText(stringList_index(res->resultList,7));

	sql_result_free(res, true);
}
