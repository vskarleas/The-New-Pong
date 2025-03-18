/**
 * @file page_2b_1t.hpp
 * @brief Header defining the notice screen page_2b_1t class
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#ifndef NOTICE_MENU_HPP
#define NOTICE_MENU_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

/**
 * @class page_2b_1t
 * @brief Notice screen with 2 buttons and 1 title
 * 
 * This class handles the notice screen that displays game instructions
 * and provides navigation buttons.
 */
class page_2b_1t
{
private:
    SDL_Texture *texture_menu;   /**< Texture for the menu background */
    SDL_Renderer *renderer;      /**< Responsible for placing the objects on the SDL screen */
    TTF_Font *police;            /**< Font used for text rendering */

    SDL_Rect button_lets_go;     /**< Rectangle for "Let's go" button */
    SDL_Rect button_back;        /**< Rectangle for "Back" button */

    bool next_view;              /**< Flag to proceed to the next view */
    bool go_back;                /**< Flag to go back to the mode selection menu */

    int notice_id;               /**< ID for the current notice text to display */

public:
    /**
     * @brief Constructor for the notice page
     * @param _renderer The SDL renderer to use for drawing
     * @param font The TTF font to use for text display
     */
    page_2b_1t(SDL_Renderer *_renderer, TTF_Font *font);
    
    /**
     * @brief Destructor for the notice page
     */
    ~page_2b_1t();

    /**
     * @brief Handles events for the menu buttons
     * @param event The SDL event to process
     * @return true if a button was clicked, false otherwise
     */
    bool action_handler(const SDL_Event &event);

    /**
     * @brief Checks if the "Next" button was pressed
     * @return true if the game should proceed to the next view, false otherwise
     */
    bool get_next_view() const { return next_view; }
    
    /**
     * @brief Checks if the "Back" button was pressed
     * @return true if the game should go back to the modes menu, false otherwise
     */
    bool get_go_back() const { return go_back; }

    /**
     * @brief Gets the current notice ID
     * @return The current notice ID to display appropriate text
     */
    int get_notice_id() const { return notice_id; }
    
    /**
     * @brief Sets the notice ID to display
     * @param _id The new notice ID to display
     */
    void set_notice_id(int _id) { notice_id = _id; }

    /**
     * @brief Renders the notice screen
     */
    void render_object();
};

#endif // NOTICE_MENU_HPP
