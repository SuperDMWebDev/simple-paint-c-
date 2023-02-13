#include "Ellipse1.h"


string Ellipse1::type()
{
	return "Ellipse";
}
string Ellipse1::toString()
{
	stringstream builder;
	builder << "Ellipse: " << _topLeft.toString() << " " << _rightBottom.toString() << " " << _width << " " << to_string(_lineColor) << " " << to_string(_fillColor);
	return builder.str();
}
Ellipse1::Ellipse1()
{
	_topLeft = Point(0, 0);
	_rightBottom = Point(0, 0);
	_width = 0;
	// them lineColor va fill color
}
Ellipse1::Ellipse1(Point topLeft, Point rightBottom, int width, DWORD lineColor, DWORD fillColor)
{
	_topLeft = topLeft;
	_rightBottom = rightBottom;
	_width = width;
	_lineColor = lineColor;
	_fillColor = fillColor;


}
Point Ellipse1::topLeft()
{
	return _topLeft;
}
Point Ellipse1::rightBottom()
{
	return _rightBottom;
}
int Ellipse1::width()
{
	return _width;
}
DWORD Ellipse1::lineColor()
{
	return _lineColor;
}
DWORD Ellipse1::fillColor()
{
	return _fillColor;
}
void Ellipse1::setTopLeft(Point value)
{
	_topLeft = value;
}
void Ellipse1::setrightBottom(Point value)
{
	_rightBottom = value;
}
void Ellipse1::setWidth(int value)
{
	_width = value;
}
void Ellipse1::setLineColor(DWORD value)
{
	_lineColor = value;
}
void Ellipse1::setFillColor(DWORD value)
{
	_fillColor = value;
}
int Ellipse1::perimeter()
{
	const double PI = 3.14159265358979323846;
	int diameter = _rightBottom.x() - _topLeft.x();
	diameter = diameter > 0 ? diameter : -diameter; // duong kinh
	int result = PI * diameter;
	return result;
}
int Ellipse1::area()
{
	const double PI = 3.14159265358979323846;
	int diameter = _rightBottom.x() - _topLeft.x();
	diameter = diameter > 0 ? diameter : -diameter; // duong kinh
	int result = PI * diameter * diameter / 4;
	return result;
}
Ellipse1* Ellipse1::parse(string info)
{
	auto tokens = Tokenizer::split(info, " ");
	Point* topLeft = Point::parse(tokens[0]);
	Point* rightBottom = Point::parse(tokens[1]);
	int width = stoi(tokens[2]);
	DWORD lineColor = strtoul(tokens[3].c_str(), 0, 0);
	DWORD fillColor = strtoul(tokens[4].c_str(), 0, 0);
	Ellipse1* result = new Ellipse1(*topLeft, *rightBottom, width, lineColor, fillColor);
	return result;
}