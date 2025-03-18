/**
 * @file game_over.hpp
 * @brief Header defining the game_over screen class
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#ifndef GAME_OVER_HPP
#define GAME_OVER_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

/**
 * @class game_over
 * @brief Handles the game over screen when a game is completed
 *
 * This class is responsible for displaying the game over screen, showing
 * the winner's name, and providing a navigation button to return to the
 * main menu.
 */
class GameOver
{
private:
    SDL_Texture *texture_menu;   /**< Texture for the menu background */
    SDL_Renderer *renderer;      /**< Responsible for placing the objects on the SDL screen */
    TTF_Font *police;            /**< Font used for text rendering */

    SDL_Rect button_back;        /**< Rectangle defining the back button's position and size */

    bool go_back;                /**< Flag to indicate going back to the modes menu */

    std::string winner_name;     /**< Name of the winning player to display */

public:
    GameOver(SDL_Renderer *_renderer, TTF_Font *font);
    ~GameOver();

    // Handles the events from the SDL window and returns true if the back button is pressed
    bool action_handler(const SDL_Event &event);

    // Returns true if the back button is pressed - used a sflag to change between screens
bool get_go_back() const { return go_back; }

    // Returns the name of the winner
    void set_winner(const std::string &name);

    // Renders the game over menu with the winner's name and a back button
    void render_object();
};

#endif // NOTICE_MENU_HPP
