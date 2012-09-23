/*
 * @file Circle.h
 * A circle that can contain multiple circles in itself.
 *
 * @author Mike Marsden
 * @date 2012-09-23
 *
 * @note This file is (c) 2012. It is licensed under the 
 * CC BY 3.0 license (http://creativecommons.org/licenses/by/3.0/),
 * which means you are free to use, share, and remix it as long as you
 * give attribution. Commercial uses are allowed.
 */ 

class Circle{
public:
	Circle(int depth, ci::Vec2f position, ci::Vec2f offset, float radius);
	
	//Pointers to my siblings
	Circle* next_;
	Circle* prev_;
	
	//Pointer to the sentinel for my list of children.
	Circle* children_;

	ci::Vec2f offset_; //From parent position
	ci::Vec2f position_; //position_ == parent's position + offset_
	float radius_;
	
	ci::Vec2f velocity_;
	
	//Return true of the (x,y) provided is inside the diamond
	bool isInside(float x, float y);
	void draw(ci::Vec2i mouse_pos);
	void update(ci::Vec2f parent_position, float parent_r);
	
	void addRandomChild(int depth);
};

void insertAfter(Circle* new_item, Circle* insert_here);