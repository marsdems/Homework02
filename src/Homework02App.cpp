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
	void keyDown( KeyEvent event );
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void prepareSettings(Settings* settings);
	void bringClickedToFront(Node* clicked_node);

	bool toggleOn;
	Font				mFont;
	Font				tempFont;
	gl::TextureFontRef	mTextureFont;
private:
	static const int kAppWidth=800;
	static const int kAppHeight=600;
	static const int kTextureSize=1024;
	static const Vec2f kX;
	static const Vec2f kY;

	Node *sentinel;
	Node *nodeOne;
	Node *nodeTwo;
	Node *nodeThree;
	Node *nodeFour;
	Node *nodeFive;

	Circle *blueCircle;
	Circle *yellowCircle;
	Circle *blackCircle;
	Circle *greenCircle;
	Circle *redCircle;

	int frame_number_;
};

const Vec2f Homework02App::kX = Vec2f(.5f, -.5f);
const Vec2f Homework02App::kY = Vec2f(.5f, .5f);

void Homework02App::prepareSettings(Settings* settings){
	settings->setWindowSize(kAppWidth,kAppHeight);
	settings->setResizable(false);
}

void Homework02App::setup()
{
	frame_number_ = 0;
	mFont = Font("Times New Roman", 28);
	tempFont = Font("", 0);
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
		
		// Handles if the user wishes to reorder the items 
		case 'R':
		case 'r':


		break;

	}
}

void Homework02App::bringClickedToFront(Node* clicked_node){
	clicked_node -> previous_ -> next_ = clicked_node -> next_;
	clicked_node -> next_ -> previous_ = clicked_node -> previous_;

	clicked_node -> next_ = sentinel;
	clicked_node -> previous_ = sentinel -> previous_;

	sentinel -> previous_ -> next_ = clicked_node;
	sentinel -> previous_ = clicked_node;

}
void Homework02App::mouseDown( MouseEvent event )
{
	Vec2i click = event.getPos();

	Node *selected_node = getSelectedNode(click);

	if(selected_node != NULL)
		bringClickedToFront(selected_node);
}

void Homework02App::update()
{
	frame_number_++;

	Node* current_ = sentinel -> next_;
	do{
		//current_ -> moveShape(frame_number_);
		current_  = current_ -> next_;
	} while(current_ != sentinel);
}

void Homework02App::draw()
{
	gl::enableAlphaBlending();
	gl::clear(Color(120,120,120));

	gl::color(Color(255,0,0));
	gl::drawSolidRect(Rectf(0,0,200,200), false);
	gl::color(ColorA(0,0,255,.5f));
	gl::drawSolidRect(Rectf(100,100,300,300), false);
	gl::color(ColorA(0,255,0,.5f));
	gl::drawSolidRect(Rectf(200,200,400,400), false);
	
	//Creates the string for instructions
	std::string str( "Press '?' to toggle these instructions on/off the screen." );
	Rectf boundsRect( 40, mTextureFont->getAscent() + 40, getWindowWidth() - 40, getWindowHeight() - 40 );

	//Text color
	ColorA semiTransparent = ColorA(.0f,.5f,.0f,.9f);
	gl::color(semiTransparent);
	mTextureFont->drawStringWrapped( str, boundsRect );

	Node* current_ = sentinel -> next_;
	do{
		current_ -> draw();
		current_  = current_ -> next_;
	} while(current_ != sentinel);

}

CINDER_APP_BASIC( Homework02App, RendererGl )
