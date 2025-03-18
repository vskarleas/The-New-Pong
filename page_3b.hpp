/**
 * @file page_3b.hpp
 * @brief Header defining the pause menu page_3b class
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#ifndef PAUSE_MENU_HPP
#define PAUSE_MENU_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

/**
 * @class page_3b
 * @brief Pause menu with 3 buttons
 * 
 * This class implements the pause menu that appears during gameplay,
 * allowing players to resume the game, save their progress, or exit.
 */
class page_3b
{
public:
    /**
     * @brief Constructor for pause menu
     * @param renderer The SDL renderer to use for drawing
     * @param font The TTF font to use for text display
     */
    page_3b(SDL_Renderer *renderer, TTF_Font *font);
    
    /**
     * @brief Destructor for pause menu
     */
    ~page_3b();

    /**
     * @brief Renders the pause menu
     */
    void render_object();
    
    /**
     * @brief Handles events for the menu buttons
     * @param event The SDL event to process
     * @return true if a button was clicked, false otherwise
     */
    bool action_handler(const SDL_Event &event);
    
    /**
     * @brief Checks if the resume button was pressed
     * @return true if the game should resume, false otherwise
     */
    bool ShouldResume() const { return mResume; }
    
    /**
     * @brief Checks if the save button was pressed
     * @return true if the game should be saved, false otherwise
     */
    bool ShouldSave() const { return mSave; }
    
    /**
     * @brief Checks if the exit button was pressed
     * @return true if the game should exit, false otherwise
     */
    bool get_exit_mode() const { return mExit; }

    /**
     * @brief Sets the current game mode type
     * @param type The game mode type ID
     */
    void set_mode_type(int type) { mode_type = type; } 
    
    /**
     * @brief Gets the current game mode type
     * @return The current game mode type ID
     */
    int get_mode_type() const { return mode_type; }

private:
    SDL_Renderer *renderer;  /**< Renderer for drawing elements */
    TTF_Font *police;        /**< Font used for text rendering */
    bool mResume;            /**< Flag for resume button */
    bool mSave;              /**< Flag for save button */
    bool mExit;              /**< Flag for exit button */
    int selected_button;     /**< Currently selected/highlighted button */

    SDL_Rect mResumeButton;  /**< Rectangle for resume button */
    SDL_Rect mSaveButton;    /**< Rectangle for save button */
    SDL_Rect button_exit;    /**< Rectangle for exit button */

    int mode_type;           /**< Current game mode type */
};

#endif