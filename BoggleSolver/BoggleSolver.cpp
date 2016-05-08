// BoggleSolver.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstring>
#include <time.h>

// Purely arbitrary to make max path length reasonable
const int kArbitraryMaxPath = 256;


void pauseForClose()
{
	writeLogLine("Hit enter to close");
	//Wait for input
	std::cin.get();
}

void RecursiveTreeWalk(BoardCursor* boardCursor, TrieCursor* dictCursor, std::vector<char*>* words);

void SearchFromIntialNode(int column, int row, Board* board, DictionaryTrie* Trie, std::vector<char*>* words)
{
	TrieCursor dictionaryCursor(Trie);
	BoardCursor boardCursor(board);

	boardCursor.StartFrom(column, row);
	if (dictionaryCursor.hasChild(*boardCursor.GetLetter()))
	{
		dictionaryCursor.goToChild(*boardCursor.GetLetter());
		RecursiveTreeWalk(&boardCursor, &dictionaryCursor, words);
	}
}

void RecursiveTreeWalk(BoardCursor* boardCursor, TrieCursor* dictCursor, std::vector<char*>* words)
{
	Direction allDirections[4] = { Right, Left, Up, Down };
	for(int i = 0; i < 4; i++)
	{
		Direction direction = allDirections[i];
		bool moved = boardCursor->Move(direction);
		if (moved)
		{
			if (dictCursor->hasChild(*boardCursor->GetLetter()))
			{
				dictCursor->goToChild(*boardCursor->GetLetter());

				if (dictCursor->isWord() && !dictCursor->getWordUsed())
				{
#if defined(_DEBUG)
					writeLogLineFormatted("Adding found word %s", boardCursor->GetWord());
#endif

					dictCursor->setWordUsed();
					words->push_back(boardCursor->GetWord());
				}

				RecursiveTreeWalk(boardCursor, dictCursor, words);
				dictCursor->goToParent();
			}
			boardCursor->Pop();
		}
	}	
}

#ifdef UNITTEST
int main()
{
	bool testsPassed = runTests();
	if (testsPassed)
	{
		writeLogLine("Tests all passed!");
	}
	else
	{
		writeLogLine("Tests failed");
	}

	pauseForClose();
	return 0;
}
#else

int main(int argc, char *argv[], char* envp[])
{
	// If this were a larger project, I'd set up a separate GTest project for this, but that's a lot of work to get a handful of unit tests implemented
	// and as such is a pretty excessive solution to my problem.

	writeLogLine("Starting boggle solver");

	char path_to_dictionary[kArbitraryMaxPath];
	char path_to_puzzle[kArbitraryMaxPath];

	if (argc != 3)
	{
		writeLogLine("Boggle Solver Command Line Arguments:");
		writeLogLine("BoggleSolver.exe {PATH_TO_DICTIONARY} {PATH_TO_PUZZLE}");
		pauseForClose();
		return 1;
	}

	strcpy_s(path_to_dictionary, argv[1]);
	writeLogLineFormatted("Path to dictionary: %s", path_to_dictionary);

	strcpy_s(path_to_puzzle, argv[2]);
	writeLogLineFormatted("Path to puzzle: %s", path_to_puzzle);

	CharIndexMap* theMap = new CharIndexMap();

	writeLogLine("Loading dictionary");
	DictionaryTrie theDictionary(theMap);
	theDictionary.LoadFromFile(path_to_dictionary);

	writeLogLine("Loading board");
	Board theBoard;
	theBoard.LoadFromFile(path_to_puzzle);

	std::vector<char*> foundWords;
	int columns = theBoard.ColumnCount();
	int rows = theBoard.RowCount();

	clock_t timer;
	timer = clock();
	for(int thisRow = 0; thisRow < rows; thisRow++)
	{
		for(int thisColumn = 0; thisColumn < columns; thisColumn++)
		{
			SearchFromIntialNode(thisColumn, thisRow, &theBoard, &theDictionary, &foundWords);
		}
	}
	timer = clock() - timer;
	float timeSpent = static_cast<float>(timer) / CLOCKS_PER_SEC;

	writeLogLineFormatted("Took %f to solve", timeSpent);
	writeLogLineFormatted("Found %i words", foundWords.size());
	writeLogLine("All words:");
	for(char* word : foundWords)
	{
		writeLogLineFormatted("%s", word);
	}

	pauseForClose();

	delete theMap;
	return 0;
}

#endif





