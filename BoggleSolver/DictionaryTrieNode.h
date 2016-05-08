#pragma once

// Optimization note - is there a faster solution than a STL generic?
class CharIndexMap;

class DictionaryTrieNode
{

public:
	DictionaryTrieNode(CharIndexMap* charMap);
	DictionaryTrieNode(CharIndexMap* charMap, DictionaryTrieNode* parent);
	~DictionaryTrieNode();

	void SetIsWord()
	{
		mIsWord = true;
	};

	DictionaryTrieNode* addLetter(char letter);
	DictionaryTrieNode* searchLetter(char letter);
	DictionaryTrieNode* getParent() const;

	bool isWord() const
	{
		return mIsWord;
	};

	bool GetIsUsed() const
	{
		return isUsed;
	};

	void SetUsed()
	{
		isUsed = true;
	};

private:
	bool mIsWord;
	bool isUsed;
	DictionaryTrieNode* parent;
	CharIndexMap* mMap;
	DictionaryTrieNode* mChildren[26];
};

