#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	// 16:9
	ofSetupOpenGL(1440,810,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
