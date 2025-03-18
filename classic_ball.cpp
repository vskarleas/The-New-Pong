/**
 * @file classic_ball.cpp
 * @brief Implementation of the classic circular ball ClassicBall class
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#include "classic_ball.hpp"
#include "renderers.hpp"
#include "macros.hpp"

#include <SDL_image.h>
#include <iostream>

/**
 * @brief Helper function to draw a filled circle
 *
 * Uses the midpoint circle algorithm to efficiently render a filled circle
 *
 * @param renderer The SDL renderer to use for drawing
 * @param center_x The x coordinate of the circle's center
 * @param center_y The y coordinate of the circle's center
 * @param radius The radius of the circle
 */
void DrawFilledCircle(SDL_Renderer *renderer, int32_t center_x, int32_t center_y, int32_t radius)
{
    const int32_t diameter = (radius * 2);
    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        // Draw horizontal lines to fill the circle
        SDL_RenderDrawLine(renderer, center_x - x, center_y + y, center_x + x, center_y + y);
        SDL_RenderDrawLine(renderer, center_x - x, center_y - y, center_x + x, center_y - y);
        SDL_RenderDrawLine(renderer, center_x - y, center_y + x, center_x + y, center_y + x);
        SDL_RenderDrawLine(renderer, center_x - y, center_y - x, center_x + y, center_y - x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

/**
 * @brief Renders the classic ball on screen
 *
 * Uses the circle_renderer function to draw a circular shape
 * at the ball's current position with the specified size and color
 *
 * @param renderer The SDL renderer used for drawing
 */
// void ClassicBall::render_object(SDL_Renderer *renderer)
// {
//     circle_renderer()(renderer, pos_x, pos_y, ball_size, color);
// }

void ClassicBall::render_object(SDL_Renderer *renderer)
{

    if (game_mode == FUN_MODE)
    {
        circle_renderer()(renderer, pos_x, pos_y, 15.0f, color); // passing the size manually in order to differentate the size for image or no image rendering that can impact the visuals
    }
    else
    {
        if (!ball_texture)
        {
            SDL_Surface *surface = IMG_Load("assets/ball.png");
            if (!surface)
            {
                std::cerr << "Failed to load ball image: " << IMG_GetError() << std::endl;

                // Fall back to circle rendering if image fails to load
                circle_renderer()(renderer, pos_x, pos_y, ball_size, color);
                return;
            }

            // Create texture from surface
            ball_texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);

            if (!ball_texture)
            {
                std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
                // Fall back to circle rendering if texture creation fails
                circle_renderer()(renderer, pos_x, pos_y, ball_size, color);
                return;
            }

            // Set color modulation to match current ball color
            SDL_SetTextureColorMod(ball_texture, color.r, color.g, color.b);
        }

        // Update texture color modulation if color has changed
        SDL_SetTextureColorMod(ball_texture, color.r, color.g, color.b);

        // Calculate render destination
        SDL_Rect dest = {
            static_cast<int>(pos_x - ball_size / 2),
            static_cast<int>(pos_y - ball_size / 2),
            static_cast<int>(ball_size),
            static_cast<int>(ball_size)};

        // Render the ball texture
        SDL_RenderCopy(renderer, ball_texture, NULL, &dest);
    }
}