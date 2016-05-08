#pragma once

// forward declarations
class DictionaryTrieNode;
class CharIndexMap;

class DictionaryTrie
{
private:
	DictionaryTrieNode* head;
	DictionaryTrieNode* mInternalCursor;

public:
	DictionaryTrie(CharIndexMap* charMap);
	~DictionaryTrie();

	bool LoadFromFile(char* filePath);
	bool Add(char* word);

	void ResetInternalCursor();
	bool SearchAtInternalCursor(char letter) const;
	void PopInternalCursor();

	DictionaryTrieNode* GetHead() const;
};
