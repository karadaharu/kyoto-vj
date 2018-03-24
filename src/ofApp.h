#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
	void updateScene0();
	void updateScene1();

		void draw();
		void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofVideoPlayer* movies;
	int width;
	int height;
	int movieWidth;
	int movieHeight;
	int* movieWidths;
	int* movieHeights;
	bool* movieNeedsRotates;
	int* movieFrameStarts;
	int* movieFrameEnds;
	int ind_playing_movie;
	int n_movie;
	
	int timer_movie;
//	int timer_keys_scene0[3] = {300, 480, 1100};
	int timer_keys_scene0[3] = {5, 10, 110};
	int last_key;
	int** movie_key_frames;
	int n_keys[3] = {1, 1, 4};
	int ind_timer_keys_scene0;
	int last_time_movie;
	
	
	int ind_anime;
	int timer_anime;
	int last_time;
	int* anime_widths;
	int* anime_heights;
	int n_imgs[13]={7, 5, 8, 5, 9, 6, 6, 6, 6, 22, 8, 9, 20};
	int ind_playing_anime;
	
	int cur_time;
	int cur_time_sec;
	
	int scene;
	ofImage** kome;
};
