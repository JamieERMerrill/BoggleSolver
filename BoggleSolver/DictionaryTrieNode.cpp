#include "stdafx.h"

DictionaryTrieNode::DictionaryTrieNode():
	mWord(nullptr),
	mChildren()
{	
}

DictionaryTrieNode::~DictionaryTrieNode()
{
	delete &mChildren;
}


DictionaryTrieNode* DictionaryTrieNode::addLetter(char letter)
{
	auto it = mChildren.find(letter);
	if(it != mChildren.end())
	{
		return &it->second;
	}

	DictionaryTrieNode* node = new DictionaryTrieNode();
	mChildren[letter] = *node;
	return node;
}

DictionaryTrieNode* DictionaryTrieNode::searchLetter(char letter)
{
	auto it = mChildren.find(letter);
	if(it != mChildren.end())
	{
		return &it->second;
	}

	// not found - return null pointer
	return nullptr;
}


