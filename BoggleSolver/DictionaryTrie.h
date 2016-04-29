#pragma once

// forward declarations
class DictionaryTrieNode;

class DictionaryTrie
{
private:
	DictionaryTrieNode* head;
	DictionaryTrieNode* cursor;
public:
	DictionaryTrie();
	~DictionaryTrie();

	bool loadFromFile(char* filePath);
	void add(char* word);

	void resetCursor();
	bool searchAtCursor(char letter);
	void cursorToParent();
};
