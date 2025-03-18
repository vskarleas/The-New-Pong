/**
 * @file sound_effects.hpp
 * @brief Header defining the SoundEffects utility class
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#ifndef SOUND_EFFECTS_HPP
#define SOUND_EFFECTS_HPP

#include <SDL_mixer.h>

/**
 * @class SoundEffects
 * @brief Utility class for handling sound effects and music in the game
 *
 * This class provides static methods for controlling audio playback,
 * including background music transitions with fade effects.
 */
class SoundEffects
{
public:
    /**
     * @brief Changes background music with fade effect
     *
     * @param music_file The new music track to play
     * @param fade_out_duration Duration of fade out in milliseconds
     * @param fade_in_duration Duration of fade in in milliseconds
     * @param volume Volume level (0-128)
     */
    static void change_music_track(Mix_Music *music_file,
                                   int fade_out_duration = 500,
                                   int fade_in_duration = 500,
                                   int volume = MIX_MAX_VOLUME / 3);
};

#endif