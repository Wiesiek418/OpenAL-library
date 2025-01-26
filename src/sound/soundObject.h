#pragma once

#ifndef SOUNDOBJECT_H
#define SOUNDOBJECT_H

#include <AL/al.h>
#include <AL/alc.h>
#include <stdio.h>
#include <stdexcept>
#include "soundLoader.h"

class SoundObject {

private:
	ALCdevice* p_ALCDevice;		//listener device
	ALCcontext* p_ALCContext;
	ALboolean g_bEAX;

	ALuint* p_ALBuffers;
	int numberOfBuffors;

	void init();
	void initBuffors();
	void initExtensions();

public:
	SoundObject();
	~SoundObject();

	void initializationTest();		//simple sample of music
};

#endif // !SOUNDOBJECT_H