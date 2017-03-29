#include "AudioComponent2D.h"

AudioComponent2D::AudioComponent2D(std::string name) : AudioComponent(name)
{
	init();
}

AudioComponent2D::~AudioComponent2D()
{
	engine->drop(); // deletes the engine.
	active = false;
}

void AudioComponent2D::init()
{
	// start the sound engine:
	engine = irrklang::createIrrKlangDevice();
	engine->setSoundVolume(0.2f);

	if (!engine) //If the engine failed to startup:
	{
		printf("ERROR: Engine failed to start up\n");
	}

}

void AudioComponent2D::playSound(char * file)
{
	if(!active)
	engine->play2D(file); //Plays the AudioComponent2D file once.

	active = true;
}

void AudioComponent2D::playMusic(char * file)
{
	if (!active)
	engine->play2D(file, true); //Plays the AudioComponent2D file on a loop.

	active = true;
}

void AudioComponent2D::stopSound()
{
	engine->stopAllSounds();
	active = false;
}


