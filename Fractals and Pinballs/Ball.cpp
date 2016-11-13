#include "Ball.h"

Ball::Ball(std::vector<int> currentCentre,int radius, std::vector<int> nextCentre, std::vector<int> velocity, std::vector<int> acceleration) {
	Ball::currentCentre = currentCentre;
	Ball::nextCentre = nextCentre;
	Ball::velocity = velocity;
	Ball::acceleration = acceleration;
	Ball::radius = radius;
}