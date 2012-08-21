#ifndef CHARACTERDESCRIPTOR_H
#define CHARACTERDESCRIPTOR_H

#include <QList>
#include <QChar>

class CharacterDescriptor
{
public:
    CharacterDescriptor(QList<int> subStrokes)
        : substrokes(subStrokes) {}
    CharacterDescriptor() {}
    QChar getCharacter() {return this->character;}
    void setCharacter(QChar character) {this->character = character;	}
    int getStrokeCount() {return this->strokeCount;}
    void setStrokeCount(int strokeCount) {this->strokeCount = strokeCount;}
	QList<int> getSubStrokes() {return this->substrokes;}
	void setSubStrokes(QList<int> subStrokes) {this->substrokes=subStrokes;}
private:
    QChar character;
	int strokeCount;
	QList<int> substrokes;
};

#endif

