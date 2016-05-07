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
	// board is:
	// a b c
	// d e f
	// g h i
	Board testBoard("abcdefghi", 3, 3);

	char letterOne = testBoard.AtGridLoc(0, 0);
	bool is_a = (letterOne == 'a');

	char letterFive = testBoard.AtGridLoc(1, 1);
	bool is_e = (letterFive == 'e');

	char letterNine = testBoard.AtGridLoc(2, 2);
	bool is_i = (letterNine == 'i');

	return is_a && is_e && is_i;
}

bool test_SimpleBoardCursor()
{
	// board is:
	// a b c d
	// e f g h
	Board testBoard("abcdefgh", 4, 2);
	BoardCursor testCursor(&testBoard);

	testCursor.StartFrom(0, 0);
	bool wentDown = testCursor.Move(Down);
	bool wentRight1 = testCursor.Move(Right);
	bool wentRight2 = testCursor.Move(Right);
	bool wentUp = testCursor.Move(Up);
	bool wentLeft = testCursor.Move(Left);

	char* word = testCursor.GetWord();
	bool rightWord = strcmp(word, "aefgcb") == 0;
	bool movements = wentDown && wentRight1 && wentRight2 && wentUp && wentLeft;
	return rightWord && movements;
}

bool test_InvalidCursorMoves()
{
	Board testBoard("a", 1, 1);
	BoardCursor testCursor(&testBoard);

	testCursor.StartFrom(0, 0);
	bool wentDown = testCursor.Move(Down);
	bool wentRight = testCursor.Move(Right);
	bool wentLeft = testCursor.Move(Left);
	bool wentUp = testCursor.Move(Up);

	char* word = testCursor.GetWord();
	bool rightWord = strcmp(word, "a") == 0;
	bool movements = !wentLeft && !wentDown && !wentRight && !wentUp;
	return rightWord && movements;
}

bool test_CannotRepeatPosition()
{
	Board testBoard("ab", 2, 1);
	BoardCursor testCursor(&testBoard);

	testCursor.StartFrom(0, 0);
	bool wentRight = testCursor.Move(Right);
	bool wentLeft = testCursor.Move(Left);

	char* word = testCursor.GetWord();
	bool rightWord = strcmp(word, "ab") == 0;
	bool movements = wentRight && !wentLeft;
	return rightWord && movements;
}

bool test_CusorPop()
{
	// Board:
	// a b c
	// d e f
	Board testBoard("abcdef", 3, 2);
	BoardCursor testCursor(&testBoard);

	testCursor.StartFrom(0, 0);
	bool wentRight1 = testCursor.Move(Right);
	bool wentRight2 = testCursor.Move(Right);
	char* firstWord = testCursor.GetWord();

	testCursor.Pop();

	bool wentDown = testCursor.Move(Down);
	char* secondWord = testCursor.GetWord();

	bool firstWordRight = strcmp(firstWord, "abc") == 0;
	bool secondWordRight = strcmp(secondWord, "abe") == 0;
	bool wordsRight = firstWordRight && secondWordRight;
	bool movements = wentRight1 && wentRight2 && wentDown;
	return wordsRight && movements;
}

bool test_PositionCompares()
{
	Position pos1 = Position{ 1, 1 };
	Position pos2 = Position{ 1, 2 };
	Position pos3 = Position{ 2, 1 };
	Position pos4 = Position{ 1, 1 };

	bool diffY = pos1 == pos2;
	bool diffX = pos1 == pos3;
	bool diffBoth = pos2 == pos3;
	bool same = pos1 == pos4;

	return !diffY && !diffX && !diffBoth && same;
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

	bool simpleBoardCursor = test_SimpleBoardCursor();
	logTest("Simple Board Cursor Behavior", simpleBoardCursor);

	bool invalidCursorMoves = test_InvalidCursorMoves();
	logTest("Invalid Cursor Moves", invalidCursorMoves);

	bool cannotRepeat = test_CannotRepeatPosition();
	logTest("Cannot repeat board position", cannotRepeat);

	bool cursorPop = test_CusorPop();
	logTest("Cursor pop operation", cursorPop);

	bool positionCompares = test_PositionCompares();
	logTest("Position comparison operator", positionCompares);

	return loadWordSimple && loadMultipleWords && loadSinglePlural && simpleBoardLookup 
		&& simpleBoardCursor && invalidCursorMoves && cannotRepeat && cursorPop && positionCompares;
}
