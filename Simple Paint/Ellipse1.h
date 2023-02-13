#pragma once
#include "Shape.h"
#include "Point.h"
#include <Windows.h>
using namespace std;
// trung ten voi ham Ellipse nen phai dat de phan biet
class Ellipse1 : public Shape
{
private:
	Point _topLeft;
	Point _rightBottom;
	int _width;
	DWORD _lineColor; // mau o ngoai 
	DWORD _fillColor; // mau o trong

public:

	Ellipse1();
	Ellipse1(Point, Point, int, DWORD, DWORD);
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
	string type();
	string toString();
	static Ellipse1* parse(string);
};