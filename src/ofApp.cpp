#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	width = ofGetWindowWidth();
	height = ofGetWindowHeight();

	n_movie = 3;
	movies = new ofVideoPlayer[n_movie];
	movieNeedsRotates = new bool[n_movie];
	movieWidths = new int[n_movie];
	movieHeights = new int[n_movie];
	movieFrameStarts = new int[n_movie];
	movieFrameEnds = new int[n_movie];
	
	movie_key_frames = new int*[n_movie];
	movie_key_frames[0] = new int[n_keys[0]];
	movie_key_frames[0][0] = 1;
	
	movie_key_frames[1] = new int[n_keys[1]];
	movie_key_frames[1][0] = 83;

	movie_key_frames[2] = new int[n_keys[2]];
	movie_key_frames[2][0] = 359;
	movie_key_frames[2][1] = 427;
	movie_key_frames[2][2] = 499;
	movie_key_frames[2][3] = 540;
	
	movies[1].load("movie/001_17cut.mp4");
	movieNeedsRotates[1] = true;
	movieWidths[1] = height;
	movieHeights[1] = movies[1].getHeight() * height / movies[1].getWidth();
	
	movies[0].load("movie/003.mp4");
	movieNeedsRotates[0] =false;
	movieWidths[0] = width;
	movieHeights[0] = movies[0].getHeight() * width / movies[0].getWidth();
	
	movies[2].load("movie/007.mp4");
	movieNeedsRotates[2] = true;
	movieWidths[2] = height;
	movieHeights[2] = movies[2].getHeight() * height / movies[2].getWidth();
	

	
