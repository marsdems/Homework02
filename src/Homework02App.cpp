/*
 * @file Homework02App.cpp
 * An app that fulfills certain requirements for Homework02
 *
 * @author Mike Marsden
 * @date 2012-09-23
 *
 * @note This file is (c) 2012. It is licensed under the 
 * CC BY 3.0 license (http://creativecommons.org/licenses/by/3.0/),
 * which means you are free to use, share, and remix it as long as you
 * give attribution. Commercial uses are allowed.
 *
 * This program satisfies the following requirements: A (linked list), B(message displayed),
 * C (re-order items by click), E(reverse items by keyboard), G (utilizing transparency).
 *
 * For stretch goals, I was unable to complete any of them. My goal was to try and incorporate 
 */ 
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Circle.h"
#include "Node.h"
#include "cinder/app/AppNative.h"
#include "cinder/gl/Texture.h"
#include "cinder/Text.h"
#include "cinder/Rand.h"
#include "cinder/gl/TextureFont.h"
#include "cinder/Utilities.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Homework02App : public AppBasic {
  public:
	void setup();
	void keyDown(KeyEvent event);
	void mouseDown(MouseEvent event);	
	void update();
	void draw();
	void prepareSettings(Settings* settings);
	void bringClickedToFront(Node* clicked_node);
	void reverse(Node* sentinel);
	Node* getClickedNode(Vec2i click);

	bool toggleOn;
	Font				mFont;
	Font				tempFont;
	Font				answerFont;
	gl::TextureFontRef	mTextureFont;
private:
	static const int kAppWidth=800;
	static const int kAppHeight=600;
	static const int kTextureSize=1024;

	// Declares the necessary node*
	Node *sentinel;
	Node *nodeOne;
	Node *nodeTwo;
	Node *nodeThree;
	Node *nodeFour;
	Node *nodeFive;

	// Declaring the "olympic rings"
	Circle *blueCircle;
	Circle *yellowCircle;
	Circle *blackCircle;
	Circle *greenCircle;
	Circle *redCircle;

	int frame_number_;
};

void Homework02App::prepareSettings(Settings* settings){
	settings->setWindowSize(kAppWidth,kAppHeight);
	settings->setResizable(false);
}

void Homework02App::setup()
{
	frame_number_ = 0;
	mFont = Font("Times New Roman", 28);
	tempFont = Font("", 0);
	answerFont = Font("Times New Roman", 28);
	mTextureFont = gl::TextureFont::create(mFont);
	toggleOn = true;

	//makes the "olympic' circles
	blueCircle = new Circle(Vec2f(400, 400), 50, ColorA(0,0,255,.75f));
	yellowCircle = new Circle(Vec2f(450,450), 50, ColorA(255,255,0,.75f));
	blackCircle = new Circle(Vec2f(500,400), 50, ColorA(0,0,0,.75f));
	greenCircle = new Circle(Vec2f(550,450), 50, ColorA(0,255,0,.75f));
	redCircle = new Circle(Vec2f(600,400), 50, ColorA(255,0,0,.75f));

	//Makes each of the circles to the linked list as a node
	nodeOne = new Node(blueCircle);
	nodeTwo = new Node(yellowCircle);
	nodeThree = new Node(blackCircle);
	nodeFour = new Node(greenCircle);
	nodeFive = new Node(redCircle);

	//makes the sentinel's next the first, and its previous the fifth circle
	sentinel = new Node(nodeOne, nodeFive);

	// 'Links' up the nodes from sentinel, to the five circles one by one
	// Uses a doubly-linked circular linked list
	nodeOne -> addNodePointers(nodeTwo, sentinel);
	nodeTwo -> addNodePointers(nodeThree, nodeOne);
	nodeThree -> addNodePointers(nodeFour, nodeTwo);
	nodeFour -> addNodePointers(nodeFive, nodeThree);
	nodeFive -> addNodePointers(sentinel, nodeFour);
}

void Homework02App::keyDown(KeyEvent event)
{	
	//Handles if the user wishes to toggle the instructions on and off. 
	switch(event.getChar()) {
		case '?':
			if (toggleOn)
			{
			mFont = Font(mFont.getName(), mFont.getSize());
			mTextureFont = gl::TextureFont::create(mFont);
			toggleOn = false;
			}

			else if (toggleOn == false) 
			{
			tempFont = Font("", 0);
			mTextureFont = gl::TextureFont::create(tempFont);
			toggleOn = true;
			}
		break;
		
		// Handles if the user wishes to reverse the items 
		case 'R':
		case 'r':
			reverse(sentinel);
		break;

		case 'A':
		case 'a':
	
		break;
	}
}

