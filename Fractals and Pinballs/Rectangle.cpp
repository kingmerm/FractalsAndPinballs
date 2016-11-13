#include "Rectangle.h"

Rectangle::Rectangle(std::vector<int> topLeftCorner, int height, int width) {
	Rectangle::topLeftCorner = topLeftCorner;
	Rectangle::height = height;
	Rectangle::width = width;
}