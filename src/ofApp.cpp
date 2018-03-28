#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	sr = new SoundReact();
	sr->setup(this);
	buffer_size = 64/2;
	ind_buffer = 17;
	moving_buffer = 0;
	power_threshold = 0.5;
	draw_scale = 1000;
	
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
//	movie_key_frames[2][0] = 359;
	movie_key_frames[2][0] = 426;
	movie_key_frames[2][1] = 492;
//	movie_key_frames[2][3] = 540;
	
	// bucket
	movies[1].load("movie/001_17cut_tate.mov");
//	movieNeedsRotates[1] = true;
	// coffee
	movies[0].load("movie/003.mp4");
//	movieNeedsRotates[0] =false;
	// face
	movies[2].load("movie/007_tate.mov");
//	movieNeedsRotates[2] = true;

	
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

	n_anime = 13;
	kome = new ofImage*[n_anime];
	anime_widths = new int[n_anime];
	anime_heights = new int[n_anime];
	
	for (int i = 0; i < n_anime; i++) {
		string ind_str = ofToString(i+1);
		if (i+1 < 10) {
			ind_str = "0" + ind_str;
		}
		kome[i] = new ofImage[ n_imgs[i] ];
		for(int j = 0; j < n_imgs[i]; j++) {
			kome[i][j].load("kome/"+ind_str+"/frame" + to_string(j+1) + ".jpg");
		}
	}
	
	setSize();
	
	ind_playing_movie = 0;
	movies[ind_playing_movie].play();
	
	ind_anime = 0;
	bpm = 130;
	timer_anime = 0.25*1000*60/130;
	timer_unit = 1000*60/bpm;
	timer_double = 2*1000*60/bpm;
	last_time_long = 0;
	

	last_time = 0;
	ind_playing_anime = 2;
	
	scene = 1;
	

	last_time_movie = 0;
	ind_timer_keys_scene0 = 0;
	
	cout << "movie:" << movies[0].isPlaying() << endl;
	last_key = 0;
	
	last_time_scene_switch=0;
	
	anime_order = 0;
	
	plane_back.set(width, height);
	plane_back.setPosition(0, 0, 0);
	plane_back.setResolution(10, 10);
	
	plane.set(200, 200);
	plane.setPosition(0, 0, 0);
	plane.setResolution(20, 20);
	n_plane_ind = plane.getMesh().getNumIndices();
	point_speed = new float[n_plane_ind];
	point_accel = new float[n_plane_ind];
	for (int i = 0; i < n_plane_ind; i++) {
		point_speed[i] = ofRandom(-1,1);
		point_accel[i] = ofRandom(-1,1);
	}
}

void ofApp::switchMovie(int nex_ind){
	movies[ind_playing_movie].stop();
	ind_playing_movie = nex_ind;
	movies[ind_playing_movie].play();
	if (ind_playing_movie==2) {
		movies[2].setSpeed(1.6);
	}


//	float ratio;
//	switch(ind_playing_movie) {
//		case 0:
////			ratio = movies[ind_playing_movie].getWidth() / width;
////			ratio = width / movies[ind_playing_movie].getWidth(); // まちがってる
////			ratio = movies[ind_playing_movie].getHeight()/ height; // ちがう
//			ratio = height / movies[ind_playing_movie].getHeight();
//
//			break;
//		case 1:
////			ratio = movies[ind_playing_movie].getHeight() / width;
////			ratio = width / movies[ind_playing_movie].getHeight();
//			ratio = height / movies[ind_playing_movie].getWidth();
//
//			break;
//
//		case 2:
//			//			ratio = movies[ind_playing_movie].getHeight() / width;
////			ratio = width / movies[ind_playing_movie].getHeight() ;
//			ratio = height / movies[ind_playing_movie].getWidth();
//			break;
//	}
//	plane.resizeToTexture( movies[ind_playing_movie].getTexture(), ratio );
	
//	for (int i = 0 ; i < n_plane_ind; i++) {
//		point_speed[i] = 0;
//	}
}

void ofApp::updateScene0(){
	movies[ind_playing_movie].update();
	// 唇の色が変わらないように動画をとめる
	if (ind_playing_movie == 2) {
		int cur_frame = movies[ind_playing_movie].getCurrentFrame();
		if ( (cur_frame > 479 && cur_frame < 490) || cur_frame > 521) {
			movies[ind_playing_movie].setPaused(true);
		}
	}
//	if ( movies[ind_playing_movie].getCurrentFrame()
	
//	if (ind_timer_keys_scene0 <= 2 && cur_time_sec > timer_keys_scene0[ind_timer_keys_scene0] ) {
//		ind_timer_keys_scene0++;
//		if (ind_timer_keys_scene0 <= 2) {
//			switchMovie(ind_timer_keys_scene0);
//		}
//	}
//
//	if(cur_time - last_time_movie > timer_double){
	if( power_threshold < sr->_power[ind_buffer] && cur_time - last_time_movie > timer_double){
		int key = movie_key_frames[ind_playing_movie][0];
		// 唇の色
		if (ind_playing_movie == 2) {
			int ind_key = ofRandom(0,1) > 0.3 ? 1 : 0;
			key = movie_key_frames[ind_playing_movie][ ind_key ];
			movies[ind_playing_movie].setPaused(false);
		}
		last_key = key;
		movies[ind_playing_movie].setFrame(key);
		last_time_movie = cur_time;

//		if (ind_timer_keys_scene0 == 3 && ofRandom(1) > 0.5) {
//			switchMovie(int(ofRandom(0, 2.9)));
//		}
	}
}

