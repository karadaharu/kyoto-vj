#pragma once

#include "ofMain.h"
#include "SoundReact.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
	void updateScene0();
	void updateScene1();
	void setSize();
	void switchMovie(int nex_ind);
	 void audioIn(float * input, int bufferSize, int nChannels);	
	void printParams();
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
	

	int timer_keys_scene0[3] = {300, 600, 900};
//	int timer_keys_scene0[3] = {5, 6, 10};
	int last_key;
	int** movie_key_frames;
	int n_keys[3] = {1, 1, 2};
	int ind_timer_keys_scene0;
	int last_time_movie;
	
	int last_time_scene_switch;
	float* point_speed;
	float* point_accel;
	
	int n_anime;
	int ind_anime;
	int timer_anime;
	int timer_unit;
	int timer_double;
	int bpm;
	
	int last_time_long;
	int last_time;
	int* anime_widths;
	int* anime_heights;
	int n_imgs[13]={7, 5, 8, 5, 9, 6, 6, 6, 6, 22, 8, 9, 20};
	int ind_playing_anime;
	int anime_order;
	
	int timer_keys_scene1[2] = {600, 1200};
//	int timer_keys_scene1[2] = {10, 20};
	int ind_timer_keys_scene1;
	
	int cur_time;
	int cur_time_sec;
	int cur_w;
	float power_threshold;
	int ind_buffer;
	int moving_buffer;
	int last_time_moving;
	int buffer_size;
	float draw_scale;
	
	int scene;
	ofImage** kome;
	
	ofPlanePrimitive plane;
	int n_plane_ind;
	ofPlanePrimitive plane_back;
    ofVboMesh deformPlane;
	SoundReact* sr;
	ofPolyline line;
};
