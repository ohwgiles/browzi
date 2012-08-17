#ifndef SEARCHRADICAL_HPP
#define SEARCHRADICAL_HPP

#include <QObject>
#include <QStringList>
class RowedList;

class SearchRadical : public QObject {
	Q_OBJECT
public:
	SearchRadical(RowedList& rads, RowedList& cand, QObject *parent = 0);
	virtual ~SearchRadical();
private:
	RowedList& rads;
	RowedList& cand;
QStringList candidates;
private slots:
	void radicalChosen(QString);
	void disambiguated(QString);
signals:
	void showCharacter(uint);
};

#endif // SEARCHRADICAL_HPP
