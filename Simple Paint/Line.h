#pragma once
#include "Point.h"
#include "Shape.h"
#include <Windows.h>
class Line : public Shape {
private:
	Point _start;
	Point _end;
	int _width; // do dam cua line
	DWORD _color; // mau sac cua line 
public:

	Line();
	Line(Point, Point, int, DWORD);
	Point start();
	Point end();
	int width();
	DWORD color();
	void setStart(Point value);
	void setEnd(Point end);
	void setWidth(int value);
	void setColor(DWORD value);
	int perimeter();
	int area();
	string type();
	string toString();
	static Line* parse(string);


};