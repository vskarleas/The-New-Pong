/**
 * @file page_3b_0t.hpp
 * @brief Header defining the main menu class with 3 buttons and no title of the page_3b_0t class
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#ifndef MENU_HPP
#define MENU_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <array>
#include <string>
#include <functional>
#include <SDL_mixer.h>

#include "game_save.hpp"

/**
 * @class page_3b_0t
 * @brief Main menu class with 3 buttons and no title
 *
 * This class implements the main menu screen with options to start a new game,
 * continue a saved game, or exit to the mode selection screen.
 */
class page_3b_0t
{
private:
    bool start_new_game;         /**< Flag for starting a new game */
    bool exit_mode;              /**< Flag for exiting to mode selection */
    bool continue_game;          /**< Flag for continuing a saved game */

    bool saved_file_exists;      /**< Whether a saved game file exists */

    SDL_Texture *texture_menu;   /**< Texture for the menu background */
    SDL_Renderer *renderer;      /**< Responsible for placing objects on the SDL screen */
    TTF_Font *police;            /**< Font used for text rendering */

    SDL_Rect button_start;       /**< Rectangle for start new game */
    SDL_Rect button_exit;        /**< Rectangle for exit */
    SDL_Rect button_continue;    /**< Rectangle for continueing game button */

public:
    /**
     * @brief Constructor for the main menu page
     * @param _renderer The SDL renderer to use for drawing
     * @param font The TTF font to use for text display
     */
    page_3b_0t(SDL_Renderer *_renderer, TTF_Font *font);
    
    /**
     * @brief Destructor for the main menu page
     */
    ~page_3b_0t();

    /**
     * @brief Handles events for the menu buttons
     * @param event The SDL event to process
     * @return true if a button was clicked, false otherwise
     */
    bool action_handler(const SDL_Event &event);
    
    /**
     * @brief Renders the main menu
     * @param mode Current game mode
     * @param highscore_name Name of the player with highest score
     * @param highscore The highest score value
     */
    void render_object(int mode, const std::string &highscore_name, int highscore);

    /**
     * @brief Checks if the start new game button was pressed
     * @return true if a new game should be started, false otherwise
     */
    bool get_started() const { return start_new_game; }
    
    /**
     * @brief Checks if the exit button was pressed
     * @return true if should exit to mode selection, false otherwise
     */
    bool get_exit_mode() const { return exit_mode; }
    
    /**
     * @brief Checks if a saved game file exists
     * @return true if a saved game exists, false otherwise
     */
    bool get_saved_file_exists() const { return saved_file_exists; }
    
    /**
     * @brief Checks if the continue game button was pressed
     * @return true if should continue a saved game, false otherwise
     */
    bool get_continue_game() const { return continue_game; }

    /**
     * @brief Updates the saved file exists flag
     */
    void set_saved_file_exists() { saved_file_exists = Saving::save_exists(); }
};

#endif