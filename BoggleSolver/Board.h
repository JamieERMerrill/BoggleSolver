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

	bool LoadFromFile(char* filePath);

	char AtGridLoc(int column, int row) const;
	char AtGridIndex(int index) const;

	int GetGridIndex(int column, int row) const;

	bool ValidIndex(int column, int row) const;

	int ColumnCount() const
	{
		return mColumns;
	};

	int RowCount() const
	{
		return mRows;
	};

};