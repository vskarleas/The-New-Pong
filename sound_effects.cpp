/**
 * @file sound_effects.cpp
 * @brief Implementation of the SoundEffects utility class
 * @authors Vasileios Filippos Skarleas, Yanis Sadoun, Dounia Bakalem
 * @copyright All rights reserved.
 */

#include "sound_effects.hpp"

#include <SDL.h>

/**
 * @brief Changes background music with fade effect
 * 
 * This function smoothly transitions from the current music track to a new one
 * by fading out the current track, then fading in the new one. It also sets
 * the volume level of the new track.
 *
 * @param music_file The new music track to play
 * @param fade_out_duration Duration of fade out in milliseconds
 * @param fade_in_duration Duration of fade in in milliseconds
 * @param volume Volume level (0-128)
 */
void SoundEffects::change_music_track(Mix_Music *music_file,
                                      int fade_out_duration,
                                      int fade_in_duration,
                                      int volume)
{
    Mix_FadeOutMusic(fade_out_duration);
    // SDL_Delay(5);
    Mix_FadeInMusic(music_file, -1, fade_in_duration);
    Mix_VolumeMusic(volume);
}