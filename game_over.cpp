/**
 * @file game_over.cpp
 * @brief Implementation of the game_over screen class
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#include "game_over.hpp"
#include "renderers.hpp"
#include "macros.hpp"

/**
 * @brief Constructor for the game_over class
 * 
 * Initializes the game over screen with default values and sets up the back button
 * 
 * @param _renderer The SDL renderer to use for drawing
 * @param font The TTF font to use for text display
 */
GameOver::GameOver(SDL_Renderer *_renderer, TTF_Font *font) : texture_menu(nullptr),
                                                                renderer(_renderer),
                                                                police(font),
                                                                go_back(false) // be default we don't go back on the modes menu
{
    const int button_width = 200;
    const int button_height = 50;
    const int base_y = WINDOW_WIDTH - 400;
    const int center_x = WINDOW_HEIGHT / 2;

    // "Go back" button above "Let's go" button
    button_back = SDL_Rect{center_x, base_y, button_width, button_height};
}

/**
 * @brief Destructor for the game_over class
 * 
 * Cleans up allocated resources
 */
GameOver::~GameOver()
{
    if (texture_menu)
    {
        SDL_DestroyTexture(texture_menu);
        texture_menu = nullptr;
    }
}

/**
 * @brief Handles user interaction events
 * 
 * Processes SDL events to detect button clicks, particularly for the back button
 * 
 * @param event The SDL event to process
 * @return true if the back button is pressed, false otherwise
 */
bool GameOver::action_handler(const SDL_Event &event)
{
    go_back = false; // Reset the flag for going back on the choose menu

    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        SDL_Point point = {event.button.x, event.button.y};

        if (SDL_PointInRect(&point, &button_back))
        {
            go_back = true;
            return true;
        }
    }

    return false;
}

/**
 * @brief Renders the game over screen
 * 
 * Displays the game over message, the winner's name, and the back button
 */
void GameOver::render_object()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Add notice text
    TTF_SetFontStyle(police, TTF_STYLE_NORMAL);
    TTF_SetFontSize(police, 14);

    const char *notice_text[20]; // Define a fixed size array
    int text_size = 0;           // To keep track of array size

    notice_text[0] = "Game is over !";
    notice_text[1] = "";
    std::string winner = "Winner: " + winner_name + "!";
    notice_text[2] = winner.c_str();
    notice_text[3] = "Feel free to go back to the new menu ";
    text_size = 4;

    int y_position = 100;
    for (int i = 0; i < text_size; i++)
    {
        SDL_Rect text_rect = {WINDOW_WIDTH / 4, y_position, 400, 18};
        Utilities::render_button(renderer, police, notice_text[i], text_rect, black);
        y_position += 20;
    }

    // Render Let's Go button
    TTF_SetFontSize(police, 24);
    TTF_SetFontStyle(police, TTF_STYLE_BOLD);
    Utilities::render_button(renderer, police, "Back to menu", button_back, black);

    SDL_RenderPresent(renderer);
}

/**
 * @brief Sets the winner's name to display on the game over screen
 * 
 * @param name The name of the winner to be displayed
 */
void GameOver::set_winner(const std::string &name)
{
    winner_name = name;
}