// BoggleSolver.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstring>

// Purely arbitrary to make max path length reasonable
const int kArbitraryMaxPath = 256;


void pauseForClose()
{
	std::cout << "Hit enter to close" << std::endl;
	//Wait for input
	std::cin.get();
}

int main(int argc, char *argv[], char* envp[])
{
	std::cout << "Starting boggle solver" << std::endl;

	char path_to_dictionary[kArbitraryMaxPath];
	char path_to_puzzle[kArbitraryMaxPath];
	
	if(argc != 3)
	{
		std::cout << "Boggle Solver Command Line Arguments:" << std::endl;
		std::cout << "BoggleSolver.exe {PATH_TO_DICTIONARY} {PATH_TO_PUZZLE}" << std::endl;
		pauseForClose();
		return 1;
	}
	else
	{
		strcpy_s(path_to_dictionary, argv[1]);
		std::cout << "Path to dictionary: " << path_to_dictionary << std::endl;

		strcpy_s(path_to_puzzle, argv[2]);
		std::cout << "Path to puzzle: " << path_to_puzzle << std::endl;
	}

	pauseForClose();

    return 0;
}



