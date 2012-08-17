#ifndef CHARACTERDISPLAYPANEL_HPP
#define CHARACTERDISPLAYPANEL_HPP

#include <QObject>

namespace Ui {
class MainWindow;
}

class CharacterDisplayPanel : public QObject
{
	Q_OBJECT
public:
	CharacterDisplayPanel(Ui::MainWindow& ui);

public slots:
	void setCharacter(uint);
	void clear();

private:
	Ui::MainWindow& ui;
};

#endif // CHARACTERDISPLAYPANEL_HPP
