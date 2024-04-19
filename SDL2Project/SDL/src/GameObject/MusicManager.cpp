#include "MusicManager.h"

MusicManager* MusicManager::s_instance = nullptr;

MusicManager::MusicManager() : m_music(nullptr), m_isMusicOn(true) {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        // Handle SDL initialization error
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        // Handle SDL_mixer initialization error
    }
}

MusicManager* MusicManager::GetInstance() {
    if (!s_instance) {
        s_instance = new MusicManager();
    }
    return s_instance;
}

void MusicManager::DestroyInstance() {
    if (s_instance) {
        delete s_instance;
        s_instance = nullptr;
    }
}

void MusicManager::PlayMusic(const char* filePath) {
    if (m_music != nullptr) {
        StopMusic();
    }
    m_music = Mix_LoadMUS(filePath);
    if (m_music != nullptr) {
        Mix_PlayMusic(m_music, -1);
    }
}

void MusicManager::StopMusic() {
    if (m_music != nullptr) {
        Mix_FreeMusic(m_music);
        m_music = nullptr;
    }
}

void MusicManager::toggleMusic(bool on) {
    m_isMusicOn = on;
    if (m_isMusicOn) {
        Mix_ResumeMusic();
    }
    else {
        Mix_PauseMusic();
    }
}
