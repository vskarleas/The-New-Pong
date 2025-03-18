/**
 * @file gui.cpp
 * @brief Implementation of the GUI class for game interface
 * @authors Vasileios Filippos Skarleas, Dounia Bakalem, Yanis Sadoun
 * @copyright All rights reserved.
 */

#include "gui.hpp"
#include "macros.hpp"

/**
 * @brief Displays an input field for a player to enter their name
 * 
 * This function creates an SDL window with an input field where the player
 * can type their name. It manages all input events and rendering.
 * 
 * @param renderer The SDL renderer to use for drawing
 * @param font The TTF font to use for text display
 * @param player_number The player number (for display purposes)
 * @return std::string The name entered by the player
 */
std::string GUI::player_name_input(SDL_Renderer *renderer, TTF_Font *font, int player_number)
{
    std::string player_name;
    SDL_Event event;
    bool typing = true;

    // Text color (black)
    SDL_Color color = {0, 0, 0, 0};
    
    /**
     * @brief Define UI element positions and dimensions
     * Centers the input field and instruction text on screen
     */
    int center_x = WINDOW_WIDTH / 2;
    SDL_Rect inputRect = {
        center_x - 100,  // Center the input field (200px wide)
        WINDOW_HEIGHT / 2,
        200,
        50
    };
    
    SDL_Rect instruction_rectangle = {
        center_x - 150,  // Center the instruction (300px wide)
        WINDOW_HEIGHT / 3,
        300,
        50
    };

    /**
     * @brief Initialize the white background
     */
    SDL_Surface *background_surface = SDL_CreateRGBSurface(0, WINDOW_WIDTH, WINDOW_HEIGHT, 32, 0, 0, 0, 0);
    SDL_FillRect(background_surface, NULL, SDL_MapRGB(background_surface->format, 255, 255, 255));
    SDL_Texture *background_texture = SDL_CreateTextureFromSurface(renderer, background_surface);

    /**
     * @brief Main input loop
     * Processes keyboard events and updates the display
     */
    while (typing)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                typing = false;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_RETURN)
                {
                    typing = false;
                }
                else if (event.key.keysym.sym == SDLK_BACKSPACE && player_name.length() > 0)
                {
                    player_name.pop_back();
                }
                else if (event.key.keysym.sym != SDLK_RETURN && event.key.keysym.sym != SDLK_BACKSPACE)
                {
                    char c = event.key.keysym.sym;
                    if (isprint(c))
                    {
                        player_name += c;
                    }
                }
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background_texture, nullptr, nullptr);

        /**
         * @brief Render the instruction text
         */
        TTF_SetFontStyle(font, TTF_STYLE_BOLD);
        std::string instruction = "Player " + std::to_string(player_number) + ", please enter your name:";
        const char *instruction_text = instruction.c_str();
        SDL_Surface *instruction_surface = TTF_RenderText_Solid(font, instruction_text, color);
        SDL_Texture *instruction_texture = SDL_CreateTextureFromSurface(renderer, instruction_surface);

        // Center the instruction text
        SDL_Rect actualinstruction_rectangle = {
            center_x - (instruction_surface->w / 2),
            instruction_rectangle.y,
            instruction_surface->w,
            instruction_surface->h
        };

        SDL_RenderCopy(renderer, instruction_texture, nullptr, &actualinstruction_rectangle);
        SDL_FreeSurface(instruction_surface);
        SDL_DestroyTexture(instruction_texture);

        /**
         * @brief Render the input text
         */
        if (!player_name.empty())
        {
            TTF_SetFontStyle(font, TTF_STYLE_NORMAL);

            SDL_Surface *text_surface = TTF_RenderText_Solid(font, player_name.c_str(), color);
            SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, text_surface);
            
            // Center the input text
            SDL_Rect actualInputRect = {
                center_x - (text_surface->w / 2),
                inputRect.y,
                text_surface->w,
                text_surface->h
            };

            SDL_RenderCopy(renderer, textTexture, nullptr, &actualInputRect);
            SDL_FreeSurface(text_surface);
            SDL_DestroyTexture(textTexture);
        }

        SDL_RenderPresent(renderer);
    }

    /**
     * @brief Cleanup resources before returning
     */
    SDL_DestroyTexture(background_texture);
    SDL_FreeSurface(background_surface);

    return player_name;
}