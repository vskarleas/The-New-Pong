/**
 * @file ball_base.hpp
 * @brief Base class for all ball types in the game
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#ifndef BALL_BASE_HPP
#define BALL_BASE_HPP

#include <SDL.h>
#include "user.hpp"

/**
 * @class BallBase
 * @brief Abstract base class for all ball types in the game
 *
 * This class defines the common interface and functionality for
 * all types of balls in the game. It handles movement, collision
 * detection, and score updates.
 */
class BallBase
{
public:
    /**
     * @brief Constructor for BallBase
     * @param size The size (diameter) of the ball, defaults to 15.0f
     */
    BallBase(float size = 35.0f);
    
    /**
     * @brief Virtual destructor for proper cleanup in derived classes
     */
    virtual ~BallBase() {};

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
    virtual void update(float travel_time, class Paddle *paddle1, class Paddle *paddle2, User *player1, User *player2);

    /**
     * @brief Pure virtual method to render the ball
     * 
     * Must be implemented by derived classes to draw their specific ball shape
     * 
     * @param renderer The SDL renderer to use for drawing
     */
    virtual void render_object(SDL_Renderer *renderer) = 0;

    /**
     * @brief Resets the ball to the center of the screen
     * 
     * Repositions the ball and randomizes its direction
     */
    virtual void reset();

    /**
     * @brief Randomizes the direction of the ball
     * 
     * Changes the ball's velocity to move in a random direction
     */
    void random_direction_angle();

    /**
     * @brief Sets the position of the ball
     * 
     * @param x The new x-coordinate
     * @param y The new y-coordinate
     */
    void set_position(float x, float y)
    {
        pos_x = x;
        pos_y = y;
    }

    /**
     * @brief Sets the velocity of the ball
     * 
     * @param velX The new x-velocity component
     * @param velY The new y-velocity component
     */
    void set_velocity(float velX, float velY)
    {
        vel_x = velX;
        vel_y = velY;
    }

    /**
     * @brief Sets the color of the ball
     * 
     * @param new_color The new color as an SDL_Color
     */
    void set_color(const SDL_Color &new_color) { color = new_color; }

    /**
     * @brief Gets the collision boundaries of the ball
     * 
     * Returns a rectangle representing the ball's position and size
     * for collision detection purposes.
     * 
     * @return SDL_Rect representing the ball's boundaries
     */
    virtual SDL_Rect boundaries() const
    {
        return SDL_Rect{
            static_cast<int>(pos_x - ball_size / 2.0f),
            static_cast<int>(pos_y - ball_size / 2.0f),
            static_cast<int>(ball_size),
            static_cast<int>(ball_size)};
    }

    /**
     * @brief Gets the x-velocity component of the ball
     * @return The ball's velocity along the x-axis
     */
    float get_vel_x() const { return vel_x; }

    /**
     * @brief Gets the y-velocity component of the ball
     * @return The ball's velocity along the y-axis
     */
    float get_vel_y() const { return vel_y; }

    /**
     * @brief Gets the x-coordinate of the ball
     * @return The ball's x position
     */
    float get_pos_x() const { return pos_x; }

    /**
     * @brief Gets the y-coordinate of the ball
     * @return The ball's y position
     */
    float get_pos_y() const { return pos_y; }

    /**
     * @brief Gets the color of the ball
     * @return The ball's color as an SDL_Color structure
     */
    SDL_Color get_color() const { return color; }

    void set_game_mode (int mode ) { game_mode = mode; }
    int get_game_mode() const { return game_mode; }

protected:
    float pos_x;           /**< Ball's x position */
    float pos_y;           /**< Ball's y position */
    float vel_x;           /**< Ball's x velocity */
    float vel_y;           /**< Ball's y velocity */
    const float ball_size; /**< Ball's size (diameter by default) */
    SDL_Color color;       /**< Ball's color */
    int game_mode = -1;
};

#endif