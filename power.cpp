/**
 * @file power.cpp
 * @brief Implementation of the Power class for special game effects
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#include "power.hpp"

#include <iostream>
#include <SDL_image.h>

/**
 * @brief Constructor for the Power class
 *
 * Initializes the power with random size and position
 *
 * @param screen_width The width of the game screen
 * @param screen_height The height of the game screen
 */
Power::Power(int screen_width, int screen_height)
{
    width = 30 + rand() % 20; // Size between 30 and 50 pixels
    height = 30 + rand() % 20;
    speed = 50.0f;        // Movement speed of 50 pixels/sec
    srand(time(nullptr)); // Initialize random colors
    reset(screen_width);
    power_texture = nullptr;
}

/**
 * @brief Updates the power's position and checks for collision with the ball
 *
 * Handles power movement, collision detection, and effect application/duration
 *
 * @param time Time delta since last update
 * @param racket1 Pointer to first paddle
 * @param racket2 Pointer to second paddle
 * @param ball The ball object
 * @param renderer SDL renderer for drawing
 */
void Power::update(float time, Paddle *racket1, Paddle *racket2, SDL_Renderer *renderer, BallBase *ball)
{
    // Power is visible and moving on screen
    if (is_active)
    {
        y += speed * time;

        if (collision(ball))
        {
            bool affects_player_one = (ball->get_pos_x() < x + width / 2);
            Paddle *affected_paddle = affects_player_one ? racket1 : racket2;

            // Apply the paddle size effect
            affected_paddle->set_racket_height(affected_paddle->get_racket_height() * 2);

            duration_effect = 0.0f; // it is using a time to determine if we need to stop the effect
            effect_is_active = true;
            is_active = false;

            // Render the updated paddle
            affected_paddle->render_object(renderer);

            // Remember which player was affected
            play = affects_player_one;
        }

        // Handle screen boundaries - bounce at edges
        if (y + height >= WINDOW_HEIGHT || y <= 0)
        {
            speed = -speed;

            // Ensure power stays on screen
            if (y <= 0)
                y = 5;
            if (y + height >= WINDOW_HEIGHT)
                y = WINDOW_HEIGHT - height - 5;
        }
    }

    else if (effect_is_active)
    {
        duration_effect += time;

        if (duration_effect >= 10.0)
        {
            Paddle *affected_paddle = play ? racket1 : racket2;

            // Return paddle to normal size
            affected_paddle->set_racket_height(affected_paddle->get_racket_height() / 2);

            // Reseting the flags otherwise we are lost on the logic
            effect_is_active = false;
            is_active = true;

            affected_paddle->render_object(renderer);

            reset(WINDOW_HEIGHT);
        }
    }
}

/**
 * @brief Renders the power on screen
 *
 * Draws a colored rectangle representing the power if it's active
 *
 * @param renderer SDL renderer for drawing
 */
void Power::render(SDL_Renderer *renderer)
{
    if (!is_active)
        return;

    if (!power_texture)
    {
        SDL_Surface *surface = IMG_Load("assets/robot-1.png");
        if (!surface)
        {
            // If image can not be loaded
            SDL_Log("Failed to load power image: %s", IMG_GetError());
            SDL_Rect rect = {static_cast<int>(x), static_cast<int>(y), width, height};
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
            SDL_RenderFillRect(renderer, &rect);
            return;
        }

        power_texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        if (!power_texture)
        {
            // What if image fails ?
            SDL_Log("Failed to create texture: %s", SDL_GetError());
            SDL_Rect rect = {static_cast<int>(x), static_cast<int>(y), width, height};
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
            SDL_RenderFillRect(renderer, &rect);
            return;
        }
    }

    // Render the power texture
    SDL_Rect dest = {static_cast<int>(x), static_cast<int>(y), width, height};
    SDL_RenderCopy(renderer, power_texture, NULL, &dest);
}

/**
 * @brief Checks for collision between the power and the ball
 *
 * @param ball_type Pointer to the ball object
 * @return true if collision detected, false otherwise
 */
bool Power::collision(BallBase *ball_type) const
{
    if (!is_active)
        return false;

    SDL_Rect power_object = {
        static_cast<int>(x),
        static_cast<int>(y),
        static_cast<int>(width),
        static_cast<int>(height)};

    SDL_Rect ball = ball_type->boundaries();

    return SDL_HasIntersection(&power_object, &ball);
}

/**
 * @brief Resets the power to a new random position
 *
 * @param screen_width The width of the game screen
 */
void Power::reset(int screen_width)
{
    int margin = screen_width * 0.1; // 10% margin from edges
    int available_width = screen_width - 2 * margin;
    x = margin + rand() % available_width;

    y = 1; // Allows to start from above the screen

    color = {static_cast<Uint8>(rand() % 256), static_cast<Uint8>(rand() % 256), static_cast<Uint8>(rand() % 256), 255};
    is_active = true; // Activate the power
}
