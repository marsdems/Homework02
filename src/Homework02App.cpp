#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Circle.h"
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
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
	Circle* circle_list_;
	static const int kAppWidth=1280;
	static const int kAppHeight=720;
};


void Homework02App::prepareSettings(Settings* settings){
	settings->setWindowSize(kAppWidth,kAppHeight);
	settings->setResizable(false);
}

void Homework02App::setup()
{
	mFont = Font("Times New Roman", 28);
	tempFont = Font("", 0);
	mTextureFont = gl::TextureFont::create(mFont);
	toggleOn = true;
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
}

void Homework02App::update()
{
}

void Homework02App::draw()
{
	gl::enableAlphaBlending();
	gl::clear( Color( 0, 0, 0 ) );
	
	std::string str( "Press '?' to toggle these instructions on/off the screen." );
	Rectf boundsRect( 40, mTextureFont->getAscent() + 40, getWindowWidth() - 40, getWindowHeight() - 40 );

	gl::color( ColorA( 1, 0.5f, 0.25f, 1.0f ) );

	mTextureFont->drawStringWrapped( str, boundsRect );
}

CINDER_APP_BASIC( Homework02App, RendererGl )
