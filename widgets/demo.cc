/*************************************************************************\
*    Part of the TISCH framework - see http://tisch.sourceforge.net/      *
*   Copyright (c) 2006 - 2011 by Florian Echtler <floe@butterbrot.org>    *
*   Licensed under GNU Lesser General Public License (LGPL) 3 or later    *
\*************************************************************************/

#include <stdlib.h>

#include "Slider.h"
#include "Window.h"
#include "Textbox.h"
#include "Checkbox.h"
#include "Tile.h"
#include "Dial.h"
#include "Label.h"

Label* lbl;

// This class demonstrates how to react to the predefined tap gesture using Button as superclass.
class MyButton: public Button {
	public:

		MyButton( int _w, int _h, int _x = 0, int _y = 0, double angle = 0.0, RGBATexture* _tex = 0 ):
			Button( _w,_h,_x,_y,angle,_tex) { }

		void tap( Vector pos, int id ) { lbl->set( " tap!" ); }
		void release( ) { lbl->set( " Button" ); }

		// example code for a "close" button:
		/*Container* foo = parent;
			foo->remove(this);
			delete foo; 
			delete this;
		*/	
};


int main( int argc, char* argv[] ) {

	std::cout << "demo - libTISCH 2.0 widget layer demo" << std::endl;
	std::cout << "(c) 2011 by Florian Echtler <floe@butterbrot.org>" << std::endl;

	// create a new window: width, height, title, use_mouse
	Window* win = new Window( 800, 480, "Widget Demo", 1 );
	win->texture( 0 );

	Container* foo = new Container( 400,300, 0, 0, M_PI*20/180, 0, 0xFF );
	win->add( foo );
	Slider * myslider = new Slider(0 ,60,20,-150,20 );	//ID,w,h,x,y
		foo->add( new Label( " fundamental", 200,20, -30,20 ) );		
	Slider * myslider1 = new Slider(1 ,60,20,-150,-20 );	
		foo->add( new Label( " partial1", 200,20, -30,-20 ) );	
	Slider * myslider2 = new Slider(2 ,60,20,-150,-60 );	
		foo->add( new Label( " partial2", 200,20, -30,-60 ) );	
	Slider * myslider3 = new Slider(3 ,60,20,-150,-100 );
		foo->add( new Label( " partial3", 200,20, -30,-100 ) );	
	Slider * myslider4 = new Slider(4,60,20,-150,-140 );	
		foo->add( new Label( " partial4", 200,20, -30,-140 ) );	
	foo->add( myslider );
	foo->add( myslider2 );
	foo->add( myslider3 );
	foo->add( myslider4 );
	foo->add( myslider1 );
//	foo->add( new Label( " Slider", 200,20, -30,20 ) );

	win->update();
	win->run();


}




