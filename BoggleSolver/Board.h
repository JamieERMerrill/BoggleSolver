#pragma once


class Board
{

private:
	char* mBoardArray;
	int mColumns;
	int mRows;

public:
	Board();
	// For test purposes
	Board(char* board, int columns, int rows);
	~Board();

	bool loadFromFile(char* filePath);

	char atGridLoc(int column, int row) const;
	char atGridIndex(int index) const;

	int getGridIndex(int column, int row) const;

	bool validIndex(int column, int row) const;
};