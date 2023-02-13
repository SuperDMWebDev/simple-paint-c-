#include "Point.h"

string Point::type()
{
	return "Point";
}
Point::Point()
{
	_x = 0;
	_y = 0;
}
Point::Point(int x, int y)
{
	_x = x;
	_y = y;

}

void Point::setX(int value)
{
	_x = value;

}
void Point::setY(int value)
{
	_y = value;
}
int Point::x()
{
	return _x;
}
int Point::y()
{
	return _y;
}
double Point::calcDistance(Point a, Point b)
{
	double dx = a.x() - b.x();
	double dy = a.y() - b.y();
	double result = sqrt(dx * dx + dy * dy);
	return result;
}
string Point::toString()
{
	stringstream builder;
	builder << _x << "," << _y;
	return  builder.str();
}
int Point::perimeter()
{
	return 0;
}
int Point::area()
{
	return 0;
}
Point* Point::parse(string info)
{
	auto tokens = Tokenizer::split(info, ",");
	int x = stoi(tokens[0]);
	int y = stoi(tokens[1]);
	Point* result = new Point(x, y);
	return result;
}
