#pragma once
#include <SDL_mixer.h>
#include <string>

class Music 
{
private:
    Mix_Music* music;  // For background music

public:
    Music(const std::string& filePath);
    ~Music();

    void Play(bool isLoop = true);
    void Stop();
    void SetVolume(int volume);  // Volume range: 0 - 128
};
