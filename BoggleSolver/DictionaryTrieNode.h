#pragma once

// Optimization note - is there a faster solution than a STL generic?
#include <map>

class DictionaryTrieNode
{

typedef std::map<char, DictionaryTrieNode*> DictionaryTrieNodeMap;
public:
	DictionaryTrieNode();
	DictionaryTrieNode(DictionaryTrieNode* parent);
	~DictionaryTrieNode();

	void SetIsWord(char* word)
	{
		mWord = word;
	};

	DictionaryTrieNode* addLetter(char letter);
	DictionaryTrieNode* searchLetter(char letter);
	DictionaryTrieNode* getParent() const;

	bool isWord() const
	{
		return mWord != nullptr && mWord[0] != '\0';
	};

	char* getWord() const
	{
		return mWord;
	};

private:
	char* mWord;
	DictionaryTrieNode* parent;
	DictionaryTrieNodeMap mChildren;
};

