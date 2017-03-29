#pragma once
#include "AudioComponent.h"

class AudioComponent3D : public AudioComponent
{
public:

	AudioComponent3D(std::string name, glm::vec3 isoundPosition);
	~AudioComponent3D();
	void init();
	void playSound(char* file);		//Plays the sound passed to it. (Accepts .wav files)
	void playMusic(char* file);		//Plays the sound passed to it on a continual loop. (Accepts .ogg files)
	void stopSound();

	void setSoundPosition(glm::vec3 pos);
	void setSoundPosition(irrklang::vec3df pos);
	void setListenerPosition(glm::vec3 pos);
	void setListenerPosition(irrklang::vec3df pos);

	glm::vec3 getSoundPositionVec3()				{ return convertToVec3(soundPosition); }		//Returns the soundPosition as a glm vec3.
	irrklang::vec3df getSoundPositionVec3df()		{ return soundPosition; }						//Returns the soundPosition as a vec3df.
	glm::vec3 getListenerPositionVec3()				{ return convertToVec3(listenerPosition); }		//Returns the listeners Position as a glm vec3.
	irrklang::vec3df getListenerPositionVec3df()	{ return listenerPosition; }					//Returns the listeners Position as a vec3df.

private:
	bool active;
	float minimumDistance;				//distance from the soundPosition at which the audio is considered to be at full volume.

	glm::vec3 convertToVec3(irrklang::vec3df convertVec);	//converts vec3df to glm vec3.
	irrklang::vec3df convertToVec3df(glm::vec3 convertVec); //converts a glm vec3 to the irrklang compatible vec3df.

	irrklang::vec3df soundPosition;		//the location at which the sound is played from.
	irrklang::vec3df listenerPosition;	//the location at which the sound is being heard.


	irrklang::ISound* musicStream;		//stores any 3d music that is being played.
};