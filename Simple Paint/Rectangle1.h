#pragma once
#include "Shape.h"
#include "Point.h"
#include <Windows.h>
class Rectangle1 : public Shape
{
private:
	Point _topLeft;
	Point _rightBottom;
	//line width
	int _width;
	//color
	DWORD _lineColor;
	DWORD _fillColor;
public:
	string type();
	string toString();
	Rectangle1();
	Rectangle1(Point, Point, int, DWORD, DWORD);
	Point topLeft();
	Point rightBottom();
	int width();
	DWORD lineColor();
	DWORD fillColor();
	void setTopLeft(Point);
	void setrightBottom(Point);
	void setWidth(int);
	void setLineColor(DWORD);
	void setFillColor(DWORD);
	int perimeter();
	int area();
	static Rectangle1* parse(string);
};