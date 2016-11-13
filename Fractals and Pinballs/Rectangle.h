#pragma once
#include <vector>

/*THIS CLASS DESCRIBES A RECTANGULAR OBJECT IN 2D*/
class Rectangle {
public:
	// public variables
	std::vector<int> topLeftCorner;
	int height;
	int width;
	// constructor
	Rectangle(std::vector<int> topLeftCorner, int height, int width);
};
