#pragma once

#include "ofMain.h"
#include "fft.h"

#define BUFFER_SIZE 16
#define NUM_WINDOWS 80

class SoundReact
{
	
public:
	void setup(ofBaseApp *app);
	void update();
	void audioIn(float * input, int bufferSize, int nChannels);
	
	float *_left;
	float *_right;
	fft    _fft;
	float  _magnitude[BUFFER_SIZE];
	float  _phase[BUFFER_SIZE];
	float  _power[BUFFER_SIZE];
	float  _freq[NUM_WINDOWS][BUFFER_SIZE/2];
	ofSoundStream soundStream;
	float curVol;
};
