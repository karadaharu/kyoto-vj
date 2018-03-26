#include "SoundReact.h"

void SoundReact::setup(ofBaseApp *app){
	soundStream.listDevices();
	soundStream.setDeviceID(0);
	//    soundStream.setInput(0);

	soundStream.setup(app, 0, 1, 44100, BUFFER_SIZE, 4);
	_left  = new float[BUFFER_SIZE];
	_right = new float[BUFFER_SIZE];
	
	for(int i = 0; i < NUM_WINDOWS; i++){
		for(int j = 0; j < BUFFER_SIZE / 2; j++){
			this->_freq[i][j] = 0.0f;
		}
	}
}

void SoundReact::update(){
	float avg_power = 0.0f;
	// 左チャンネルのデータに対してのみFFTを実行
	this->_fft.PowerSpectrum(0, (int)BUFFER_SIZE/2,
							 this->_left, BUFFER_SIZE, &this->_magnitude[0], &this->_phase[0], &this->_power[0], &avg_power);
	// _magnitude[0]は直流成分(時間変化のない=振動しない成分)のため、無視する
}

void SoundReact::audioIn(float * input, int bufferSize, int nChannels){
	curVol = 0.0;
	for (int i = 0; i < bufferSize; i++){
		curVol += input[i*2+1]*input[i*2+1]; // 聴覚上は出力の2乗に比例するので、2乗しています。
		this->_left[i]  = input[i * 2];
		//        this->_right[i] = input[i * 2 + 1]; //右をどこにも使ってない
	}
	curVol /= bufferSize; // 平均を取ります。
}