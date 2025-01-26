#include "soundObject.h"



// constructor
SoundObject::SoundObject()
{
	try {
		init();
		initBuffors();
		initExtensions();

	}
	catch (const std::runtime_error& e)
	{
		printf(e.what());
	}
	
}


// initialization
void SoundObject::init() {
	p_ALCDevice = alcOpenDevice(nullptr); //get default device
	if (!p_ALCDevice) {
		throw std::runtime_error("OpenAL -> init: Failed to open device");  //throw exception
	}

	p_ALCContext = alcCreateContext(p_ALCDevice, nullptr);
	if (!p_ALCContext || !alcMakeContextCurrent(p_ALCContext)) {
		throw std::runtime_error("OpenAL -> init: Failed to load context on the device");  //throw exception
	}

	printf("OpenAL initialized successfully.\n");
}

void SoundObject::initBuffors()
{
	alGetError();

	alGenBuffers(numberOfBuffors, p_ALBuffers);


	ALenum error;
	if ((error = alGetError()) != AL_NO_ERROR)
	{
		alDeleteBuffers(numberOfBuffors, p_ALBuffers);
		throw std::runtime_error("OpenAL -> initBuffors: "+error);
	}
}

void SoundObject::initExtensions()
{
	g_bEAX = alIsExtensionPresent("EAX 2.0");
}

// deconstructor
SoundObject::~SoundObject() {
	if (p_ALCContext) {
		alcMakeContextCurrent(nullptr);
		alcDestroyContext(p_ALCContext);
	}
	if (p_ALCDevice) {
		alcCloseDevice(p_ALCDevice);
	}
	printf("OpenAL resources cleaned up.\r\n");
}


void SoundObject::initializationTest()
{
	std::vector<char> data;
	ALenum format;
	ALsizei freq;
	loadWAVFile("..\\..\\..\\test\\CantinaBand60.wav", data, format, freq);

	unloadWAVFile(data);
}





