/**
 * @file paddle.cpp
 * @brief Implementation of the Paddle class for the game
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#include "paddle.hpp"
#include "macros.hpp"

/**
 * @brief Constructing the Racket object for the game
 *
 * @param x Initial x-coordinate position
 * @param on_the_left_side True if this paddle is on the left side, false if right
 */
Paddle::Paddle(int x, bool on_the_left_side) : // Paddle's position on the screen initially
                                               pos_y(static_cast<float>(WINDOW_HEIGHT / 2)),
                                               pos_x(static_cast<float>(x)),

                                               // Paddle's caracteristics that compose the object height x width
                                               racket_height(100.0f),
                                               racket_width(15.0f),

                                               // Paddle's speed for mouvement
                                               racket_speed(300.0f),
                                               is_left(on_the_left_side)
{
}

/**
 * @brief Updating the paddle's position on the screen
 *
 * @param travel_time Time delta since last update (in seconds)
 */
void Paddle::update(float travel_time)
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    /**
     * @brief Lambda for moving the paddle
     * @param delta Direction multiplier (-1 for up, 1 for down)
     * @param time Time delta for smooth movement
     */
    auto move_paddle = [this](float delta, float time)
    {
        this->set_pos_y(this->get_pos_y() + delta * this->get_racket_speed() * time);
    };

    /**
     * @brief Lambda for checking and adjusting paddle boundaries
     */
    auto adjust_boundaries = [this]()
    {
        if (this->get_pos_y() < this->get_racket_height() / 2.0f)
        {
            this->set_pos_y(this->get_racket_height() / 2.0f);
        }
        else if (this->get_pos_y() > 600.0f - this->get_racket_height() / 2.0f)
        {
            this->set_pos_y(600.0f - this->get_racket_height() / 2.0f);
        }
    };

    // The mouvement
    if (Paddle::get_inverse_power_active())
    {
        multiplier = -1.0f;
    }
    else
    {
        multiplier = 1.0f;
    }

    if (Paddle::get_is_left())
    {
        if (state[SDL_SCANCODE_W])
        {
            move_paddle(-1.0f * multiplier, travel_time);
        }
        if (state[SDL_SCANCODE_S])
        {
            move_paddle(1.0f * multiplier, travel_time);
        }
    }
    else
    {
        if (state[SDL_SCANCODE_UP])
        {
            move_paddle(-1.0f * multiplier, travel_time);
        }
        if (state[SDL_SCANCODE_DOWN])
        {
            move_paddle(1.0f * multiplier, travel_time);
        }
    }

    // Adjust paddle position if it's out of bounds
    adjust_boundaries();
}
/* The lambdas make the code more modular and easier to modify if we need to change the movement behavior or boundary conditions later for the paddle. */

/**
 * @brief Drawing the paddle on the screen
 *
 * @param renderer The SDL renderer to use for drawing
 */
void Paddle::render_object(SDL_Renderer *renderer)
{
    SDL_Rect paddle = {
        static_cast<int>(Paddle::get_pos_x() - Paddle::get_racket_width() / 2.0f),
        static_cast<int>(Paddle::get_pos_y() - Paddle::get_racket_height() / 2.0f),
        static_cast<int>(Paddle::get_racket_width()),
        static_cast<int>(Paddle::get_racket_height())};
    SDL_RenderFillRect(renderer, &paddle);
}

/**
 * @brief Getting the paddle's position on the screen on SDL
 *
 * @return SDL_Rect representing the paddle's position and dimensions
 */
SDL_Rect Paddle::rectangle() const
{
    SDL_Rect rect = {
        static_cast<int>(Paddle::get_pos_x() - Paddle::get_racket_width() / 2.0f),
        static_cast<int>(Paddle::get_pos_y() - Paddle::get_racket_height() / 2.0f),
        static_cast<int>(Paddle::get_racket_width()),
        static_cast<int>(Paddle::get_racket_height())};
    return rect;
}