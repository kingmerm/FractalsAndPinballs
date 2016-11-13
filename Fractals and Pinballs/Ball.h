#pragma once
#include <vector>
/*THIS CLASS DESCRIBES A PINBALL IN 2D SPACE */
class Ball {
public:
	// constructor
	Ball(std::vector<int> currentCentre, int radius, std::vector<int> nextCentre, std::vector<int> velocity, std::vector<int> acceleration);
	// public variables
	std::vector<int> currentCentre;
	std::vector<int> nextCentre;
	std::vector<int> velocity;
	std::vector<int> acceleration;
	int radius;
};