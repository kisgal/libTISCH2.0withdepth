/*************************************************************************\
*    Part of the TISCH framework - see http://tisch.sourceforge.net/      *
*   Copyright (c) 2006 - 2011 by Florian Echtler <floe@butterbrot.org>    *
*   Licensed under GNU Lesser General Public License (LGPL) 3 or later    *
\*************************************************************************/

#include "BlobList.h"

#include <sstream>


// static global ID counter for all TUIO entities
int gid = 0;


// create new BlobList from a {0,255}-image
BlobList::BlobList( TiXmlElement* _config, Filter* _input ): Filter( _config, _input ) {

	blobs = oldblobs = NULL;
	reset();

	checkImage();
	parent = 0;

	width  = image->getWidth();
	height = image->getHeight();

	type  = 0;
	hflip = 0;
	vflip = 0;

	minsize = 50;
	maxsize = 0;

	factor = 1.5;
	radius = 20;
	peakmode = 0.0;
	ignore_orphans = 0;

	// try to read settings from XML
	config->QueryIntAttribute( "Type",  &type  );
	config->QueryIntAttribute( "HFlip", &hflip );
	config->QueryIntAttribute( "VFlip", &vflip );
	config->QueryIntAttribute( "IgnoreOrphans", &ignore_orphans );

	config->QueryIntAttribute( "MinSize",  &minsize  );
	config->QueryIntAttribute( "MaxSize",  &maxsize  );

	config->QueryDoubleAttribute( "TrackRadius", &radius   );
	config->QueryDoubleAttribute( "PeakFactor",  &factor   );
	config->QueryDoubleAttribute( "PeakMode",    &peakmode );
	//config->QueryIntAttribute( "CrossColor", &cross);
	//config->QueryIntAttribute( "TrailColor", &trail);

	// setting variables for Configurator
	countOfOptions = 5; // quantity of variables that can be manipulated
}

BlobList::~BlobList() {
	delete blobs;
	delete oldblobs;
}

void BlobList::reset() {
	delete blobs;
	delete oldblobs;
	blobs = new std::vector<Blob>;
	oldblobs = NULL;
}

void BlobList::link( Filter* _link ) {
	parent = dynamic_cast<BlobList*>(_link);
}


int BlobList::process() {

	// swap blob lists
	delete oldblobs;
	oldblobs = blobs;
	blobs = new std::vector<Blob>;

	// clone the input image
	*image = *(input->getImage());
	if(!useIntensityImage) 
	{
		*shortimage = *(input->getShortImage());
		shortimage->convert(*image);
	}

	// frame-local blob counter to differentiate between blobs
	
	unsigned char value = 254;
	// scan for bright spots
	unsigned char* data = image->getData();
	for (int i = 0; i < width*height; i++) 
		if (data[i] == 255) try {
		

		// try to create a new blob. throws if blob too small, continues silently.
		blobs->push_back( Blob( image, Point(i%width,i/width), value, gid, minsize, maxsize ) );

		// adjust counters
		value--;
		gid++;

		// did the frame-local blob counter overflow?
		if (value == 0) {
			value = 254;
			std::cerr << "Warning: too many type " << type << " blobs!" << std::endl;
		}

	} catch (...) { }

	else if(data[i] < 240 && data[i] > 10) try {


//	std::cout << "ITS WORKING MOTHERFUCKER!!!!!" << std::endl;
	// create a blob if depth is 10 (depth shades?) higher then threshmax and less then the value given to pixels within the threshold (max depth), throws exception if blob is too small
		blobs->push_back( Blob( image, Point(i%width,i/width), data[i], gid, minsize, 65535 ) );

		// adjust counters
		//data[i]--;
		gid++;

		// did the frame-local blob counter overflow?
		if (value == 0) {
			value = 254;
			std::cerr << "Warning: too many type " << type << " blobs!" << std::endl;
		}	


	} catch(...) {}
	

	// ---------------------------------------------------------------------------
	// tracking: update IDs from a previous list
	if (!oldblobs) return 0;

	// for each old blob: find the nearest new blob at the predicted location
	for ( std::vector<Blob>::iterator oldblob = oldblobs->begin(); oldblob != oldblobs->end(); oldblob++ ) {

		double speed = oldblob->speed.length();
		Vector newpos = oldblob->pos + oldblob->speed;

		double mindist = speed + radius;
		std::vector<Blob>::iterator nearest = blobs->end();

		// find closest new blob within search radius (that hasn't yet been assigned)
		for ( std::vector<Blob>::iterator newblob = blobs->begin(); newblob != blobs->end(); newblob++ ) {
			if (newblob->tracked) continue;
			Vector delta = newblob->pos - newpos;
			double dist = delta.length();
			if (dist < mindist) {
				mindist = dist;
				nearest = newblob;
			}
		}

		// if new blob found, assign previous id/peak/speed and remove from search list
		if ( nearest != blobs->end() ) {
			nearest->id = oldblob->id;
			nearest->peak = oldblob->peak;
			nearest->speed = nearest->pos - oldblob->pos;
			nearest->tracked = oldblob->tracked + 1;
		}
	}

	// ---------------------------------------------------------------------------
	// for each new blob: find peak according to old peak, major and minor axis
	for ( std::vector<Blob>::iterator blob = blobs->begin(); blob != blobs->end(); blob++ )
		blob->setPeak( image, factor, peakmode );

	// ---------------------------------------------------------------------------
	// TODO: allow disabling this feature (even if parent set)
	// find parent IDs from another list (if available)
	if (!parent) return 0;
	std::vector<Blob>::iterator blob = blobs->begin(); 
	while ( blob != blobs->end() ) {
		unsigned char value = blob->scan( parent->image, factor );
		int pid = parent->getID( value );
		if (ignore_orphans && !pid) blob = blobs->erase( blob );
		else { blob->pid = pid; blob++; }
	}

	return 0;
}


