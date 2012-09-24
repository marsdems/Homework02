#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Circle.h"
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

	bool toggleOn;
	Font				mFont;
	Font				tempFont;
	gl::TextureFontRef	mTextureFont;
private:
	Circle* circleList_;
	static const int kAppWidth=800;
	static const int kAppHeight=600;
	static const int kTextureSize=1024;
	static const Vec2f kX;
	static const Vec2f kY;

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

	Vec2f pos = (kAppWidth/2.0f)* kX + (kAppHeight/2.0f) * kY;
	circleList_= new Circle(4, pos, Vec2f(0,0), kAppHeight/2.0f);
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

void Homework02App::mouseDown( MouseEvent event )
{
	//Vec2f mousePoint = Vec2f((float)event.getX(), (float)event.getY());
	//gl::drawSolidCircle(mousePoint, 30, 0);
}

void Homework02App::update()
{
	Circle* cur = circleList_;
	Vec2f center = kX * kAppWidth/2.0 + kY * kAppHeight/2.0;
	 
	if (cur != NULL) {
		do {
			cur-> update(center, kAppWidth/2.0);
			cur = cur->next_;
		} while (cur != circleList_);
	} 
	frame_number_++;
}

void Homework02App::draw()
{
	gl::enableAlphaBlending();
	gl::clear(Color(0,0,0));

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

	Circle* cur = circleList_;
	
	if(cur != NULL){
		do {
			cur->draw(getMousePos());
			cur = cur->next_;
		} while (cur != circleList_);
	} 
}

CINDER_APP_BASIC( Homework02App, RendererGl )
