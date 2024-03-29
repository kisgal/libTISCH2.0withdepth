/*************************************************************************\
*    Part of the TISCH framework - see http://tisch.sourceforge.net/      *
*   Copyright (c) 2006 - 2011 by Florian Echtler <floe@butterbrot.org>    *
*   Licensed under GNU Lesser General Public License (LGPL) 3 or later    *
\*************************************************************************/

#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Widget.h"
#include "Texture.h"

class TISCH_SHARED Button: public Widget {

	public:
		int getID();
		Button( int _w, int _h, int _x = 0, int _y = 0, double angle = 0.0, RGBATexture* _tex = 0 , int id = 0);
		virtual ~Button(); 

		virtual void draw();
		virtual void action( Gesture* gesture );

		virtual void tap( Vector pos, int id );
		virtual void release();

	protected:
		int id;
		int active;
};

#endif // _BUTTON_H_

