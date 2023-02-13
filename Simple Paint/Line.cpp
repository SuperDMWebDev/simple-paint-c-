#pragma once
#include "Line.h"

string Line::type()
{
	return "Line";

}
string Line::toString()
{
	stringstream builder;
	builder << "Line: " << _start.toString() << " " << _end.toString() << " " << to_string(_width) << " " << to_string(_color);
	return builder.str();
}
Line::Line()
{
	_start = Point(0, 0);
	_end = Point(0, 0);
	_width = 2;
}
Line::Line(Point start, Point end, int width, DWORD color)
{
	_start = start;
	_end = end;
	_width = width;
	_color = color;
}
Point Line::start()
{
	return _start;
}
Point Line::end()
{
	return _end;
}
int Line::width()
{
	return _width;
}
DWORD Line::color()
{
	return _color;
}
void Line::setStart(Point value)
{
	_start = value;
}
void Line::setEnd(Point value)
{
	_end = value;
}
void Line::setWidth(int value)
{
	_width = value;
}
void Line::setColor(DWORD value)
{
	_color = value;
}
int Line::perimeter()
{
	return Point::calcDistance(_start, _end);
}
int Line::area()
{
	return 1;
}
Line* Line::parse(string info)
{
	auto tokens = Tokenizer::split(info, " ");
	Point* start = Point::parse(tokens[0]);
	Point* end = Point::parse(tokens[1]);
	int width = stoi(tokens[2]);
	DWORD color = stoul(tokens[3]);
	Line* result = new Line(*start, *end, width, color);
	return result;

}