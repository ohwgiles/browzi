#include "writtencharacter.h"
#include "writtenstroke.h"
#include <QList>

WrittenCharacter::WrittenCharacter() {
    strokeList.clear();
}

void WrittenCharacter::addStroke(WrittenStroke stroke) {
	this->strokeList.append(stroke);
}

void WrittenCharacter::clear() {
	this->strokeList.clear();
}

void WrittenCharacter::clearLastStroke() {
	this->strokeList.removeLast();
}

void WrittenCharacter::analyzeAndMark() {
    QMutableListIterator<WrittenStroke> strokeIter(strokeList);
    while (strokeIter.hasNext()) {
		WrittenStroke nextStroke = (WrittenStroke)strokeIter.next();
		if(!nextStroke.isAnalyzed()) {
			nextStroke.analyzeAndMark();
			strokeIter.setValue(nextStroke);
		}
	}
}

CharacterDescriptor WrittenCharacter::buildCharacterDescriptor()
{
	int strokeCount = this->strokeList.count();
	QList<int> strokes;
	
    for (int i=0; i<strokeCount; i++)
    {
        WrittenStroke str=strokeList.at(i);
		int type=str.getType();
        strokes.append(type);
	}
	CharacterDescriptor descriptor(strokes);
	descriptor.setStrokeCount(strokeCount);
	return descriptor;
}
