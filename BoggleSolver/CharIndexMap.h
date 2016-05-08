#pragma once
#include <map>

class CharIndexMap
{
private:
	std::map<char, int> mMap;
public:
	CharIndexMap();

	// returns -1 if the lookup is invalid
	int get(char theCharacter) const
	{
		auto it = mMap.find(theCharacter);
		return it == mMap.end() ? -1 : it->second;

	};
};