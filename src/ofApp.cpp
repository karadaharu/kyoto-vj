#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	width = ofGetWindowWidth();
	height = ofGetWindowHeight();
	indPlayingMovie = 0;
	
	movies = new ofVideoPlayer[6];
	movieNeedsRotates = new bool[6];
	movieWidths = new int[6];
	movieHeights = new int[6];
	
	movies[0].load("movie/001_17cut.mp4");
	movieNeedsRotates[0] = true;
	movieWidths[0] = height;
	movieHeights[0] = movies[0].getHeight() * height / movies[0].getWidth();
	
	
 	movies[1].load("movie/002_17cut.mp4");
	movieNeedsRotates[1] = false;
	movieWidths[1] = width;
	movieHeights[1] = movies[1].getHeight() * width / movies[1].getWidth();
	
	movies[2].load("movie/003.mp4");
	movieNeedsRotates[2] =false;
	movieWidths[2] = width;
	movieHeights[2] = movies[2].getHeight() * width / movies[2].getWidth();
	
	
	movies[3].load("movie/006_17-1.mp4");
	movieNeedsRotates[3] = false;
	movieWidths[3] = width;
	movieHeights[3] = movies[3].getHeight() * width / movies[3].getWidth();
	
	movies[4].load("movie/006_17-2.mp4");
	movieNeedsRotates[4] = false;
	movieWidths[4] = width;
	movieHeights[4] = movies[4].getHeight() * width / movies[4].getWidth();
	

	movies[5].load("movie/007.mp4");
	movieNeedsRotates[5] = true;
	movieWidths[5] = height;
	movieHeights[5] = movies[5].getHeight() * height / movies[5].getWidth();
	
	for(int i = 0; i < 6; i++) {
		movies[i].setLoopState(OF_LOOP_NORMAL);
	}

}

//--------------------------------------------------------------
void ofApp::update(){
	myPlayer.update();
	movies[indPlayingMovie].update();
}

void ofApp::exit(){
	delete [] movies;
	delete [] movieWidths;
	delete [] movieHeights;
	delete [] movieNeedsRotates;
}

//--------------------------------------------------------------
void ofApp::draw(){
//	ofBackground(0, 0, 0);
	ofBackground(255, 255, 255);

	ofTranslate(width/2, height/2);

	if (movieNeedsRotates[indPlayingMovie]) {
		ofRotate( -90 );
	}
	movies[indPlayingMovie].draw(-movieWidths[indPlayingMovie]/2, -movieHeights[indPlayingMovie]/2, movieWidths[indPlayingMovie], movieHeights[indPlayingMovie]);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
//	myPlayer.setSpeed( myPlayer.getSpeed() * -1  );
	if (key == '`') {
		movies[indPlayingMovie].stop();
		indPlayingMovie = 0;
		movies[indPlayingMovie].play();
	} else if (key == '1') {
		movies[indPlayingMovie].stop();
		indPlayingMovie = 1;
		movies[indPlayingMovie].play();
	}else if (key == '2') {
		movies[indPlayingMovie].stop();
		indPlayingMovie = 2;
		movies[indPlayingMovie].play();
	}else if (key == '3') {
		movies[indPlayingMovie].stop();
		indPlayingMovie = 3;
		movies[indPlayingMovie].play();
	}else if (key == '4') {
		movies[indPlayingMovie].stop();
		indPlayingMovie = 4;
		movies[indPlayingMovie].play();
	}else if (key == '5') {
		movies[indPlayingMovie].stop();
		indPlayingMovie = 5;
		movies[indPlayingMovie].play();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
