#pragma once
#include "AudioComponent.h"

class AudioComponentLinear3D : public AudioComponent
{
public:

	AudioComponentLinear3D(std::string name);
	~AudioComponentLinear3D();
	void init();
	void playSound(char* file);		//Plays the sound passed to it. (Accepts .wav files)
	void playMusic(char* file);		//Plays the sound passed to it on a continual loop. (Accepts .ogg files)
	void stopSound();

	void setSoundPosition(glm::vec3 pos);
	void setListenerPosition(glm::vec3 pos);

	glm::vec3 getSoundPosition() { return soundPosition; }		//Returns the soundPosition as a glm vec3.
	glm::vec3 getListenerPosition() { return listenerPosition; }		//Returns the listeners Position as a glm vec3.

private:
	bool active;
	float linearVolume; //the volume of sound based on distance
	float soundDistance; //how far away the sound can be heard from
	void determineVolume(); //sets the linearvolume based on distance between listener and sound positions.

	glm::vec3 soundPosition;	//the location at which the sound is played from.
	glm::vec3 listenerPosition;	//the location at which the sound is being heard.

	irrklang::ISound* musicStream;		//stores any 3d music that is being played.
};