#pragma once
#include "Tokenizer.h"
#include <sstream>

vector<string> Tokenizer::split(string haystack, string separator = "")
{
	vector<string> tokens;
	int startPos = 0;
	size_t foundPos = 0;

	while (1) {
		foundPos = haystack.find(separator, startPos);
		if (foundPos != string::npos) {
			string token = haystack.substr(startPos, foundPos - startPos);
			tokens.push_back(token);
			startPos = foundPos + separator.length();
		}
		else {
			string token = haystack.substr(startPos, haystack.length() - startPos);
			tokens.push_back(token);
			break;
		}
	}
	return tokens;
}