Node* Homework02App::getClickedNode(Vec2i click) {
	Node* selected_node = sentinel -> previous_;
	Node* current_ = sentinel -> next_;

	//While loop cycles through the linked list
	while(current_ != sentinel){
		//Only updates selected_node if the circle is inside the click
		if(current_ -> isPointInside(click))
			selected_node = current_;
		current_ = current_ -> next_;
	}
	return selected_node;
}
void Homework02App::bringClickedToFront(Node* clicked_node){
	clicked_node -> previous_ -> next_ = clicked_node -> next_;
	clicked_node -> next_ -> previous_ = clicked_node -> previous_;
	clicked_node -> next_ = sentinel;
	clicked_node -> previous_ = sentinel -> previous_;
	sentinel -> previous_ -> next_ = clicked_node;
	sentinel -> previous_ = clicked_node;
}

// Referenced from notes from class lecture
void Homework02App::reverse(Node* sentinel) {
	Node* cur = sentinel;
	do {
		Node* temp = cur-> next_;
		cur->next_ = cur-> previous_;
		cur->previous_ = temp;
		cur = cur -> previous_;
	} while (cur != sentinel);
}

void Homework02App::mouseDown(MouseEvent event)
{
	Vec2i click = event.getPos();
	Node *selected_node = getClickedNode(click);

	if(selected_node != NULL)
		bringClickedToFront(selected_node); 
}

void Homework02App::update()
{

	//This code doesn't seem to do anything other than interating through
	//Your linked list and using up memory.
	
	/*
	frame_number_++;

	Node* current_ = sentinel -> next_;
	do{
		current_  = current_ -> next_;
	} while(current_ != sentinel);
	*/
}

void Homework02App::draw()
{
	/*
	I think a better way to impliment all this code in your draw() method
	would be to have it in seperate methods that could be called more easily.
	This would also cut down the clutter in this method and make your code more readable
	*/

	gl::enableAlphaBlending();
	gl::clear(Color(120,120,120));

	//Draws the 12 squares for the background
	//Row 1
	gl::color(ColorA(255,0,0,.5f));
	gl::drawSolidRect(Rectf(0,0,200,200), false);	
	gl::color(ColorA(255,255,0,.5f));
	gl::drawSolidRect(Rectf(200,0,400,200), false);
	gl::color(ColorA(0,0,255,.5f));
	gl::drawSolidRect(Rectf(400,0,600,200), false);
	gl::color(ColorA(0,255,0,.5f));
	gl::drawSolidRect(Rectf(600,0,800,200), false);

	//Row 2
	gl::color(ColorA(0,255,0,.5f));
	gl::drawSolidRect(Rectf(0,200,200,400), false);	
	gl::color(ColorA(255,0,0,.5f));
	gl::drawSolidRect(Rectf(200,200,400,400), false);
	gl::color(ColorA(255,255,0,.5f));
	gl::drawSolidRect(Rectf(400,200,600,400), false);
	gl::color(ColorA(0,0,255,.5f));
	gl::drawSolidRect(Rectf(600,200,800,400), false);

	//Row 3
	gl::color(ColorA(0,0,255,.5f));
	gl::drawSolidRect(Rectf(0,400,200,600), false);	
	gl::color(ColorA(0,255,0,.5f));
	gl::drawSolidRect(Rectf(200,400,400,600), false);
	gl::color(ColorA(255,0,0,.5f));
	gl::drawSolidRect(Rectf(400,400,600,600), false);
	gl::color(ColorA(255,255,0,.5f));
	gl::drawSolidRect(Rectf(600,400,800,600), false);

	//Inner Row 1
	gl::color(ColorA(255,0,0,.5f));
	gl::drawSolidRect(Rectf(100,100,300,300), false);	
	gl::color(ColorA(0,255,0,.5f));
	gl::drawSolidRect(Rectf(300,100,500,300), false);
	gl::color(ColorA(0,0,255,.5f));
	gl::drawSolidRect(Rectf(500,100,700,300), false);

	//Inner Row 2
	gl::color(ColorA(0,0,255,.5f));
	gl::drawSolidRect(Rectf(100,300,300,500), false);	
	gl::color(ColorA(255,0,0,.5f));
	gl::drawSolidRect(Rectf(300,300,500,500), false);
	gl::color(ColorA(0,255,255,.5f));
	gl::drawSolidRect(Rectf(500,300,700,500), false);

	//Creates the string for instructions
	std::string str( "Click any of the rings to bring them to the front of the screen. Press 'R' to reverse the order of the rings. Press '?' to toggle these instructions on/off the screen. Mini-game: Count the number of squares displayed on the screen! (squares underneath squares count, but the border of the program is not a square) Tweet @mmarsden5 with your answer and be the first to win!");
	Rectf boundsRect( 40, mTextureFont->getAscent() + 40, getWindowWidth() - 40, getWindowHeight() - 40 );

	//Text color
	ColorA semiTransparent = ColorA(0,0,0,.9f);
	gl::color(semiTransparent);
	mTextureFont->drawStringWrapped( str, boundsRect );

	Node* current_ = sentinel -> next_;
	do{
		current_ -> draw();
		current_  = current_ -> next_;
	} while(current_ != sentinel);

}

CINDER_APP_BASIC( Homework02App, RendererGl )
