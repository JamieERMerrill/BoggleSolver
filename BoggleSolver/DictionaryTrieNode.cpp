#include "stdafx.h"

DictionaryTrieNode::DictionaryTrieNode(CharIndexMap* charMap) :
	mIsWord(false),
	isUsed(false),
	parent(nullptr),
	mMap(charMap)
{
	
}

DictionaryTrieNode::DictionaryTrieNode(CharIndexMap* charMap, DictionaryTrieNode* parent) :
	mIsWord(false),
	isUsed(false),
	parent(parent),
	mMap(charMap)
{	
}

DictionaryTrieNode::~DictionaryTrieNode()
{
}


DictionaryTrieNode* DictionaryTrieNode::addLetter(char letter)
{
	int index = mMap->get(letter);
	if(index < 0)
	{
		return nullptr;
	}
	if(mChildren[index] != nullptr)
	{
		return mChildren[index];
	}

	DictionaryTrieNode* node = new DictionaryTrieNode(mMap, this);
	mChildren[index] = node;
	return node;
}

DictionaryTrieNode* DictionaryTrieNode::searchLetter(char letter)
{
	int index = mMap->get(letter);
	if(index >= 0)
	{
		if(mChildren[index] != nullptr)
		{
			return mChildren[index];
		}
	}

	// not found - return null pointer
	return nullptr;
}

DictionaryTrieNode* DictionaryTrieNode::getParent() const
{
	return parent;
}



