/*
 * @file Node.cpp
 * A node class
 *
 * @author Mike Marsden
 * @date 2012-09-23
 *
 * @note This file is (c) 2012. It is licensed under the 
 * CC BY 3.0 license (http://creativecommons.org/licenses/by/3.0/),
 * which means you are free to use, share, and remix it as long as you
 * give attribution. Commercial uses are allowed.
 */ 

#include "Node.h"

Node::Node(Circle*nodeData, Node *next, Node *prev){
	nodeData_ = nodeData;
	next_ = next;
	previous_ = prev;
}

// Node with data from a Circle 
Node::Node(Circle *nodeData){
	nodeData_ = nodeData;
}

// Node with next and previous pointers
Node::Node(Node *next, Node *prev){
	next_ = next;
	previous_ = prev;
}

// Adds a new link for a pointer with next and previous pointers
void Node::addNodePointers(Node *next_node, Node *prev_node){
	next_ = next_node;
	previous_ = prev_node;
}

bool Node::isPointInside(Vec2i point){
	return nodeData_ -> isPointInside(point);
}

void Node::draw(){
	nodeData_ -> draw();
}