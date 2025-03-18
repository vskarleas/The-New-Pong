/**
 * @file page_3b_1t.hpp
 * @brief Header defining the middle menu class with 3 buttons and 1 title of page_3b_1t class
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#ifndef MIDDLE_MENU_HPP
#define MIDDLE_MENU_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <array>
#include <SDL_mixer.h>

class Game;

/**
 * @class page_3b_1t
 * @brief Middle menu class with 3 buttons and 1 title
 *
 * This class is a versatile menu that can be used for multiple purposes
 * such as ball type selection or AI difficulty selection.
 */
class page_3b_1t
{
private:
    int selected_button;         /**< Currently selected button (-1 if none) */
    int mode_type;               /**< Mode type for determining what options to show */
    
    SDL_Texture *texture_middle_menu;  /**< Texture for the menu background */
    SDL_Renderer *renderer;            /**< Responsible for placing objects on the SDL screen */
    TTF_Font *police;                  /**< Font used for text rendering */

    SDL_Rect button_1;           /**< Rectangle for first option button */
    SDL_Rect button_2;           /**< Rectangle for second option button */
    SDL_Rect button_3;           /**< Rectangle for third option button */

public:
    /**
     * @brief Constructor for the middle menu page
     * @param _renderer The SDL renderer to use for drawing
     * @param font The TTF font to use for text display
     */
    page_3b_1t(SDL_Renderer *_renderer, TTF_Font *font);
    
    /**
     * @brief Destructor for the middle menu page
     */
    ~page_3b_1t();

    /**
     * @brief Gets the currently selected option
     * @return The selected button index (0-2), or -1 if none selected
     */
    int get_selected_option() const { return selected_button; }

    /**
     * @brief Handles events for the menu buttons
     * @param event The SDL event to process
     * @return true if a button was clicked, false otherwise
     */
    bool action_handler(const SDL_Event &event);
    
    /**
     * @brief Renders the middle menu
     */
    void render_object();

    /**
     * @brief Gets the current mode type
     * @return The current mode type ID
     */
    int get_mode_type() const { return mode_type; }
    
    /**
     * @brief Sets the mode type to display appropriate options
     * @param type The mode type ID to set
     */
    void set_mode_type(int type) { mode_type = type; }
};

#endif // MIDDLE_MENU_HPP
