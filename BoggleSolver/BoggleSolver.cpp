// BoggleSolver.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstring>

// Purely arbitrary to make max path length reasonable
const int kArbitraryMaxPath = 256;


void pauseForClose()
{
	writeLogLine("Hit enter to close");
	//Wait for input
	std::cin.get();
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

	writeLogLine("Loading dictionary");
	DictionaryTrie theDictionary;
	theDictionary.loadFromFile(path_to_dictionary);

	pauseForClose();

	return 0;
}

#endif





