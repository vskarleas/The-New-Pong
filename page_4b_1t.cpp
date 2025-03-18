/**
 * @file page_4b_1t.cpp
 * @brief Implementation of the mode selection menu page_4b_1t class
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#include "page_4b_1t.hpp"
#include "macros.hpp"
#include "renderers.hpp"
#include "game.hpp"

#include <SDL_mixer.h>
#include <iostream>
#include <string>

/**
 * @brief Constructor for the mode menu page
 * 
 * Initializes the menu with buttons for different game modes and an exit button
 * 
 * @param _renderer The SDL renderer to use for drawing
 * @param font The TTF font to use for text display
 */
page_4b_1t::page_4b_1t(SDL_Renderer *_renderer, TTF_Font *font) :
    mode_id(-1),
    exit_game(false),

    texture_menu(nullptr),
    renderer(_renderer),
    police(font)
{
    // Button dimensions
    const int button_width = 200;
    const int button_height = 50;
    const int vertical_spacing = 20;
    const int start_y = 150;

    const int center_x = (WINDOW_WIDTH - button_width) / 2;

    // Center all buttons horizontally and space them vertically
    button_ai_mode = SDL_Rect{center_x, start_y, button_width, button_height};
    button_two_players_mode = SDL_Rect{center_x, start_y + (button_height + vertical_spacing), button_width, button_height};
    button_storytime_mode = SDL_Rect{center_x, start_y + 2 * (button_height + vertical_spacing), button_width, button_height};
    button_fun_mode = SDL_Rect{center_x, start_y + 3 * (button_height + vertical_spacing), button_width, button_height};
    button_exit = SDL_Rect{center_x, start_y + 4 * (button_height + vertical_spacing), button_width, button_height};
}

/**
 * @brief Destructor for the mode menu page
 * 
 * Cleans up allocated resources
 */
page_4b_1t::~page_4b_1t()
{
    if (texture_menu)
    {
        SDL_DestroyTexture(texture_menu);
        texture_menu = nullptr;
    }
}

/**
 * @brief Handles events for the menu buttons
 * 
 * Processes SDL events to detect button clicks and set corresponding mode flags
 * 
 * @param event The SDL event to process
 * @return true if a button was clicked, false otherwise
 */
bool page_4b_1t::action_handler(const SDL_Event &event)
{
    // Reinitialising everything sinc ethis is a repeated menu
    mode_id = -1;
    exit_game = false;

    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        SDL_Point point = {event.button.x, event.button.y};

        // Ball selection menu clicks
        if (SDL_PointInRect(&point, &button_ai_mode))
        {
            Mix_PlayChannel(-1, Game::racket_hit_sound, 0);
            mode_id = AI_MODE;
            return true;
        }
        else if (SDL_PointInRect(&point, &button_two_players_mode))
        {
            Mix_PlayChannel(-1, Game::racket_hit_sound, 0);
            mode_id = TWO_PLAYERS_MODE;
            return true;
        }
        else if (SDL_PointInRect(&point, &button_storytime_mode))
        {
            Mix_PlayChannel(-1, Game::racket_hit_sound, 0);
            mode_id = STORYTIME_MODE;
            return true;
        }
        else if (SDL_PointInRect(&point, &button_fun_mode))
        {
            Mix_PlayChannel(-1, Game::racket_hit_sound, 0);
            mode_id = FUN_MODE;
            return true;
        }
        else if (SDL_PointInRect(&point, &button_exit))
        {
            exit_game = true;
            SDL_Event quitEvent;
            quitEvent.type = SDL_QUIT;
            SDL_PushEvent(&quitEvent);
            return true;
        }
    }
    return false;
}

/**
 * @brief Renders the mode menu
 * 
 * Draws the title and all game mode buttons on screen
 */
void page_4b_1t::render_object()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    TTF_SetFontStyle(police, TTF_STYLE_BOLD);
    Utilities::render_button(renderer, police, "Select mode", 
        SDL_Rect{(WINDOW_WIDTH - 200) / 2, 50, 200, 50},
        black);

    TTF_SetFontStyle(police, TTF_STYLE_NORMAL);
    Utilities::render_button(renderer, police, "AI mode", button_ai_mode, black);
    Utilities::render_button(renderer, police,"Classic Pong", button_two_players_mode, black);
    Utilities::render_button(renderer, police,"Storytime mode", button_storytime_mode, black);
    Utilities::render_button(renderer, police,"Fun mode", button_fun_mode, black);

    TTF_SetFontStyle(police, TTF_STYLE_BOLD);  // Set bold style for exit button
    Utilities::render_button(renderer, police, "Exit Game", button_exit, black);

    SDL_RenderPresent(renderer);
}