// retrieve a GID using a frame-local value
int BlobList::getID( unsigned char value ) {
	if (value == 0) return 0;
	for ( std::vector<Blob>::iterator blob = blobs->begin(); blob != blobs->end(); blob++ )
		if (blob->value == value) return blob->id;
	return 0;
}


// draw the entire list to a window, taking care to minimize GL state switches
void BlobList::draw( GLUTWindow* win ) {

	double xoff,yoff,height,size;
	height = win->getHeight();

	win->show( *image, 0, 0 );

	glTranslatef(0,0,500); // FIXME: compensate video image default z offset
	glLineWidth(2.0);

	// draw trails
	// glColor4f( trail.x, trail.y, trail.z, 1.0 );
	glColor4f( 0.0, 0.0, 1.0, 1.0 );
	glBegin( GL_LINES );

	for ( std::vector<Blob>::iterator blob = blobs->begin(); blob != blobs->end(); blob++ ) {

		xoff = blob->pos.x;
		yoff = height - blob->pos.y;

		glVertex2d( xoff, yoff );
		glVertex2d( xoff - blob->speed.x, yoff + blob->speed.y );
	}

	glEnd();

	// draw size-adjusted crosshairs
	//glColor4f( cross.x, cross.y, cross.z, 1.0 );
	glColor4f( 0.0, 1.0, 0.0, 1.0 );
	glBegin( GL_LINES );

	for ( std::vector<Blob>::iterator blob = blobs->begin(); blob != blobs->end(); blob++ ) {

		xoff = blob->pos.x;
		yoff = height - blob->pos.y;
		size = sqrt((double)blob->size)/factor;

		glVertex2d( xoff - blob->axis1.x, yoff + blob->axis1.y );
		glVertex2d( xoff + blob->axis1.x, yoff - blob->axis1.y );

		glVertex2d( xoff - blob->axis2.x, yoff + blob->axis2.y );
		glVertex2d( xoff + blob->axis2.x, yoff - blob->axis2.y );

		/*glVertex2f( xoff - size, yoff );
		glVertex2f( xoff + size, yoff );
		glVertex2f( xoff, yoff - size );
		glVertex2f( xoff, yoff + size );*/
	}

	glEnd();

	// print IDs (and parent IDs)
	for ( std::vector<Blob>::iterator blob = blobs->begin(); blob != blobs->end(); blob++ ) {
		std::ostringstream tmp;
		tmp << blob->id; if (blob->pid) tmp << "." << blob->pid;
		win->print( tmp.str(), (int)blob->peak.x, (int)blob->peak.y );
	}
}


