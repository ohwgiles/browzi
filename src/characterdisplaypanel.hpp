#ifndef CHARACTERDISPLAYPANEL_HPP
#define CHARACTERDISPLAYPANEL_HPP

#include <QWidget>

class QLineEdit;

class CharacterDisplayPanel : public QWidget {
	Q_OBJECT
public:
	CharacterDisplayPanel();

public slots:
	void setCharacter(uint);
	void clear();

private:
	QLineEdit* rs_hz;
	QLineEdit* rs_rad;
	QLineEdit* rs_es;
	QLineEdit* rs_ts;
	QLineEdit* rs_def;
	QLineEdit* rs_py;
	QLineEdit* rs_cj;
	QLineEdit* rs_hsk;
	QLineEdit* rs_fq;

};

#endif // CHARACTERDISPLAYPANEL_HPP
