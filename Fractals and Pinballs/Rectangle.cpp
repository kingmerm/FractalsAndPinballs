#include "Rectangle.h"

Rectangle::Rectangle(std::vector<double> topLeftCorner, double height, double  width) {
	Rectangle::topLeftCorner = topLeftCorner;
	Rectangle::height = height;
	Rectangle::width = width;
}