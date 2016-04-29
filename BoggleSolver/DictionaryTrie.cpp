#include "stdafx.h"
#include "DictionaryTrie.h"

DictionaryTrie::DictionaryTrie():
	head(nullptr)
{
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
	return false;
}

void DictionaryTrie::add(char * word)
{
}

void DictionaryTrie::resetCursor()
{
	cursor = head;
}

bool DictionaryTrie::searchAtCursor(char letter)
{
	return false;
}

void DictionaryTrie::cursorToParent()
{
	DictionaryTrieNode* parent = cursor->getParent();
	if(parent)
	{
		cursor = parent;
	}
}
