#ifndef SEARCHPANEL_HPP
#define SEARCHPANEL_HPP

#include <QWidget>
class CharacterDisplayPanel;

class SearchPanel : public QWidget {
	Q_OBJECT
public:
	SearchPanel(QWidget *parent = 0);

	//void charChosen(uint);
	uint lastChar() const { return lastCharacter; }
private:
	uint lastCharacter;

signals:
	void showCharacter(uint);
protected slots:
	void disambiguated(QString);
};

#endif // SEARCHPANEL_HPP
