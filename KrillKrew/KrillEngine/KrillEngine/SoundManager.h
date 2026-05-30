#pragma once
#include "Log.h"
#include "Music.h"
#include "SFX.h"
#include <map>
#include <string>

namespace KrillSoundManager
{
class SoundManager
{
private:
    static SoundManager* instance;
    std::map<std::string, Music*> musicSounds;
    std::map<std::string, SFX*> SFXSounds;

public:
    SoundManager();
    ~SoundManager();

    static SoundManager* GetInstance();

    void LoadSFX(const std::string& name, const std::string& filePath);
    void LoadMusic(const std::string& name, const std::string& filePath);

    void PlaySFX(const std::string& name, bool isloop = 0);
    void PlayMusic(const std::string& name, bool isloop = 1);

    void StopSFX(const std::string& name);
    void StopMusic(const std::string& name);

    void SetVolumeSFX(const std::string& name, int volume);
    void SetVolumeMusic(const std::string& name, int volume);

    void SetVolumeAllSFX(int volume);
    void SetVolumeAllMusic(int volume);

    void SaveVolumeConfig(
        const std::string& filename, float master, bool ismute_master, float music, bool ismute_music, float sfx, bool ismute_sfx);
    void LoadVolumeConfig(
        const std::string& filename, float& master, bool& ismute_master, float& music, bool& ismute_music, float& sfx, bool& ismute_sfx);

    void Cleanup();
};
} // namespace KrillSoundManager
