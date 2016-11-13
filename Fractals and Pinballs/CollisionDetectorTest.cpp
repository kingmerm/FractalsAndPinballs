#include <memory>
#include <vector>
#include <algorithm>
#include <math.h>
#include "Ball.h"
#include "Rectangle.h"

int findClosestPoint(int value, int min, int max) {
	int distFromMinExtent = abs(min - value);
	int distFromMaxExtent = abs(max - value);
	if (distFromMinExtent < distFromMaxExtent) { return min; }
	else { return max; }
}


bool collisionCheck(std::shared_ptr<Ball> pinball, std::shared_ptr<Rectangle> obj) {
	std::vector<int> halfObjExtents = {obj->width / 2, obj->height / 2 };
	//COMPUTE CLOSEST X POINT OF RECTANGLE TO CIRCLE CENTRE X
	int closestXPoint = findClosestPoint(pinball->currentCentre[0], obj->topLeftCorner[0], obj->topLeftCorner[0] + obj->width);
	int closestYPoint = findClosestPoint(pinball->currentCentre[1], obj->topLeftCorner[1] - obj->height, obj->topLeftCorner[0]);
	if (pinball->currentCentre[0] > obj->topLeftCorner[0] + obj->width && obj->topLeftCorner[1] - obj->height) { return false; }
	//COMPUTE DISTANCE BETWEEN CIRCLE CENTER AND CLOSEST RECTANGLE POINT
	int xDistance = abs(pinball->currentCentre[0] - closestXPoint);
	int yDistance = abs(pinball->currentCentre[1] - closestYPoint);
	//WHEN DISTANCE SQUARED < RADIUS SQUARED WE GET A HIT
	int distanceFromCircleSquared = (int)pow(xDistance,2) + (int)pow(yDistance,2);
	return (distanceFromCircleSquared < (int)pow(pinball->radius,2));
}

int main(int argv, char**argsc) {
	/*initial parameters of simulation*/
	std::vector<int> currentBallCentre = { 0,0 };
	std::vector<int> nextBallCentre = { 0,0 };
	std::vector<int> ballVelocity = { 1,0 };
	std::vector<int> acceleration = { 1,0 };
	int ballRadius = 2;
	auto pinball = std::make_shared<Ball>(currentBallCentre, ballRadius, nextBallCentre, ballVelocity, acceleration);
	std::vector<int> objTopLeftCorner = { 20,4 }; /*Obj rectangle with centre x,y*/
	auto object = std::make_shared<Rectangle>(objTopLeftCorner, 2, 2);
	int thetaFromXDir = 0; /*parallel with x direction*/
	int currentTime = 0;
	int dt = 1;
	bool collision = false;
	while (!collision) {
		// check if we can move our ball without collision
		pinball->nextCentre[0] = pinball->currentCentre[0] + pinball->velocity[0] * dt;
		if (!collisionCheck(pinball,object)) {
			//
			pinball->velocity[0] += dt; //v(i+1) = v(t) + acc*dt
			pinball->currentCentre[0] = pinball->nextCentre[0];
			currentTime += dt;
			printf("NO COLLISION AT CENTRE (%d,%d) \n", pinball->currentCentre[0], pinball->currentCentre[1]);
		}
		else
		{
			printf("COLLISION WHEN CENTRE OF BALL AT (%d,%d) \n", pinball->currentCentre[0], pinball->currentCentre[1]);
			collision = true;
		}
	}
}