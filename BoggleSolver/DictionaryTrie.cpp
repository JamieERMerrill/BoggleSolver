#include "stdafx.h"
#include "DictionaryTrie.h"
#include <fstream>

DictionaryTrie::DictionaryTrie(CharIndexMap* charMap):
	head(new DictionaryTrieNode(charMap))
{
	ResetInternalCursor();
}

DictionaryTrie::~DictionaryTrie()
{
	if (head)
	{
		delete head;
	}
}

bool DictionaryTrie::LoadFromFile(char * filePath)
{
	std::ifstream infp(filePath, std::ios_base::in);
	if(infp.fail())
	{
		return false;
	}

	while(infp.good())
	{
		// The longest word in a major dictionary is 45 characters long. The next longest word is 182. After that 1909 and 189819 letters.
		// I'll stick with pneumonoultramicascropicsilicovolcansoconiosis as my longest permitted word. Deal with it.
		char* theWord = new char[46];
		infp.getline(theWord, 46);
		
		// Don't include words with apostrophes
		auto apostropheFound = strstr(theWord, "'");
		auto quotesFound = strstr(theWord, "\"");
		if (apostropheFound || quotesFound)
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
		
		// Don't include words shorter than three letters
		if (wordLength < 3)
		{
			continue;
		}
	

		writeLogLineFormatted("Adding word: %s", theWord);
		bool added = Add(theWord);
		if(!added)
		{
			return false;
		}

		delete[] theWord;
	}

	ResetInternalCursor();
	return true;
}

bool DictionaryTrie::Add(char * word)
{
	ResetInternalCursor();
	char* currentChar = nullptr;
	for(currentChar=word; *currentChar!='\0'; currentChar++)
	{
		DictionaryTrieNode* nextNode = mInternalCursor->addLetter(*currentChar);
		if (nextNode)
		{
			mInternalCursor = nextNode;
		}
		else
		{
			return false;
		}
	}

	mInternalCursor->SetIsWord();
	return true;
}

void DictionaryTrie::ResetInternalCursor()
{
	mInternalCursor = head;
}

bool DictionaryTrie::SearchAtInternalCursor(char letter) const
{
	auto found = mInternalCursor->searchLetter(letter);
	return found != nullptr;
}

void DictionaryTrie::PopInternalCursor()
{
	DictionaryTrieNode* parent = mInternalCursor->getParent();
	if(parent)
	{
		mInternalCursor = parent;
	}
}

DictionaryTrieNode * DictionaryTrie::GetHead() const
{
	return head;
}
