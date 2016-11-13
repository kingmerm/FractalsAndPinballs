#ifndef COLLISIONDETECTORTEST_H
#define COLLISIONDETECTORTEST_H
#include "Rectangle.h"
#include "Ball.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
class CollisionDetectorTest
{
public:
	CollisionDetectorTest() {};
	double findClosestPoint(double value, double min, double max);
	bool collisionCheck(std::shared_ptr<Ball> pinball, std::shared_ptr<Rectangle> rect);
	void fileWriter(std::ofstream &file, std::string text, const std::shared_ptr<Ball> &pinball, const std::shared_ptr<Rectangle> &rect);
	void testCollision();
};
#endif
