#pragma once
#include "stdafx.h"
#include <vector>


struct Position
{
	int x;
	int y;

	bool operator==(Position other) const
	{
		if(other.x == x && other.y == y)
		{
			return true;
		}
		return false;
	}
};

enum Direction
{
	Up,
	Down,
	Left,
	Right
};

class BoardCursor
{
private:
	const Board* mBoard;

	Position* mPosition;
	std::vector<Position*> mPriorPositions;
	
	char* mLetter;
	std::vector<char*> mPriorLetters;

public:
	BoardCursor(Board* board);
	~BoardCursor();

	void Reset();
	bool StartFrom(int x, int y);
	bool Move(Direction direction);
	bool Pop();

	char* GetWord();
	char* GetLetter()
	{
		if(mLetter)
		{
			char* theLetter = new char[2];
			theLetter[0] = mLetter[0];
			theLetter[1] = '\0';
			return theLetter;
		}
		return nullptr;
	};
};
