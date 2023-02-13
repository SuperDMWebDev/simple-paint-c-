#include "Rectangle1.h"

string Rectangle1::type()
{
	return "Rectangle";
}
string Rectangle1::toString()
{
	stringstream builder;
	builder << "Rectangle: " << _topLeft.toString() << " " << _rightBottom.toString() << " " << _width << " " << to_string(_lineColor) + " " + to_string(_fillColor);
	return builder.str();
}
Rectangle1::Rectangle1()
{
	_topLeft = Point(0, 0);
	_rightBottom = Point(0, 0);
	_width = 0;

}
Rectangle1::Rectangle1(Point topLeft, Point rightBottom, int width, DWORD lineColor, DWORD fillColor)
{
	_topLeft = topLeft;
	_rightBottom = rightBottom;
	_width = width;
	_lineColor = lineColor;
	_fillColor = fillColor;
}
Point Rectangle1::topLeft()
{
	return _topLeft;
}
Point Rectangle1::rightBottom()
{
	return _rightBottom;
}
int Rectangle1::width()
{
	return _width;
}
DWORD Rectangle1::lineColor()
{
	return _lineColor;
}
DWORD Rectangle1::fillColor()
{
	return _fillColor;
}
void Rectangle1::setTopLeft(Point value)
{
	_topLeft = value;
}
void Rectangle1::setrightBottom(Point value)
{
	_rightBottom = value;
}
void Rectangle1::setWidth(int value)
{
	_width = value;
}
void Rectangle1::setLineColor(DWORD value)
{
	_lineColor = value;
}
void Rectangle1::setFillColor(DWORD value)
{
	_fillColor = value;
}
int Rectangle1::perimeter()
{
	int dx = _rightBottom.x() - _topLeft.x();
	int dy = _rightBottom.y() - _topLeft.y();
	dx = dx > 0 ? dx : -dx;
	dy = dy > 0 ? dy : -dy;
	int result = 2 * (dx + dy);
	return result;

}
int Rectangle1::area()
{
	int dx = _rightBottom.x() - _topLeft.x();
	int dy = _rightBottom.y() - _topLeft.y();
	dx = dx > 0 ? dx : -dx;
	dy = dy > 0 ? dy : -dy;
	int result = dx * dy;
	return result;
}

Rectangle1* Rectangle1::parse(string info) {
	auto  tokens = Tokenizer::split(info, " ");
	Point* topLeft = Point::parse(tokens[0]);
	Point* rightBottom = Point::parse(tokens[1]);
	int lineWidth = stoi(tokens[2]);
	DWORD outlineColor = strtoul(tokens[3].c_str(), 0, 0);
	DWORD fillColor = strtoul(tokens[4].c_str(), 0, 0);
	Rectangle1* rectangle = new Rectangle1(*topLeft, *rightBottom, lineWidth, outlineColor, fillColor);
	return rectangle;
}
