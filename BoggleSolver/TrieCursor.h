#pragma once

class DictionaryTrieNode;

class TrieCursor
{
private:
	DictionaryTrie* theTrie;
	DictionaryTrieNode* currentNode;

public:
	TrieCursor(DictionaryTrie* trie);
	void set(DictionaryTrieNode* newNode);
	bool isWord() const;
	bool hasChild(char letter) const;
	bool goToChild(char letter);
	void goToParent();
};
