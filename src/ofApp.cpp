#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	width = ofGetWindowWidth();
	height = ofGetWindowHeight();
	ind_playing_movie = 0;
	
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

	kome = new ofImage*[13];
	anime_widths = new int[13];
	anime_heights = new int[13];
	
	for (int i = 0; i < 13; i++) {
		string ind_str = ofToString(i+1);
		if (i < 10) {
			ind_str = "0" + ind_str;
		}
		cout << ind_str << endl;
		kome[i] = new ofImage[ n_imgs[i] ];
		for(int j = 0; j < n_imgs[i]; j++) {
			cout << "kome/"+ind_str+"/frame" + to_string(j+1) + ".jpg" << endl;
			kome[i][j].load("kome/"+ind_str+"/frame" + to_string(j+1) + ".jpg");
		}
		anime_heights[i] = height;
		anime_widths[i] = kome[i][0].getWidth() * height / kome[i][0].getHeight();
	}
	
	ind_anime = 0;
	timer_anime = 300;
	last_time = 0;
	ind_playing_anime = 3;
}

//--------------------------------------------------------------
void ofApp::update(){

	movies[ind_playing_movie].update();
	int cur_time = ofGetElapsedTimeMillis();
	if (cur_time - last_time > timer_anime ) {
		ind_anime++;
		if (ind_anime > n_imgs[ind_playing_anime]-1) {
			ind_anime = 0;
		}
		last_time = cur_time;
	}
}

void ofApp::exit(){
	delete [] movies;
	delete [] movieWidths;
	delete [] movieHeights;
	delete [] movieNeedsRotates;
	
	for (int i = 0; i < 13; i++) {
		delete [] kome[i];
	}
	delete [] kome;
	delete [] anime_heights;
	delete [] anime_widths;
}

//--------------------------------------------------------------
void ofApp::draw(){
//	ofBackground(0, 0, 0);
	ofBackground(255, 255, 255);

	ofTranslate(width/2, height/2);
//
//	if (movieNeedsRotates[ind_playing_movie]) {
//		ofRotate( -90 );
//	}
//	movies[ind_playing_movie].draw(-movieWidths[ind_playing_movie]/2, -movieHeights[ind_playing_movie]/2, movieWidths[ind_playing_movie], movieHeights[ind_playing_movie]);
//
	kome[ind_playing_anime][ind_anime].draw(-anime_widths[ind_playing_anime]/2, -anime_heights[ind_playing_anime]/2, anime_widths[ind_playing_anime], anime_heights[ind_playing_anime]);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
//	myPlayer.setSpeed( myPlayer.getSpeed() * -1  );
	if (key == '`') {
		movies[ind_playing_movie].stop();
		ind_playing_movie = 0;
		movies[ind_playing_movie].play();
	} else if (key == '1') {
		movies[ind_playing_movie].stop();
		ind_playing_movie = 1;
		movies[ind_playing_movie].play();
	}else if (key == '2') {
		movies[ind_playing_movie].stop();
		ind_playing_movie = 2;
		movies[ind_playing_movie].play();
	}else if (key == '3') {
		movies[ind_playing_movie].stop();
		ind_playing_movie = 3;
		movies[ind_playing_movie].play();
	}else if (key == '4') {
		movies[ind_playing_movie].stop();
		ind_playing_movie = 4;
		movies[ind_playing_movie].play();
	}else if (key == '5') {
		movies[ind_playing_movie].stop();
		ind_playing_movie = 5;
		movies[ind_playing_movie].play();
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
