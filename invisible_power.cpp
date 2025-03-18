/**
 * @file invisible_power.cpp
 * @brief Implementation of the InvisiblePower class
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#include "invisible_power.hpp"
#include "macros.hpp"

#include <SDL.h>
#include <SDL_image.h>

/**
 * @brief Constructor for the InvisiblePower class
 *
 * Initializes the star-shaped power at a random position
 *
 * @param screen_width The width of the game screen
 * @param screen_height The height of the game screen
 */
InvisiblePower::InvisiblePower(int screen_width, int screen_height) : Power(screen_width, screen_height)
{
    speed = 80.0f;
    is_active = true;

    reset(WINDOW_HEIGHT);
}

/**
 * @brief Updates the power's position and handles ball visibility effects
 *
 * Manages the star's movement, collision detection, and ball invisibility timing
 *
 * @param time Time delta since last update
 * @param ball Pointer to the ball object
 * @param renderer SDL renderer for drawing
 */
void InvisiblePower::update(float time, BallBase *ball, SDL_Renderer *renderer)
{
    if (initialisation) // Only once, otherwise the ball will be invisible all the time
    {
        initialisation = false;
        ball->set_color(white);
    }

    // Star movement
    if (is_active)
    {
        y += speed * time;

        // color_change_timer += time;
        // if (color_change_timer >= 0.5f) // Change color every half second
        // {
        //     // Generate new random color
        //     color.r = static_cast<Uint8>(rand() % 256);
        //     color.g = static_cast<Uint8>(rand() % 256);
        //     color.b = static_cast<Uint8>(rand() % 256);
        //     color_change_timer = 0.0f;
        // }

        if (collision(ball))
        {
            is_active = false;
            effect_is_active = true;
            ball->set_color(black); // Make ball blend with background
            duration_effect = 0.0f; // Reset timer
            repeat = 0.0f;
        }

        if (y + height >= WINDOW_HEIGHT || y <= -40) // Reverse star movement at screen edges
        {
            speed = -speed;
        }
    }
    else if (effect_is_active)
    {
        duration_effect += time;
        repeat += time;

        if (duration_effect >= 3.0)
        {
            // Return ball to original color after 3 seconds
            ball->set_color(white);
            duration_effect = 3.0f;
        }

        if (repeat >= 13.0)
        {
            // Star reappears after 13 seconds
            is_active = true;
            effect_is_active = false;
            // y = 0; // Reset star position

            reset(WINDOW_HEIGHT);
        }
    }
}

/**
 * @brief Renders the star-shaped power on screen
 *
 * Draws a star shape using SDL rendering functions
 *
 * @param renderer SDL renderer for drawing
 */
void InvisiblePower::render(SDL_Renderer *renderer)
{
    if (!is_active)
        return;

    if (!power_texture)
    {
        SDL_Surface *surface = IMG_Load("assets/robot-3.png");
        if (!surface)
        {
            // Fallback to star rendering if image can't be loaded
            SDL_Log("Failed to load invisible power image: %s", IMG_GetError());

            // Original star rendering code as fallback
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

            float center_x = x + width / 2.0f;
            float center_y = y + height / 2.0f;
            float outer_radius = width / 2.0f;
            float inner_radius = outer_radius * 0.4f;

            // Create a 5-pointed star (10 points in total)
            SDL_Point points[10];
            for (int i = 0; i < 10; i++)
            {
                float angle = i * 36 * M_PI / 180;
                float radius = (i % 2 == 0) ? outer_radius : inner_radius;

                points[i].x = static_cast<int>(center_x + radius * sin(angle));
                points[i].y = static_cast<int>(center_y - radius * cos(angle));
            }

            // Draw star outline
            for (int i = 0; i < 10; i++)
            {
                SDL_RenderDrawLine(renderer,
                                   points[i].x, points[i].y,
                                   points[(i + 1) % 10].x, points[(i + 1) % 10].y);
            }

            for (int i = 0; i < 10; i += 2)
            {
                SDL_RenderDrawLine(renderer,
                                   center_x, center_y,
                                   points[i].x, points[i].y);
            }
            return;
        }

        power_texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        if (!power_texture)
        {
            SDL_Log("Failed to create texture: %s", SDL_GetError());
            return;
        }
    }

    // Render the texture
    SDL_Rect dest = {static_cast<int>(x), static_cast<int>(y), width, height};
    SDL_RenderCopy(renderer, power_texture, NULL, &dest);
}

void InvisiblePower::reset(int screen_width)
{
    int min_x = screen_width * 0.1;
    int max_x = screen_width * 0.6;

    x = min_x + rand() % (max_x - min_x);
    y = 0;

    color = {static_cast<Uint8>(rand() % 256), static_cast<Uint8>(rand() % 256), static_cast<Uint8>(rand() % 256), 255};
    is_active = true;
}