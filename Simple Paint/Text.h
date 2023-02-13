#pragma once
#include <Windows.h>
#include "framework.h"
#include <string>
#include <sstream>
#include "Tokenizer.h"
using namespace std;
class Text {
private:
	int _x;
	int _y;
	string _content;

	int _length;

	LOGFONT _font;
	DWORD _color;
public:
	string type();
	string toString();
	Text();
	Text(int, int, string, int, LOGFONT, DWORD);
	int x();
	int y();
	int length();
	LOGFONT font();
	string content();
	DWORD color();
	static Text* parse(string, string);

};