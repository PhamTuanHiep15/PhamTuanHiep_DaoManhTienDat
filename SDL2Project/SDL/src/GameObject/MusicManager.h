#pragma once

#include <SDL.h>
#include <SDL_mixer.h>

class MusicManager {
private:
    static MusicManager* s_instance;
    Mix_Music* m_music;
    bool m_isMusicOn;

    MusicManager();

public:
    static MusicManager* GetInstance();
    static void DestroyInstance();

    void PlayMusic(const char* filePath);
    void StopMusic();
    void toggleMusic(bool on);

    bool isMusicOn() const { return m_isMusicOn; }
};
