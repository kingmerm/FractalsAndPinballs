#include "Ball.h"

Ball::Ball(std::vector<double> currentCentre,double radius, std::vector<double> nextCentre, std::vector<double> velocity, std::vector<double> acceleration) {
	Ball::currentCentre = currentCentre;
	Ball::nextCentre = nextCentre;
	Ball::velocity = velocity;
	Ball::acceleration = acceleration;
	Ball::radius = radius;
}