// send blob list via OSC as TUIO 2.0
void BlobList::send( TUIOOutStream* oscOut ) {

	for (std::vector<Blob>::iterator it = blobs->begin(); it != blobs->end(); it++) {

		BasicBlob tmp = *it;
		tmp.type = type;

		tmp.pos.x  = tmp.pos.x  / (double)width; tmp.pos.y  = tmp.pos.y  / (double)height;
		tmp.peak.x = tmp.peak.x / (double)width; tmp.peak.y = tmp.peak.y / (double)height;

		if (hflip) {
			tmp.pos.x  = 1.0 - tmp.pos.x;
			tmp.peak.x = 1.0 - tmp.peak.x;
		}

		if (vflip) {
			tmp.pos.y  = 1.0 - tmp.pos.y;
			tmp.peak.y = 1.0 - tmp.peak.y;
		}

		*oscOut << tmp;
	}
}

const char* BlobList::getOptionName(int option) {
	const char* OptionName = "";

	switch(option) {
	case 0:
		OptionName = "Horizontal Flip";
		break;
	case 1:
		OptionName = "Vertical Flip";
		break;
	case 2:
		OptionName = "Minimum Size";
		break;
	case 3:
		OptionName = "Maximum Size";
		break;
	case 4:
		OptionName = "Peakmode";
		break;
	default:
		// leave OptionName empty
		break;
	}

	return OptionName;
}

double BlobList::getOptionValue(int option) {
	double OptionValue = -1.0;

	switch(option) {
	case 0:
		OptionValue = hflip;
		break;
	case 1:
		OptionValue = vflip;
		break;
	case 2:
		OptionValue = minsize;
		break;
	case 3:
		OptionValue = maxsize;
		break;
	case 4:
		OptionValue = peakmode;
		break;
	default:
		// leave OptionValue = -1.0
		break;
	}

	return OptionValue;
}

void BlobList::modifyOptionValue(double delta, bool overwrite) {
	switch(toggle) {
	case 0: // hflip is a boolean value
		if(overwrite) {
			hflip = (delta == 0 ? 0 : (delta == 1 ? 1 : hflip));
		} else {
			hflip += delta;
			hflip = (hflip < 0) ? 0 : (hflip > 1) ? 1 : hflip;
		}
		break;
	case 1: // vflip is a boolean value
		if(overwrite) {
			vflip = (delta == 0 ? 0 : (delta == 1 ? 1 : vflip));
		} else {
			vflip += delta;
			vflip = (vflip < 0) ? 0 : (vflip > 1) ? 1 : vflip;
		}
		break;
	case 2:
		if(overwrite) {
			minsize = (delta < 0) ? 0 : (delta > MAX_VALUE) ? MAX_VALUE : delta;
		} else {
			minsize += delta;
			minsize = (minsize < 0) ? 0 : (minsize > MAX_VALUE) ? MAX_VALUE : minsize;
		}
		break;
	case 3:
		if(overwrite) {
			maxsize = (delta < 0) ? 0 : (delta > MAX_VALUE) ? MAX_VALUE : delta;
		} else {
			maxsize += delta;
			maxsize = (maxsize < 0) ? 0 : (maxsize > MAX_VALUE) ? MAX_VALUE : maxsize;
		}
		break;
	case 4:
		if(overwrite) {
			peakmode = (delta < -MAX_VALUE) ? -MAX_VALUE : (delta > MAX_VALUE) ? MAX_VALUE : delta;
		} else {
			peakmode += delta;
			peakmode = (peakmode < -MAX_VALUE) ? -MAX_VALUE : (peakmode > MAX_VALUE) ? MAX_VALUE : peakmode;
		}
		break;
	}
}

TiXmlElement* BlobList::getXMLRepresentation() {
	TiXmlElement* XMLNode = new TiXmlElement( "BlobFilter" );
	
	XMLNode->SetAttribute( "IgnoreOrphans", ignore_orphans );
	XMLNode->SetAttribute( "MinSize",  minsize );
	XMLNode->SetAttribute( "MaxSize",  maxsize );
	XMLNode->SetAttribute( "PeakMode", peakmode );
	XMLNode->SetAttribute( "HFlip", hflip );
	XMLNode->SetAttribute( "VFlip", vflip );
	XMLNode->SetAttribute( "Type",  type  );
	XMLNode->SetAttribute( "TrackRadius", radius );
	XMLNode->SetAttribute( "PeakFactor", factor );
	
	return XMLNode;
}
