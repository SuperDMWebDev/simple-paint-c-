#include "Text.h"

string Text::type()
{
	return "Text";
}
string Text::toString()
{
	stringstream builder;
	builder << "Text: " << _x << "," << _y << "," << _content << "," << _length << "," << _color << endl;
	int fontNameSize = 0;
	for (int i = 0; i < LF_FACESIZE; i++)
	{
		if (_font.lfFaceName[i] == '\0')
			break;
		fontNameSize++;
	}

	builder << (long)_font.lfHeight << " " << (long)_font.lfWidth << " " << (long)_font.lfEscapement << " " << (long)_font.lfOrientation << " " <<
		(long)_font.lfWeight << " " << (byte)_font.lfItalic << " " << (byte)_font.lfUnderline << " " << (byte)_font.lfStrikeOut << " " << (byte)_font.lfCharSet << " " <<
		(byte)_font.lfOutPrecision << " " << (byte)_font.lfClipPrecision << " " << (byte)_font.lfQuality << " " << (byte)_font.lfPitchAndFamily << " " <<
		((fontNameSize == 0) ? L"NULL" : _font.lfFaceName);

	return builder.str();
}
Text::Text()
{
	_x = 0;
	_y = 0;
	_length = 0;
	_color = NULL;


}
Text::Text(int x, int y, string content, int length, LOGFONT font, DWORD color)
{
	_x = x;
	_y = y;
	_length = length;
	_content = content;
	_color = color;
	_font = font;

}
int Text::x()
{
	return _x;
}
int Text::y()
{
	return _y;
}
int Text::length()
{
	return _length;
}
LOGFONT Text::font()
{
	return _font;
}
string Text::content()
{
	return _content;
}
DWORD Text::color()
{
	return _color;
}
Text* Text::parse(string info, string info1)
{
	vector<string> tokens = Tokenizer::split(info, ",");
	int x = stoi(tokens[0]);
	int y = stoi(tokens[1]);
	string content = tokens[2];
	int length = stoi(tokens[3]);
	DWORD color = strtoul(tokens[4].c_str(), 0, 0);

	LOGFONT lgFont;

	vector<string> fontTokens = Tokenizer::split(info1, " ");
	if (fontTokens[13] == "NULL") {
		lgFont = {
		   stol(fontTokens[0]),
		   stol(fontTokens[1]),
		   stol(fontTokens[2]),
		   stol(fontTokens[3]),
		   stol(fontTokens[4]),
		   BYTE(fontTokens[5].c_str()),
		   BYTE(fontTokens[6].c_str()),
		   BYTE(fontTokens[7].c_str()),
		   BYTE(fontTokens[8].c_str()),
		   BYTE(fontTokens[9].c_str()),
		   BYTE(fontTokens[10].c_str()),
		   BYTE(fontTokens[11].c_str()),
		   BYTE(fontTokens[12].c_str()),
		   NULL
		};
	}
	else {
		lgFont = {
			stol(fontTokens[0]),
			stol(fontTokens[1]),
			stol(fontTokens[2]),
			stol(fontTokens[3]),
			stol(fontTokens[4]),
			BYTE(fontTokens[5].c_str()),
			BYTE(fontTokens[6].c_str()),
			BYTE(fontTokens[7].c_str()),
			BYTE(fontTokens[8].c_str()),
			BYTE(fontTokens[9].c_str()),
			BYTE(fontTokens[10].c_str()),
			BYTE(fontTokens[11].c_str()),
			BYTE(fontTokens[12].c_str())
		};

		int u = 0;
		const char fontTokensSize = fontTokens.size();
		for (int i = 13; i < fontTokensSize; i++) {
			for (int j = 0; j < fontTokens[i].length(); j++)
			{
				lgFont.lfFaceName[u] = fontTokens[i][j];
				u++;
			}


			if (i == fontTokensSize - 1)
			{
				lgFont.lfFaceName[u] = '\0';
				u++;
			}
			else
			{
				lgFont.lfFaceName[u] = ' ';
				u++;
			}
		}
	}
	Text* a = new Text(x, y, content, length, lgFont, color);
	return a;
}