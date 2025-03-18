/**
 * @file ball_base.cpp
 * @brief Implementation of the BallBase class
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#include <cstdlib>
#include <ctime>
#include <cmath>

#include "paddle.hpp"
#include "ball_base.hpp"
#include "game.hpp"

/**
 * @brief Constructor for BallBase
 * 
 * Initializes the ball at the center of the screen with a specified size
 * and randomizes its initial direction
 * 
 * @param size The size (diameter) of the ball
 */
BallBase::BallBase(float size)
    : pos_x(400.0f), pos_y(300.0f), vel_x(0.0f), vel_y(0.0f), ball_size(size)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    random_direction_angle();
}

/**
 * @brief Randomizes the direction of the ball
 * 
 * Sets the ball's velocity to move in a random direction
 * with a random angle between -45 and 45 degrees
 */
void BallBase::random_direction_angle()
{
    // Random angle between -45 and 45 degrees
    float angle = (std::rand() % 90 - 45) * 3.14159f / 180.0f;
    float speed = 300.0f;

    // Randomly choose left or right direction with a base angle
    float direction_angle = (std::rand() % 2) ? 0.0f : 3.14159f;
    angle += direction_angle;

    vel_x = speed * std::cos(angle);
    vel_y = speed * std::sin(angle);
}

/**
 * @brief Updates the ball's position and handles collisions
 * 
 * Moves the ball according to its velocity, checks for collisions with
 * walls and paddles, and updates player scores when necessary.
 * 
 * @param travel_time Time delta since last update (in seconds)
 * @param paddle1 Pointer to the first paddle
 * @param paddle2 Pointer to the second paddle
 * @param player1 Pointer to the first player's data
 * @param player2 Pointer to the second player's data
 */
void BallBase::update(float travel_time, Paddle *paddle1, Paddle *paddle2, User *player1, User *player2)
{
    pos_x += vel_x * travel_time; // velocity = position / time => position = velocity * time
    pos_y += vel_y * travel_time;

    // Wall collision sound
    if (pos_y <= 0.0f || pos_y >= 600.0f)
    {
        Mix_PlayChannel(-1, Game::mWallHitSound, 0);
    }

    // Check if the ball hit the top or bottom of the screen so that we reverse the velocity direction
    if (pos_y <= 0.0f)
    {
        pos_y = 0.0f;
        vel_y *= -1;
    }
    else if (pos_y >= 600.0f)
    {
        pos_y = 600.0f;
        vel_y *= -1;
    }

    if (pos_x <= 0.0f || pos_x >= 800.0f)
    {
        Mix_PlayChannel(-1, Game::mScoreSound, 0);

        // Check if the ball hit the left or right side of the screen and we update the score
        if (pos_x <= 0.0f)
        {
            player2->increment_score();
            reset(); // starting the new round
        }
        else if (pos_x >= 800.0f)
        {
            player1->increment_score();
            reset();
        }
    }

    SDL_Rect ballRect = {
        static_cast<int>(pos_x - ball_size / 2.0f),
        static_cast<int>(pos_y - ball_size / 2.0f),
        static_cast<int>(ball_size),
        static_cast<int>(ball_size)};

    SDL_Rect paddle1Rect = paddle1->rectangle();
    SDL_Rect paddle2Rect = paddle2->rectangle();

    if (SDL_HasIntersection(&ballRect, &paddle1Rect))
    {
        Mix_PlayChannel(-1, Game::racket_hit_sound, 0);
        pos_x = paddle1Rect.x + paddle1Rect.w + ball_size / 2.0f;
        vel_x *= -1.1f;
    }
    else if (SDL_HasIntersection(&ballRect, &paddle2Rect))
    {
        Mix_PlayChannel(-1, Game::racket_hit_sound, 0);
        pos_x = paddle2Rect.x - ball_size / 2.0f;
        vel_x *= -1.1f;
    }
}

/**
 * @brief Resets the ball to the center of the screen
 * 
 * Repositions the ball to the center and randomizes its direction
 */
void BallBase::reset()
{
    pos_x = 400.0f;
    pos_y = 300.0f;
    random_direction_angle();
}