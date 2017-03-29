#pragma once
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

#include <stdio.h>
#include <irrKlang.h>
#include <iostream>

#include "Component.h"

class AudioComponent : public Component
{
public:

	AudioComponent(std::string name);
	virtual ~AudioComponent();
	void init();
	void playSound(char* file); //Plays the sound passed to it. (Accepts .wav files)
	void playMusic(char* file); //Plays the sound passed to it on a continual loop. (Accepts .ogg files)

protected:

	irrklang::ISoundEngine* engine; //Responsible for all irrklang sound processes.

};