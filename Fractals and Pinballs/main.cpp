#include "CollisionDetectorTest.h"
#include "Visualization.h"

int main(int argv, char* argsc[]) {
	auto tester = std::make_shared<CollisionDetectorTest>();
	auto visualizer = visualization_sptr();
    tester->testCollision();
	visualizer->initGraphics(argv, argsc);
}