// BoggleSolver.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstring>
#include <time.h>
#include <fstream>
#include <thread>

// Purely arbitrary to make max path length reasonable
const int kArbitraryMaxPath = 256;
const int kThreadPoolSize = 10;


void pauseForClose()
{
	writeLogLine("Hit enter to close");
	//Wait for input
	std::cin.get();
}

void RecursiveTreeWalk(BoardCursor* boardCursor, TrieCursor* dictCursor, ThreadsafeStack<char*>* words);

void SearchFromIntialNode(int column, int row, Board* board, DictionaryTrie* Trie, ThreadsafeStack<char*>* words)
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

void RecursiveTreeWalk(BoardCursor* boardCursor, TrieCursor* dictCursor, ThreadsafeStack<char*>* words)
{
	Direction allDirections[4] = { Right, Left, Up, Down };
	for(int i = 0; i < 4; i++)
	{
		Direction direction = allDirections[i];
		bool moved = boardCursor->Move(direction);
		if (moved)
		{
			char* boardLetter = boardCursor->GetLetter();
			if (dictCursor->hasChild(*boardLetter))
			{
				dictCursor->goToChild(*boardLetter);
				dictCursor->LockNode();
				if (dictCursor->isWord() && !dictCursor->getWordUsed())
				{
					char* word = boardCursor->GetWord();
#if defined(_DEBUG)
					writeLogLineFormatted("Adding found word %s", word);
#endif

					dictCursor->setWordUsed();
					words->Lock();
					words->push(word);
					words->Unlock();
					//delete[] word;
				}
				dictCursor->UnlockNode();

				RecursiveTreeWalk(boardCursor, dictCursor, words);
				dictCursor->goToParent();
			}
			delete[] boardLetter;
			boardCursor->Pop();
		}
	}	
}

void threadBaseLevel(Board* board, DictionaryTrie* dictionary, ThreadsafeStack<std::pair<int, int>>* taskStack, ThreadsafeStack<char*>* words)
{
	while(true)
	{
		taskStack->Lock();
		if(taskStack->empty())
		{
			taskStack->Unlock();
			break;
		}

		std::pair<int, int> thisStartPoint = taskStack->pop();
		taskStack->Unlock();

		SearchFromIntialNode(thisStartPoint.first, thisStartPoint.second, board, dictionary, words);
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
	char path_to_results[kArbitraryMaxPath];

	if (argc != 4)
	{
		writeLogLine("Boggle Solver Command Line Arguments:");
		writeLogLine("BoggleSolver.exe {PATH_TO_DICTIONARY} {PATH_TO_PUZZLE} {RESULTS_FILE}");
		pauseForClose();
		return 1;
	}

	strcpy_s(path_to_dictionary, argv[1]);
	writeLogLineFormatted("Path to dictionary: %s", path_to_dictionary);

	strcpy_s(path_to_puzzle, argv[2]);
	writeLogLineFormatted("Path to puzzle: %s", path_to_puzzle);
	
	strcpy_s(path_to_results, argv[3]);
	writeLogLineFormatted("Path to results file %s", path_to_results);

	CharIndexMap* theMap = new CharIndexMap();

	writeLogLine("Loading dictionary");
	DictionaryTrie theDictionary(theMap);
	bool dictLoaded = theDictionary.LoadFromFile(path_to_dictionary);

	if(!dictLoaded)
	{
		writeLogLine("Dictionary Load Failed");
		pauseForClose();
		return -1;
	}

	writeLogLine("Loading board");
	Board theBoard;
	bool boardLoaded = theBoard.LoadFromFile(path_to_puzzle);

	if(!boardLoaded)
	{
		writeLogLine("Failed board loading");
		pauseForClose();
		return -1;
	}

	ThreadsafeStack<char*> foundWords;
	ThreadsafeStack<std::pair<int, int>> taskStack;
	int columns = theBoard.ColumnCount();
	int rows = theBoard.RowCount();

	for (int thisRow = 0; thisRow < rows; thisRow++)
	{
		for (int thisColumn = 0; thisColumn < columns; thisColumn++)
		{
			taskStack.push(std::pair<int, int>(thisColumn, thisRow));
		}
	}

	clock_t timer;
	timer = clock();

	std::vector<std::thread> threadPool;
	for (int i = 0; i < kThreadPoolSize; i++)
	{
		threadPool.push_back(std::thread(threadBaseLevel, &theBoard, &theDictionary, &taskStack, &foundWords));
	}
	
	for (int i = 0; i < kThreadPoolSize; i++)
	{
		threadPool[i].join();
	}

	timer = clock() - timer;
	float timeSpent = static_cast<float>(timer) / CLOCKS_PER_SEC;

	writeLogLineFormatted("Took %f to solve", timeSpent);
	writeLogLineFormatted("Found %i words", foundWords.size());

	std::ofstream outfp(path_to_results);
	if(outfp.is_open())
	{
		while(!foundWords.empty())
		{
			char* word = foundWords.pop();
			outfp.write(word, strlen(word));
			outfp.write("\n", 1);
		}
	}

	
	//writeLogLine("All words:");
	//for(char* word : foundWords)
	//{
	//	writeLogLineFormatted("%s", word);
	//}

	pauseForClose();

	delete theMap;
	return 0;
}

#endif





