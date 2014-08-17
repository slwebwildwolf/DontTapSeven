#ifndef __Piano__
#define __Piano__

#include <iostream>
#include <cocos2d.h>
#include <vector>

USING_NS_CC;

class Piano
{
private:	
	std::vector<std::string> musics;
	int musicNow;
	int musicNowCount;
public:
	Piano();
	~Piano();

	static Piano* getInstance();
	void init();
	void playPiano(char sound);
	void playBeep();
	void playCamera();// "sound/camera.wav"
	void playCheer();// "sound/cheer.m4a"
	void playError();// "sound/error.m4a"
	void playError_piano();// "sound/error_piano.m4a"
	void playMistake();// "sound/mistake.mp3"
	void playTick();// "sound/tick.m4a" 
	void playTouch();// "sound/touch.m4a"
	void playWin();// "sound/win.mp3"

	void playMusic();
};

#endif //