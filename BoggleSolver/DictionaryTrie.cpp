#include "stdafx.h"
#include "DictionaryTrie.h"
#include <fstream>

DictionaryTrie::DictionaryTrie():
	head(new DictionaryTrieNode())
{
	resetCursor();
}

DictionaryTrie::~DictionaryTrie()
{
	if (head)
	{
		delete head;
	}
}

bool DictionaryTrie::loadFromFile(char * filePath)
{
	std::ifstream infp(filePath, std::ios_base::in);
	if(infp.fail())
	{
		return false;
	}

	while(infp.good())
	{
		char theWord[256];
		infp.getline(theWord, 256);
		
		// Don't include words with apostrophes
		auto apostropheFound = strstr(theWord, "'");
		if (apostropheFound)
		{
			continue;
		}

		// Don't include words with numbers in them
		char* c = nullptr;
		int wordLength = 0;
		for(c = theWord; *c!='\0'; c++)
		{
			if(isdigit(*c))
			{
				continue;
			}
			wordLength++;
		}
		
		// Don't include words shorter than three 
		if (wordLength < 3)
		{
			continue;
		}
	

		writeLogLineFormatted("Adding word: %s", theWord);
		add(theWord);
	}

	return true;
}

void DictionaryTrie::add(char * word)
{
	resetCursor();
	char* currentChar = nullptr;
	for(currentChar=word; *currentChar!='\0'; currentChar++)
	{
		cursor = cursor->addLetter(*currentChar);
	}

	cursor->SetIsWord(word);
}

void DictionaryTrie::resetCursor()
{
	cursor = head;
}

bool DictionaryTrie::searchAtCursor(char letter) const
{
	auto found = cursor->searchLetter(letter);
	return found != nullptr;
}

void DictionaryTrie::cursorToParent()
{
	DictionaryTrieNode* parent = cursor->getParent();
	if(parent)
	{
		cursor = parent;
	}
}

DictionaryTrieNode * DictionaryTrie::getHead()
{
	return head;
}
