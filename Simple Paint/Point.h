#pragma once
#include "Tokenizer.h"
#include <sstream>
#include "Shape.h"
class Point : public Shape
{
private:
	int _x;
	int _y;
public:
	Point();
	Point(int, int);
	static double calcDistance(Point, Point);
	int x();
	int y();
	void setX(int);
	void setY(int);
	string type();
	string toString();
	int perimeter();
	int area();
	static Point* parse(string);
};