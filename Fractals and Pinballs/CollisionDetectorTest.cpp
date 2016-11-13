#include "CollisionDetectorTest.h"


double CollisionDetectorTest::findClosestPoint(double value, double min, double max) {
	double distFromMinExtent = abs(min - value);
	double distFromMaxExtent = abs(max - value);
	if (distFromMinExtent < distFromMaxExtent) { return min; }
	else { return max; }
}


bool CollisionDetectorTest::collisionCheck(std::shared_ptr<Ball> pinball, std::shared_ptr<Rectangle> obj) {
	std::vector<double> halfObjExtents = {obj->width / 2, obj->height / 2 };
	//COMPUTE CLOSEST X POINT OF RECTANGLE TO CIRCLE CENTRE X
	double closestXPoint = findClosestPoint(pinball->currentCentre[0], obj->topLeftCorner[0], obj->topLeftCorner[0] + obj->width);
	double closestYPoint = findClosestPoint(pinball->currentCentre[1], obj->topLeftCorner[1] - obj->height, obj->topLeftCorner[0]);
	if (pinball->nextCentre[0] > obj->topLeftCorner[0] + obj->width && obj->topLeftCorner[1] - obj->height) { return false; }
	//COMPUTE DISTANCE BETWEEN CIRCLE CENTER AND CLOSEST RECTANGLE POINT
	double xDistance = abs(pinball->currentCentre[0] - closestXPoint);
	double yDistance = abs(pinball->currentCentre[1] - closestYPoint);
	//WHEN DISTANCE SQUARED < RADIUS SQUARED WE GET A HIT
	double distanceFromCircleSquared = (int)pow(xDistance,2) + (int)pow(yDistance,2);
	return (distanceFromCircleSquared <= (int)pow(pinball->radius,2));
}

void CollisionDetectorTest::fileWriter(std::ofstream &file, std::string text, const std::shared_ptr<Ball> &pinball, const std::shared_ptr<Rectangle> &rect) {
	if (file.is_open()) {
		file << "BEGIN \n"  << "OBJECTS:" << "Pinball" << ", Rectangle \n" 
			 << "OBJECT 1: " << pinball->radius << "\n"
			 << "OBJECT 2: " << rect->topLeftCorner[0] << "," << rect->topLeftCorner[1] << "," << rect->height << ","
			 << rect->width  << "\n" << "OBJECT 1 POSITIONS: \n"
			 << text << "END \n";
		file.close();
	}
	else std::cout << "File could not be opened. \n";
}

void CollisionDetectorTest::testCollision() {
	/*initial parameters of simulation*/
	std::vector<double> currentBallCentre = { 0.0,0.0 };
	std::vector<double> nextBallCentre = { 0.0,0.0 };
	std::vector<double> ballVelocity = { 1.0,0.0 };
	std::vector<double> acceleration = { 1.0,0.0 };
	double ballRadius = 2.0;
	auto pinball = std::make_shared<Ball>(currentBallCentre, ballRadius, nextBallCentre, ballVelocity, acceleration);
	std::vector<double> objTopLeftCorner = { 20.0,2.0 }; /*Obj rectangle with centre x,y*/
	auto object = std::make_shared<Rectangle>(objTopLeftCorner, 2.0, 2.0);
	double thetaFromXDir = 0.0; /*parallel with x direction*/
	double currentTime = 0.0;
	double dt = 1.0;
	bool collision = false;
	std::stringstream tempOutputText;
	std::ofstream outputFile("M:\\Documents\\Coursework\\FractalsAndPinball\\FractalsAndPinballs\\x64\\Debug\\Run1.txt");
	while (!collision) {
		// check if we can move our ball without collision
		pinball->nextCentre[0] = pinball->currentCentre[0] + pinball->velocity[0] * dt;
		if (!collisionCheck(pinball, object)) {
			double currentCentreX = pinball->currentCentre[0];
			double currentCentreY = pinball->currentCentre[1];
			tempOutputText << pinball->currentCentre[0] << "," << pinball->currentCentre[1] << "\n";
			pinball->velocity[0] += dt; //v(i+1) = v(t) + acc*dt
			pinball->currentCentre[0] = pinball->nextCentre[0];
			currentTime += dt;
			printf("NO COLLISION AT CENTRE (%f,%f) \n", pinball->currentCentre[0], pinball->currentCentre[1]);
		}
		else
		{
			tempOutputText << pinball->currentCentre[0] << "," << pinball->currentCentre[1] << "\n";
			printf("COLLISION WHEN CENTRE OF BALL AT (%f,%f) \n", pinball->currentCentre[0], pinball->currentCentre[1]);
			collision = true;
		}
	}
	std::string output = tempOutputText.str();
	fileWriter(outputFile, output, pinball, object);
}