void ofApp::updateScene1(){
	if (ind_timer_keys_scene1 <= 1 && cur_time_sec > timer_keys_scene1[ind_timer_keys_scene1] ) {
		ind_timer_keys_scene1++;
		anime_order = ind_timer_keys_scene1;
	}
	
	
	if (cur_time - last_time > timer_anime ) {
		ind_anime++;
		if (ind_anime > n_imgs[ind_playing_anime]-1) {
			ind_anime = 0;
		}
		last_time = cur_time;
	}
	

	if (power_threshold < sr->_power[ind_buffer] && cur_time - last_time_long > timer_unit) {
		switch(anime_order) {
		case 0:
				ind_playing_anime++;
				break;
		case 1:
				ind_playing_anime--;
				break;
		case 2:
				ind_playing_anime = ind_playing_anime+int(ofRandom(-5, 5));
				break;
		}
		if (ind_playing_anime > n_anime - 1) {
			ind_playing_anime = 0;
		} else if (ind_playing_anime < 0) {
			ind_playing_anime = n_anime - 1;
		}
		ind_anime = 0;
		last_time_long = cur_time;
	}
	
}

//--------------------------------------------------------------
void ofApp::update(){
	sr->update();
	cur_time = ofGetElapsedTimeMillis();
	cur_time_sec = int(ofGetElapsedTimef()) - last_time_scene_switch;
	
	if (cur_time - last_time_moving > timer_unit) {
		last_time_moving = cur_time;
		moving_buffer++;
		if (moving_buffer > buffer_size-1) {
			moving_buffer = 0;
		}
		cout << "power : " << sr->_power[ind_buffer] << " threshold : " << power_threshold << endl;
	}
	
	if (scene == 0) {
		updateScene0();
	} else if (scene == 1){
		updateScene1();
	}
	
	if (scene == 0) {
		cur_w = movieWidths[ind_playing_movie];
	}else {
		cur_w = anime_widths[ind_playing_anime];
	}
//	line.clear();
//	for (int i = 0; i < buffer_size; i++) {
//		ofPoint pt;
//		pt.set(i*(cur_w / (buffer_size-1) ),-sr->_power[i]*draw_scale);
//		line.addVertex(pt);
//	}

	if (sr->_power[1] == INFINITY || sr->_power[1] != sr->_power[1] || sr->_power[1]  > pow(10, 30) ) {
		delete sr;
		sr = new SoundReact();
		sr->setup(this);
	}
}

void ofApp::audioIn(float * input, int bufferSize, int nChannels){
	sr->audioIn(input, bufferSize, nChannels);
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
	
	for (int i = 0; i < n_anime; i++) {
		delete [] kome[i];
	}
	delete [] kome;
	delete [] anime_heights;
	delete [] anime_widths;
	delete [] point_speed;
	delete [] point_accel;
	
	delete sr;
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (scene == 0) {
		ofBackground(0, 0, 0);
	} else {
		ofBackground(255, 255, 255);
	}

	ofSetColor(255, 255, 255);
	ofTranslate(width/2, height/2);
	if (scene==0) {
//		ofTexture t = movies[ind_playing_movie].getTexture();
//		deformPlane = plane.getMesh();
//		float speed_sine = sin(ofGetElapsedTimef()*3.6);
//		ofVec3f vert;
//		for(size_t i = 0; i < deformPlane.getNumIndices(); i++ ) {
//			int ii = deformPlane.getIndex( i );
//			vert = deformPlane.getVertex( ii );
//			point_speed[i] += point_accel[i];
//			if (ind_playing_movie == 0) {
//			vert.y += point_speed[i];
//			}else{
//			vert.x += point_speed[i];
//			}
////			ofDrawBitmapString(ofToString(i), vert);
//			deformPlane.setVertex( ii, vert );
//		}
//		t.bind();
//		plane_back.drawWireframe();
//		t.unbind();
//		ofPushMatrix();
//		if (movieNeedsRotates[ind_playing_movie]) {
//			ofRotate( -90 );
//		}
		movies[ind_playing_movie].draw(-movieWidths[ind_playing_movie]/2, -movieHeights[ind_playing_movie]/2, movieWidths[ind_playing_movie], movieHeights[ind_playing_movie]);
//		ofPopMatrix();
//		t.bind();
//		deformPlane.draw();
//		t.unbind();
		
	} else if (scene == 1) {
		kome[ind_playing_anime][ind_anime].draw(-anime_widths[ind_playing_anime]/2, -anime_heights[ind_playing_anime]/2, anime_widths[ind_playing_anime], anime_heights[ind_playing_anime]);
	}


//	ofDrawRectangle(100, 100, sr->_magnitude[0] * 1000.0, sr->_magnitude[0] * 1000.0);
//	if (scene == 0) {
//		ofSetColor(255,255,255);
//	} else {
//		ofSetColor(0,0,0);
//	}
//	ofTranslate(-cur_w / 2, height/2);
//	line.draw();
//	ofNoFill();
//	ofDrawRectangle(ind_buffer * cur_w / (buffer_size-1), 0, cur_w / (buffer_size-1), -power_threshold*draw_scale);
//	ofDrawRectangle(moving_buffer * cur_w / (buffer_size-1), 0, cur_w / (buffer_size-1), -0.2*draw_scale);


//	ofDrawCircle(0, 0, 100);

}

