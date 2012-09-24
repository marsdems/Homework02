/*
 * @file Circle.cpp
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
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"
#include "Circle.h"
#include "Node.h"
#include "cinder/Rand.h";
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "Resources.h"

using namespace ci;
using namespace ci::app;
using namespace std;
int counter;

Circle::Circle(Vec2f center, float radius, ColorA c1) {	
	center_ = center;
	radius_ = radius;
	color_ = c1;
	counter = 0;
}

void Circle::update() {

}

// Referenced this method's code from Cooper Riley
bool Circle::isPointInside(Vec2i point){
	return (sqrt(pow((point.x-center_.x),2)+pow((point.y-center_.y),2))<=radius_);
}

void Circle::draw() {
	gl::enableAlphaBlending;
	//Draws the outer circle which makes the 'rings'
	gl::color(color_);
	gl::drawSolidCircle(center_, radius_);

	//Draws the inner circle, with a high level of transparency
	gl::color(ColorA(120,120,120, 0.5f));
	gl::drawSolidCircle(center_, radius_-5);	
}