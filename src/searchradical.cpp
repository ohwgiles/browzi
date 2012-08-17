#include "searchradical.hpp"
#include "rowedlist.hpp"

extern "C" {
#include <libUnihan/Unihan.h>
}

#include <iostream>

SearchRadical::SearchRadical(RowedList& rads,RowedList& cand, QObject* parent) :
	QObject(parent), rads(rads), cand(cand)
{unihanDb_open_default();/*
	std::cout << "here" << std::endl;
	unihanDb_open_default(); //todo errors
	UnihanField* r = unihanTable_get_fields(UNIHAN_TABLE_KRSUNICODE);
	for(int i=0; r[i] != UNIHAN_INVALID_FIELD; ++i) {
		std::cout << *r << std::endl;
		std::cout << unihanField_to_string(r[i]) << std::endl;
	}
	g_free(r);*/
setlocale(LC_CTYPE, "zh_CN.UTF-8");
	char rad[1024] = "|";
	char *rp = &rad[1];
	wchar_t wcs_radical[] = L"";
	for(int i=0; i < 214; ++i) {
	wcs_radical[0] = 0x2f00 + i;//sqlite3_column_int(stmt_radicals, 1);
	rp += wcstombs(rp, wcs_radical, 4);
	}/*
	for(int i=0; i < 116; ++i) {
	wcs_radical[0] = 0x2e80 + i;//sqlite3_column_int(stmt_radicals, 1);
	rp += wcstombs(rp, wcs_radical, 4);
	}*/
	std::cout << rad << std::endl;
	QStringList p;
	p << QString::fromUtf8(rad, rp-rad);
	rads.setItems(p);
	connect(&rads, SIGNAL(characterSelected(QString)), this, SLOT(radicalChosen(QString)));
	connect(&cand, SIGNAL(characterSelected(QString)), this, SLOT(disambiguated(QString)));
}

void SearchRadical::radicalChosen(QString s) {
	// get radical number from string
	uint radicalNumber = s.toUcs4()[0] - 0x2f00 + 1;
	cand.clear();
	std::cout << "fetching data for radical: " << radicalNumber << std::endl;
	// First, get the number of possible additional strokes
	QList<uint> extraStrokes;
	{
		QString query = "select additionalStrokeCount from kRSUnicodeTable where radicalIndex = " + QString::number(radicalNumber) + " group by additionalStrokeCount";
		SQL_Result* res = unihanSql_get_sql_result(query.toAscii().constData());
		for(int i = 0; i < res->resultList->len; ++i) {
			extraStrokes.append(QString(stringList_index(res->resultList, i)).toInt());
		}
		sql_result_free(res, true);
		qSort(extraStrokes);
	}

	// Now for each possible number of extra strokes, assemble the list of candidates
	//QStringList candidates;
	candidates.clear();
	{
		foreach(uint s, extraStrokes) {
			QString query = "select utf8 from utf8Table inner join kRSUnicodeTable on kRSUnicodeTable.code=utf8Table.code where kRSUnicodeTable.radicalIndex = " + QString::number(radicalNumber) + " and krsUnicodeTable.additionalStrokeCount = " + QString::number(s);
			SQL_Result* res = unihanSql_get_sql_result(query.toAscii().constData());
			QString chars = QString::number(s) + "|";
			for(int i = 0; i < res->resultList->len; ++i) {
				chars.append(QString::fromUtf8(stringList_index(res->resultList, i)));
			}
			sql_result_free(res, true);
			candidates << chars;
		}
	}
	std::cout << "Setting candidates" << std::endl;
	cand.setItems(candidates);
}

void SearchRadical::disambiguated(QString s) {
	// get char number from string
	emit showCharacter(s.toUcs4()[0]);
}

SearchRadical::~SearchRadical() {
	unihanDb_close();
}
