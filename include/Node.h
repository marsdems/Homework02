/*
 * @file Node.h
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
#include "cinder\gl\gl.h"
#include "Circle.h"

using namespace ci;

class Node {
public:
	//Pointer for each node
	Circle *nodeData_;
	Node *next_;
	Node *previous_;

	//Various Node constructors
	Node(Circle *nodeData, Node *next, Node *previous);
	Node(Circle *nodeData);
	Node(Node *next, Node *previous);
	
	//Methods for nodes
	void addNodePointers(Node *next_node, Node *prev_node);
	void draw();
	bool isPointInside(Vec2i point);
};