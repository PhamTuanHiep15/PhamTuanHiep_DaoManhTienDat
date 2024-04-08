#pragma once
#include "SDL.h"
#include "SDL_mixer.h"
#include <string>

class MusicManager {
private:
    bool isMusicOn;
    Mix_Music* m_backgroundMusic; // Biến để lưu trữ nhạc nền

public:
    MusicManager() : isMusicOn(false), m_backgroundMusic(nullptr) {}

    // Phương thức để bật/tắt nhạc nền
    void toggleMusic(bool state);

    // Phương thức để thiết lập nhạc nền
    void setBackgroundMusic(const std::string& musicPath);

    // Phương thức để phát nhạc nền
    void playBackgroundMusic();

    // Phương thức để dừng nhạc nền
    void stopBackgroundMusic();

};