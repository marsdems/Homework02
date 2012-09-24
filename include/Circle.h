#ifndef CIRCLE_H
#define CIRCLE_H
/*
 * @file Circle.h
 * A circle class.
 *
 * @author Mike Marsden
 * @date 2012-09-23
 *
 * @note This file is (c) 2012. It is licensed under the 
 * CC BY 3.0 license (http://creativecommons.org/licenses/by/3.0/),
 * which means you are free to use, share, and remix it as long as you
 * give attribution. Commercial uses are allowed.
 */ 
#include "cinder\gl\gl.h"
using namespace ci;

class Circle {

public:	
	Circle(Vec2f center, float radius, ColorA c1);
	void update();
	void draw();
	bool isPointInside(Vec2i point);
private:
	Vec2f center_;
	float radius_;
	ColorA color_;
};

#endif