// 	movies[1].load("movie/002_17cut.mp4");
//	movieNeedsRotates[1] = false;
//	movieWidths[1] = width;
//	movieHeights[1] = movies[1].getHeight() * width / movies[1].getWidth();
//	
//	movies[3].load("movie/006_17-1.mp4");
//	movieNeedsRotates[3] = false;
//	movieWidths[3] = width;
//	movieHeights[3] = movies[3].getHeight() * width / movies[3].getWidth();
//	
//	movies[4].load("movie/006_17-2.mp4");
//	movieNeedsRotates[4] = false;
//	movieWidths[4] = width;
//	movieHeights[4] = movies[4].getHeight() * width / movies[4].getWidth();
	
	for(int i = 0; i < n_movie; i++) {
		movies[i].setLoopState(OF_LOOP_NORMAL);
	}

	kome = new ofImage*[13];
	anime_widths = new int[13];
	anime_heights = new int[13];
	
	for (int i = 0; i < 13; i++) {
		string ind_str = ofToString(i+1);
		if (i+1 < 10) {
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
	
	ind_playing_movie = 0;
	movies[ind_playing_movie].play();
	
	ind_anime = 0;
	timer_anime = 100;

	last_time = 0;
	ind_playing_anime = 2;
	
	scene = 0;
	
	timer_movie = 4*1000*60/130;
	last_time_movie = 0;
	ind_timer_keys_scene0 = 0;
	
	cout << "movie:" << movies[0].isPlaying() << endl;
	last_key = 0;
}


void ofApp::updateScene0(){
	movies[ind_playing_movie].update();
	
	if (ind_timer_keys_scene0 <= 2 && cur_time_sec > timer_keys_scene0[ind_timer_keys_scene0] ) {
		ind_timer_keys_scene0++;
		if (ind_timer_keys_scene0 <= 2) {
			movies[ind_playing_movie].stop();
			ind_playing_movie = ind_timer_keys_scene0;
			movies[ind_playing_movie].play();
		}
	}
	
	if (ind_timer_keys_scene0 <= 2 && cur_time_sec > timer_keys_scene0[ind_timer_keys_scene0] ) {
		ind_timer_keys_scene0++;
		if (ind_timer_keys_scene0 <= 2) {
			movies[ind_playing_movie].stop();
			ind_playing_movie = ind_timer_keys_scene0;
			movies[ind_playing_movie].play();
		}
	}
	
	if(cur_time - last_time_movie > timer_movie){
		int key = movie_key_frames[ind_playing_movie][0];
		
		// 唇の色
		if (ind_playing_movie == 2 && last_key != 540) {
			key = movie_key_frames[ind_playing_movie][ int(ofRandom(1, n_keys[ind_playing_movie]-0.3)) ];
		}
		last_key = key;
		
		movies[ind_playing_movie].setFrame(key);
		last_time_movie = cur_time;
		
		if (ind_timer_keys_scene0 == 3 && ofRandom(1) > 0.5) {
			movies[ind_playing_movie].stop();
			ind_playing_movie = int(ofRandom(0, 2.9));
			movies[ind_playing_movie].play();
		}
	}
}

void ofApp::updateScene1(){
	if (cur_time - last_time > timer_anime ) {
		ind_anime++;
		if (ind_anime > n_imgs[ind_playing_anime]-1) {
			ind_anime = 0;
		}
		last_time = cur_time;
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	cur_time = ofGetElapsedTimeMillis();
	cur_time_sec = int(ofGetElapsedTimef());
	
	if (scene == 0) {
		updateScene0();
	} else if (scene == 1){
		updateScene1();
	}
}

void ofApp::exit(){
	delete [] movies;
	delete [] movieWidths;
	delete [] movieHeights;
	delete [] movieNeedsRotates;
	delete [] movieFrameStarts;
	delete [] movieFrameEnds;
	
	for (int i =0; i < n_movie; i++) {
		delete [] movie_key_frames[i];
	}
	delete [] movie_key_frames;
	
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
	if (scene==0) {
		if (movieNeedsRotates[ind_playing_movie]) {
			ofRotate( -90 );
		}
		movies[ind_playing_movie].draw(-movieWidths[ind_playing_movie]/2, -movieHeights[ind_playing_movie]/2, movieWidths[ind_playing_movie], movieHeights[ind_playing_movie]);
	
	} else if (scene == 1) {
		kome[ind_playing_anime][ind_anime].draw(-anime_widths[ind_playing_anime]/2, -anime_heights[ind_playing_anime]/2, anime_widths[ind_playing_anime], anime_heights[ind_playing_anime]);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
//	myPlayer.setSpeed( myPlayer.getSpeed() * -1  );
	if (key == ' ') {
		scene = 1 - scene;
	} else if (key == 'q') {
		if (movies[ind_playing_movie].isPlaying()) {
			cout << "frame:" << movies[ind_playing_movie].getCurrentFrame() << endl;
			movies[ind_playing_movie].stop();
		} else{
			movies[ind_playing_movie].play();
		}
	} else if (key == 'w') {


		movies[5].setFrame(359);
	} else if (key == 'e') {
		movies[5].setFrame(427);

	} else if (key =='r') {
		movies[5].setFrame(499);

	} else if (key =='t') {
		movies[5].setFrame(540);
	} else if (key == 'y') {
		movies[0].setFrame(83);
	} else if (key =='u') {
		movies[1].setFrame(60);
	} else if (key =='i') {
		movies[1].setFrame(410);
	}else {
		if (scene == 0) {
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
		} else if (scene == 1) {
			if (key == '`') {
				ind_playing_anime = 0;
				ind_anime = 0;
			} else if (key == '1') {
				ind_playing_anime = 1;
				ind_anime = 0;
			}else if (key == '2') {
				ind_playing_anime = 2;
				ind_anime = 0;
			}else if (key == '3') {
				ind_playing_anime = 3;
				ind_anime = 0;
			}else if (key == '4') {
				ind_playing_anime = 4;
				ind_anime = 0;
			}else if (key == '5') {
				ind_playing_anime = 5;
				ind_anime = 0;
			} else if (key == '6') {
				ind_playing_anime = 6;
				ind_anime = 0;
			} else if (key == '7') {
				ind_playing_anime = 7;
				ind_anime = 0;
			} else if (key == '8') {
				ind_playing_anime = 8;
				ind_anime = 0;
			} else if (key == '9') {
				ind_playing_anime = 9;
				ind_anime = 0;
			} else if (key == '0') {
				ind_playing_anime = 10;
				ind_anime = 0;
			} else if (key == '-') {
				ind_playing_anime = 11;
				ind_anime = 0;
			} else if (key == '=') {
				ind_playing_anime = 12;
				ind_anime = 0;
			}
		}
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
