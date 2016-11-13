#pragma once
#ifndef VISUALIZATION_H
#define VISUALIZATION_H
#include <time.h>
#include <memory>
#ifdef MACOSX
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Visualization
{
public:
	Visualization();
	void initGraphics(int argc, char *argv[]);
};
typedef std::shared_ptr<Visualization> visualization_sptr;

#endif