#include "stdafx.h"
#include "Tests.h"


void logTest(char* testName, bool status)
{
	char* result = status ? "pass" : "fail";
	writeLogLineFormatted("%s: %s", testName, result);
}

bool test_LoadWordSimple()
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

bool test_LoadMultipleWords()
{
	DictionaryTrie testTrie;
	TrieCursor cursor(&testTrie);

	testTrie.add("cat");
	testTrie.add("hat");

	bool got_c = cursor.goToChild('c');
	bool got_a = cursor.goToChild('a');
	bool got_t = cursor.goToChild('t');

	bool isWord_cat = cursor.isWord();
	bool cat_components = got_c && got_a && got_t;
	
	cursor.set(testTrie.getHead());

	bool got_h = cursor.goToChild('h');
	bool got_a_2 = cursor.goToChild('a');
	bool got_t_2 = cursor.goToChild('t');

	bool isWord_hat = cursor.isWord();
	bool hat_components = got_h && got_a_2 && got_t_2;

	return isWord_cat && cat_components && isWord_hat && hat_components;
}

bool test_LoadSinglePlural()
{
	DictionaryTrie testTrie;
	TrieCursor cursor(&testTrie);

	testTrie.add("cat");
	testTrie.add("cats");

	bool got_c = cursor.goToChild('c');
	bool got_a = cursor.goToChild('a');
	bool got_t = cursor.goToChild('t');

	bool isWord_cat = cursor.isWord();
	bool got_s = cursor.goToChild('s');
	bool isWord_cats = cursor.isWord();

	return got_c && got_a && got_t && got_s && isWord_cat && isWord_cats;
}

bool test_SimpleBoardLookup()
{
	Board testBoard("abcdefghi", 3, 3);

	char letterOne = testBoard.atGridLoc(0, 0);
	bool is_a = (letterOne == 'a');

	char letterFive = testBoard.atGridLoc(1, 1);
	bool is_e = (letterFive == 'e');

	char letterNine = testBoard.atGridLoc(2, 2);
	bool is_i = (letterNine == 'i');

	return is_a && is_e && is_i;
}

bool runTests()
{
	bool loadWordSimple = test_LoadWordSimple();
	logTest("Load Word", loadWordSimple);

	bool loadMultipleWords = test_LoadMultipleWords();
	logTest("Load Multiple Words", loadMultipleWords);

	bool loadSinglePlural = test_LoadSinglePlural();
	logTest("Load Single and Plural Words", loadSinglePlural);

	bool simpleBoardLookup = test_SimpleBoardLookup();
	logTest("Simple Board Lookup", simpleBoardLookup);

	return loadWordSimple && loadMultipleWords;
}
