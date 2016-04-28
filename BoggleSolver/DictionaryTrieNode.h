#pragma once

// Optimization note - is there a faster solution than a STL generic?
#include <map>

class DictionaryTrieNode
{

typedef std::map<char, DictionaryTrieNode> DictionaryTrieNodeMap;
public:
	DictionaryTrieNode();
	~DictionaryTrieNode();

	void SetIsWord(char* word)
	{
		mWord = word;
	};

	DictionaryTrieNode* addLetter(char letter);
	DictionaryTrieNode* searchLetter(char letter);

private:
	char* mWord;
	DictionaryTrieNodeMap mChildren;

};

