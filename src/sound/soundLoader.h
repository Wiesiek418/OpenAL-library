#ifndef SOUND_LOADER_H
#define SOUND_LOADER_H

#include <string>
#include <vector>
#include <AL/al.h>

void loadWAVFile(const std::string& fileName, std::vector<char>& data, ALenum& format, ALsizei& freq);
void unloadWAVFile(std::vector<char>& data);

#endif // SOUND_LOADER_H