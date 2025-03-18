/**
 * @file gui.hpp
 * @brief Header defining the GUI utility class for game interface
 * @authors Vasileios Filippos Skarleas, Dounia Bakalem, Yanis Sadoun
 * @copyright All rights reserved.
 */

#ifndef GUI_HPP
#define GUI_HPP

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

/**
 * @class GUI
 * @brief Utility class providing user interface functionality
 *
 * This class contains static methods for handling UI elements and
 * user interactions throughout the game.
 */
class GUI
{
public:
    /**
     * @brief Gets the player's name input from the SDL window
     *
     * This function handles SDL events to capture the player's name input
     * from the keyboard. It displays the input text on screen and updates
     * it in real-time as the player types.
     *
     * @param renderer The SDL renderer used for drawing
     * @param font The TTF font used to render text
     * @param player_number The player number (for display purposes)
     * @return std::string The name entered by the player
     */
    static std::string player_name_input(SDL_Renderer *renderer, TTF_Font *font, int player_number);
};

#endif