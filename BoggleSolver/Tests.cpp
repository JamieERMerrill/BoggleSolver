#include "stdafx.h"
#include "Tests.h"


void logTest(char* testName, bool status)
{
	char* result = status ? "pass" : "fail";
	writeLogLineFormatted("%s: %s", testName, result);
}

bool test_LoadWord()
{
	DictionaryTrie testTrie;
	TrieCursor cursor(&testTrie);
	testTrie.add("cat");

	bool got_c = cursor.goToChild('c');
	bool got_a = cursor.goToChild('a');
	bool got_t = cursor.goToChild('t');

	bool isWord = cursor.isWord();

	return got_c && got_a && got_t && isWord;
}

bool runTests()
{
	bool loadWord = test_LoadWord();
	logTest("Load Word", loadWord);

	return loadWord;
}