void ofApp::printParams(){
	cout << "threshold : " << power_threshold  << endl;
	cout << "ind : " << ind_buffer << endl;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'f') {
		ofToggleFullscreen();
		setSize();
	} else if (key == ' ') {
		scene = 1 - scene;
		last_time_scene_switch =  int(ofGetElapsedTimef());
		ind_timer_keys_scene1 = 0;
		ind_timer_keys_scene0 = 0;
		anime_order = 0;
		switchMovie(0);
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
		movies[2].setFrame(429);
		movies[2].setPaused(false);
	} else if (key =='r') {
		movies[2].setFrame(491);
		movies[2].setPaused(false);
	} else if (key =='t') {
		movies[5].setFrame(540);
	} else if (key == 'y') {
		movies[0].setFrame(83);
	} else if (key =='u') {
		movies[1].setFrame(60);
	} else if (key =='i') {
		movies[1].setFrame(410);
	} else if (key == 'h' && ind_buffer > 0) {
		ind_buffer--;
		printParams();
	} else if (key == 'j' && power_threshold > 0) {
		power_threshold = power_threshold * 0.9;
		printParams();
	} else if (key == 'k') {
		power_threshold = power_threshold * 10 / 9.0;
		printParams();
	} else if (key == 'l' && ind_buffer < buffer_size - 2) {
		ind_buffer++;
		printParams();
	} else if (key == 'n') {
		draw_scale = draw_scale * 0.8;
	} else if (key == 'm') {
		draw_scale = draw_scale * 10 / 8.0;
	} else if (key == ',' && bpm > 0) {
		bpm--;
		cout << "bpm:" << bpm << endl;
		timer_unit = 1000*60/bpm;
		timer_double = 2*1000*60/bpm;
	} else if (key == '.') {
		bpm++;
		cout << "bpm:" << bpm << endl;
		timer_unit = 1000*60/bpm;
		timer_double = 2*1000*60/bpm;
	} else {
		if (scene == 0) {
			if (key == '`') {
				switchMovie(0);
			} else if (key == '1') {
				switchMovie(1);
			}else if (key == '2') {
				switchMovie(2);
			}
//			else if (key == '3') {
//				movies[ind_playing_movie].stop();
//				ind_playing_movie = 3;
//				movies[ind_playing_movie].play();
//			}else if (key == '4') {
//				movies[ind_playing_movie].stop();
//				ind_playing_movie = 4;
//				movies[ind_playing_movie].play();
//			}else if (key == '5') {
//				movies[ind_playing_movie].stop();
//				ind_playing_movie = 5;
//				movies[ind_playing_movie].play();
//			}
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
void ofApp::setSize() {
	width = ofGetWindowWidth();
	height = ofGetWindowHeight();
	
	movieHeights[0] = height;
	movieWidths[0] = movies[0].getWidth() * height / movies[0].getHeight();

//	movieWidths[1] = height;
//	movieHeights[1] = movies[1].getHeight() * height / movies[1].getWidth();
	movieHeights[1] = height;
	movieWidths[1] = movies[1].getWidth() * height / movies[1].getHeight();

//	movieWidths[2] = height;
//	movieHeights[2] = movies[2].getHeight() * height / movies[2].getWidth();
	movieHeights[2] = height;
	movieWidths[2] = movies[2].getWidth() * height / movies[2].getHeight();

	
	for (int i = 0; i < n_anime; i++) {
		anime_heights[i] = height * 0.5;
		anime_widths[i] = kome[i][0].getWidth() * height * 0.5 / kome[i][0].getHeight();
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
