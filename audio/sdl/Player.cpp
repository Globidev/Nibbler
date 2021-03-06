#include "Player.hpp"

#include "Sound.hpp"

#include <map>
#include <memory>

static const char EAT_PATH[] = "./audio/sdl/assets/nyan.wav";
static const char DIE_PATH[] = "./audio/sdl/assets/cry.wav";

using SoundMap = std::map<audio::Sound, std::shared_ptr<SDLSound>>;
static const SoundMap SOUNDS = {
    { audio::Sound::FoodEaten, std::make_shared<SDLSound>(EAT_PATH) },
    { audio::Sound::Dead,      std::make_shared<SDLSound>(DIE_PATH) },
};

SDLPlayer::SDLPlayer(void) {
    SDL_Init(SDL_INIT_AUDIO);
}

void            SDLPlayer::play(audio::Sound sound) {
    auto soundIt = SOUNDS.find(sound);
    if (soundIt != SOUNDS.end())
        soundIt->second->play();
}
