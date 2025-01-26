#include <AL/al.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

struct WAVFileHeader {

	char chunkID[4];
	uint32_t chunkSize;
	char format[4];

	char subchunk1ID[4];
	uint32_t subchunk1Size;
	uint16_t audioFormat;
	uint16_t numChannels;
	uint32_t sampleRate;
	uint16_t blockAlign;
	uint16_t bitsPerSample;

	char subchunk2ID[4];
	uint32_t subchunk2Size;
};


void loadWAVFile(const std::string& fileName, std::vector<char>& data, ALenum& format, ALsizei& freq)
{
	std::ifstream wavFile(fileName, std::ios::binary);

	if (!wavFile.is_open())
	{
		throw std::runtime_error("SoundLoader error: Cannot open the wav file: "+fileName);
	}

	WAVFileHeader wavHeader;
	wavFile.read(reinterpret_cast<char*> (&wavHeader), sizeof(WAVFileHeader));
	
	if (std::string(wavHeader.format,4) != "WAVE" || std::string(wavHeader.chunkID, 4) != "RIFF")
	{
		wavFile.close();
		throw std::runtime_error("SoundLoader error: Incorrect WAVE file format");
	}

	//Set format of audio
	if (wavHeader.numChannels == 1)						//mono audio
	{
		if (wavHeader.bitsPerSample == 8)
			format = AL_FORMAT_MONO8;
		else
			format = AL_FORMAT_MONO16;
	}
	else if (wavHeader.numChannels == 2)				//stereo audio
	{
		if (wavHeader.bitsPerSample == 8)				
			format = AL_FORMAT_STEREO8;
		else
			format = AL_FORMAT_STEREO16;
	}
	else
	{
		throw std::runtime_error("SoundLoader error: Unsupported number of channels");
	}

	//Set frequency of audio
	freq = wavHeader.sampleRate;

	//Get data from WAV file
	data.resize(wavHeader.subchunk2Size);					//Resize data vector to size of WAV data
	wavFile.read(data.data(), wavHeader.subchunk2Size);

	
	if (data.size() != wavHeader.subchunk2Size)
	{
		wavFile.close();
		data.clear();
		throw std::runtime_error("SoundLoader error: Failed to read WAV file data");
	}

	wavFile.close();
}

void unloadWAVFile(std::vector<char>& data)
{
	data.clear();
}