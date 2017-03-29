#pragma once
#include "AudioComponent.h"

class AudioComponent2D : public AudioComponent
{
public:

	AudioComponent2D(std::string name);
	~AudioComponent2D();
	void init();
	void playSound(char* file); //Plays the sound passed to it. (Accepts .wav files)
	void playMusic(char* file); //Plays the sound passed to it on a continual loop. (Accepts .ogg files)
	void stopSound();
private:
	bool active;
};