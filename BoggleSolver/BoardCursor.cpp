#include "stdafx.h"
#include "BoardCursor.h"

BoardCursor::BoardCursor(Board* board):
	mBoard(board),
	mPosition(nullptr),
	mLetter(nullptr)
{
}

BoardCursor::~BoardCursor()
{
	delete mPosition;
}


void BoardCursor::Reset()
{
	mPosition = nullptr;
	mPriorPositions.clear();
	mLetter = nullptr;
	mPriorLetters.clear();
}

bool BoardCursor::StartFrom(int x, int y)
{
	if(mBoard->ValidIndex(x, y))
	{
		Reset();
		mPosition = new Position();
		mPosition->x = x;
		mPosition->y = y;

		mLetter = new char(mBoard->AtGridLoc(x, y));
		return true;
	}

	return false;
}

bool BoardCursor::Move(Direction direction)
{
	if(mPosition && mLetter)
	{
		Position* newPosition = new Position();
		newPosition->x = mPosition->x;
		newPosition->y = mPosition->y;
		switch (direction)
		{
		case Up:
			newPosition->y -= 1;
			break;
		case UpLeft:
			newPosition->y -= 1;
			newPosition->x -= 1;
			break;
		case UpRight:
			newPosition->y -= 1;
			newPosition->x += 1;
			break;
		case Down:
			newPosition->y += 1;
			break;
		case DownLeft:
			newPosition->y += 1;
			newPosition->x -= 1;
		case DownRight:
			newPosition->y += 1;
			newPosition->x += 1;
			break;
		case Left:
			newPosition->x -= 1;
			break;
		case Right:
			newPosition->x += 1;
			break;
		}
		if (mBoard->ValidIndex(newPosition->x, newPosition->y))
		{
			// Cannot repeat a position. Possibly an optimization target. Hashset?
			for(Position* pos : mPriorPositions)
			{
				if(*pos == *newPosition)
				{
					delete newPosition;
					return false;
				}
			}

			mPriorPositions.push_back(mPosition);
			mPriorLetters.push_back(mLetter);
			
			mPosition = newPosition;
			mLetter = new char(mBoard->AtGridLoc(mPosition->x, mPosition->y));
			return true;
		}

		delete newPosition;
		return false;
	}

	return false;
}

bool BoardCursor::Pop()
{
	if(mPriorPositions.size() > 0 && mPriorLetters.size() > 0)
	{
		delete mPosition;
		delete mLetter;

		mPosition = mPriorPositions.back();
		mPriorPositions.pop_back();
		mLetter = mPriorLetters.back();
		mPriorLetters.pop_back();

		return true;
	}

	return false;
}

char* BoardCursor::GetWord()
{
	if(mPosition && mLetter)
	{
		int length = 1;
		length += mPriorLetters.size();
		char* word = new char[length+1];
		
		word[length] = '\0';
		word[length-1] = *mLetter;

		int currentIndex = 0;
		for(char* thisChar : mPriorLetters)
		{
			word[currentIndex] = *thisChar;
			currentIndex++;
		}

		return word;
	}

	return nullptr;
}






