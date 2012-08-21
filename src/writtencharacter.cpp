/// writtencharacter.cpp
/// This file is part of Plain Hanzi Editor (PHE):
/// http://qt-apps.org/content/show.php/PHE+-+Plain+Hanzi+Editor?content=100586
/// It is used in Browzi under the terms of the GPL, under which PHE is released.
/// Plain Hanzi Editor appears to be Copyright 2009 Alex Novichkov.
/// Specific copyright and licensing details were unforthcoming at the
/// time of this file's inclusion in Browzi.
/// Modifications to this file from its original are Copyright 2012 Oliver Giles
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
