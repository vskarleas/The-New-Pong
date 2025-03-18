/**
 * @file page_4b_1t.hpp
 * @brief Header defining the mode selection menu page_4b_1t class
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#ifndef MODE_MENU_HPP
#define MODE_MENU_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <array>

/**
 * @class page_4b_1t
 * @brief Defines the mode selection menu with 4 buttons and 1 title
 * 
 * This class handles the mode selection screen where players can choose
 * between different game modes (AI mode, Two players mode, etc.)
 */
class page_4b_1t
{
private:
    int mode_id;        /**< Selected game mode ID */
    bool exit_game;     /**< Flag to exit the game */
    /**
     * mode = 1 -> AI mode
     * mode = 2 -> Two players mode
     * mode = 3 -> Storytime mode
     * mode = 4 -> Fun mode
     *
     * Check macros.hpp for more information
     */

    SDL_Texture *texture_menu;   /**< Texture for the menu background */
    SDL_Renderer *renderer;      /**< Responsible for placing the objects on the SDL screen */
    TTF_Font *police;            /**< Font used for text rendering */

    SDL_Rect button_ai_mode;            /**< Rectangle for AI mode button */
    SDL_Rect button_two_players_mode;   /**< Rectangle for two players mode button */
    SDL_Rect button_storytime_mode;     /**< Rectangle for storytime mode button */
    SDL_Rect button_fun_mode;           /**< Rectangle for fun mode button */
    SDL_Rect button_exit;               /**< Rectangle for exit button */

public:
    /**
     * @brief Constructor for the mode menu page
     * @param _renderer The SDL renderer to use for drawing
     * @param font The TTF font to use for text display
     */
    page_4b_1t(SDL_Renderer *_renderer, TTF_Font *font);
    
    /**
     * @brief Destructor for the mode menu page
     */
    ~page_4b_1t();

    /**
     * @brief Handles events for the menu buttons
     * @param event The SDL event to process
     * @return true if a button was clicked, false otherwise
     */
    bool action_handler(const SDL_Event &event);
    
    /**
     * @brief Renders the mode menu
     */
    void render_object();

    /**
     * @brief Checks if the exit game flag is set
     * @return true if the game should exit, false otherwise
     */
    bool get_exit_game() const { return exit_game; }

    /**
     * @brief Gets the selected game mode ID
     * @return The selected mode ID for redirecting to the correct view
     */
    int get_mode_id() const { return mode_id; }
};

#endif