#include "stdafx.h"
#include "Board.h"
#include <fstream>
#include <assert.h>

// Not entirely arbitrary this assumes the largest acceptable line is 10000 elements long.
const int kArbitraryMaxLineLength = 19999;

Board::Board():
	mBoardArray(nullptr),
	mColumns(0),
	mRows(0)
{
}

Board::Board(char * board, int columns, int rows):
	mColumns(columns),
	mRows(rows)
{
	// allow us to safely free our version.
	mBoardArray = new char[strlen(board)];
	memcpy(mBoardArray, board, strlen(board));
}

Board::~Board()
{
	if(mBoardArray)
	{
		delete mBoardArray;
	}
}

bool Board::loadFromFile(char * filePath)
{
	std::fstream stream(filePath, std::ios_base::in);
	if (stream.is_open())
	{
		char readBuffer[kArbitraryMaxLineLength];

		// read one line, count commas, get column count
		stream.getline(readBuffer, kArbitraryMaxLineLength);
		
		int firstLineLength = strlen(readBuffer);
		bool isOdd = (firstLineLength % 2) == 1;
		
		assert(isOdd);
		if(!isOdd)
		{
			return false;
		}

		// All lines are going to be odd - a line of characters 1 == "1" - a line of characters 2 == "1,2" (len 3) etc.
		mColumns = (firstLineLength / 2) + 1;

		// read all lnes, get row count
		mRows = 1;
		while(!stream.eof())
		{
			// clear buffer
			memset(readBuffer, '\0', kArbitraryMaxLineLength);
			stream.getline(readBuffer, kArbitraryMaxLineLength);
			if(strlen(readBuffer) == firstLineLength)
			{
				mRows++;
			}
			else
			{
				return false;
			}
		}

		// construct array of size column * row
		int arraySize = mColumns * mRows;
		mBoardArray = new char[arraySize];
		
		// seek head
		stream.clear();
		stream.seekg(0, std::ios::beg);
		
		// load elements
		int currentIndex = 0;
		while(!stream.eof())
		{
			memset(readBuffer, '\0', kArbitraryMaxLineLength);
			stream.getline(readBuffer, kArbitraryMaxLineLength);
			for(int i = 0; readBuffer[i] != '\0'; i++)
			{
				char thisChar = readBuffer[i];
				if (thisChar != ',')
				{
					mBoardArray[currentIndex] = thisChar;
					currentIndex++;
				}
			}
		}

		return true;
	}

	return false;
}

char Board::atGridLoc(int column, int row) const
{
	int asIndex = getGridIndex(column, row);
	return atGridIndex(asIndex);
}

char Board::atGridIndex(int index) const
{
	return mBoardArray[index];
}

int Board::getGridIndex(int column, int row) const
{
	return row * mColumns + column;
}

bool Board::validIndex(int column, int row) const
{
	return column < mColumns && row < mRows;
}
