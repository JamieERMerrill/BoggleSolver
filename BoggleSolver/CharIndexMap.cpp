#include "stdafx.h"


CharIndexMap::CharIndexMap():
	mMap()
{
	char allChars[53]{
		"aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ"
	};

	char* currentChar = new char[2];
	currentChar[1] = '\0';
	for (int i = 0; i < 52; i++)
	{
		currentChar[0] = allChars[i];
		mMap[*currentChar] = i / 2;
	}

	delete[] currentChar;
}