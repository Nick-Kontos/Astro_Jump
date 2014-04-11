#pragma once
#include "stdafx.h"
#include "sssf\text\TextGenerator.h"

class AstroJumpTextGenerator : public TextGenerator
{
private:
	// THIS IS THE TEXT THIS OBJECT WILL UPDATE EACH FRAME
	wstring textToGenerate;
	wstring pathfindingText;

public:
	// NOTHING TO INITIALIZE OR DESTROY
	AstroJumpTextGenerator()	{}
	~AstroJumpTextGenerator()	{}

	// DEFINED IN BugsTextGenerator.cpp
	void appendMouseCoords(Game *game);
	void appendAntRotationInfo(Game *game);
	void appendPathfindingText(Game *game);
	void initText(Game *game);
	void updateText(Game *game);
};