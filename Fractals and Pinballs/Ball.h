#ifndef BALL_H
#define BALL_H
#include <vector>
/*THIS CLASS DESCRIBES A PINBALL IN 2D SPACE */
class Ball {
public:
	// constructor
	Ball(std::vector<double> currentCentre, double radius, std::vector<double> nextCentre, std::vector<double> velocity, std::vector<double> acceleration);
	// public variables
	std::vector<double> currentCentre;
	std::vector<double> nextCentre;
	std::vector<double> velocity;
	std::vector<double> acceleration;
	double radius;
};
#endif