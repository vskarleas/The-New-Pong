/**
 * @file page_3b_1t.cpp
 * @brief Implementation of the middle menu page_3b_1t class
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#include "page_3b_1t.hpp"
#include "macros.hpp"
#include "renderers.hpp"
#include "game.hpp"

#include <iostream>
#include <string>

/**
 * @brief Constructor for the middle menu page
 * 
 * Initializes the menu with three buttons and default settings
 * 
 * @param _renderer The SDL renderer to use for drawing
 * @param font The TTF font to use for text display
 */
page_3b_1t::page_3b_1t(SDL_Renderer *_renderer, TTF_Font *font) : selected_button(-1),
                                                                  mode_type(-1),
                                                                  texture_middle_menu(nullptr),
                                                                  renderer(_renderer),
                                                                  police(font)
{
    button_1 = SDL_Rect{WINDOW_HEIGHT / 2, WINDOW_WIDTH - 500, 200, 40}; // The three following buttons will be closer to each other
    button_2 = SDL_Rect{WINDOW_HEIGHT / 2, WINDOW_WIDTH - 450, 200, 40};
    button_3 = SDL_Rect{WINDOW_HEIGHT / 2, WINDOW_WIDTH - 400, 200, 40};
}

/**
 * @brief Destructor for the middle menu page
 * 
 * Cleans up allocated resources
 */
page_3b_1t::~page_3b_1t()
{
    // Deallocate menu texture
    if (texture_middle_menu)
    {
        SDL_DestroyTexture(texture_middle_menu);
        texture_middle_menu = nullptr;
    }
}

/**
 * @brief Handles events for the menu buttons
 * 
 * Processes SDL events to detect button hovers and clicks
 * 
 * @param event The SDL event to process
 * @return true if a button was clicked, false otherwise
 */
bool page_3b_1t::action_handler(const SDL_Event &event)
{
    // Reinitialisations
    selected_button = -1;
    // mode_type = -1;

    if (event.type == SDL_MOUSEMOTION)
    {
        SDL_Point point = {event.motion.x, event.motion.y};

        // Ball selection menu hover handling
        if (SDL_PointInRect(&point, &button_1))
            selected_button = 0;
        else if (SDL_PointInRect(&point, &button_2))
            selected_button = 1;
        else if (SDL_PointInRect(&point, &button_3))
            selected_button = 2;
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        SDL_Point point = {event.button.x, event.button.y};

        // Ball selection menu clicks
        if (SDL_PointInRect(&point, &button_1))
        {
            selected_button = 0;
            // Saving::delete_save();
            Mix_PlayChannel(-1, Game::racket_hit_sound, 0);
            return true;
        }
        else if (SDL_PointInRect(&point, &button_2))
        {
            selected_button = 1;
            Mix_PlayChannel(-1, Game::racket_hit_sound, 0);
            // Saving::delete_save();
            return true;
        }
        else if (SDL_PointInRect(&point, &button_3))
        {
            selected_button = 2;
            Mix_PlayChannel(-1, Game::racket_hit_sound, 0);
            // Saving::delete_save();
            return true;
        }
    }
    return false;
}

/**
 * @brief Renders the middle menu
 * 
 * Displays different options based on the current mode_type value
 */
void page_3b_1t::render_object()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    TTF_SetFontStyle(police, TTF_STYLE_BOLD);
    if (mode_type == BALL_TYPE_SELECTION)
    {
        Utilities::render_button(renderer, police, "Select Ball Type", SDL_Rect{WINDOW_HEIGHT / 2, 50, 200, 50}, black);

        TTF_SetFontStyle(police, TTF_STYLE_NORMAL);
        Utilities::render_button(renderer, police, "Classic Ball", button_1, black);
        Utilities::render_button(renderer, police, "Square Ball", button_2, black);
        Utilities::render_button(renderer, police, "Triangle Ball", button_3, black);
    }
    else if (mode_type == AI_MODE_SELECTION)
    {
        Utilities::render_button(renderer, police, "Select difficulty level", SDL_Rect{WINDOW_HEIGHT / 2, 50, 200, 50}, black);

        TTF_SetFontStyle(police, TTF_STYLE_NORMAL);
        Utilities::render_button(renderer, police, "Easy", button_1, black);
        Utilities::render_button(renderer, police, "Normal", button_2, black);
        Utilities::render_button(renderer, police, "Hard", button_3, black);
    }

    SDL_RenderPresent(renderer);
}
