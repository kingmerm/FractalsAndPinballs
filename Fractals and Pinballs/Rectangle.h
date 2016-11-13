#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <vector>

/*THIS CLASS DESCRIBES A RECTANGULAR OBJECT IN 2D*/
class Rectangle {
public:
	// public variables
	std::vector<double> topLeftCorner;
	double height;
	double width;
	// constructor
	Rectangle(std::vector<double> topLeftCorner, double height, double width);
};
#endif