#pragma once
#include <string>
using namespace std;
class Shape {
public:
	virtual string type() = 0;
	virtual string toString() = 0;
	virtual int perimeter() = 0;
	virtual int area() = 0;

};