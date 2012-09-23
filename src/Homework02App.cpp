#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Homework02App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void Homework02App::setup()
{
}

void Homework02App::mouseDown( MouseEvent event )
{
}

void Homework02App::update()
{
}

void Homework02App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_BASIC( Homework02App, RendererGl )
