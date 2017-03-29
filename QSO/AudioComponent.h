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
	virtual void init();
	virtual void playSound(char* file) = 0; //Plays the sound passed to it. (Accepts .wav files)
	virtual void playMusic(char* file) = 0; //Plays the sound passed to it on a continual loop. (Accepts .ogg files)

protected:

	irrklang::ISoundEngine* engine; //Responsible for all irrklang sound processes.

};