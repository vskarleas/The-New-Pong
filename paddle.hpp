/**
 * @file paddle.hpp
 * @brief Header defining the Paddle class for the game
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#ifndef PADDLE_HPP
#define PADDLE_HPP
#include <SDL.h>

/**
 * @class Paddle
 * @brief Represents a player paddle/racket in the game
 *
 * This class handles the paddle's position, movement, rendering,
 * and collision detection for the game.
 */
class Paddle
{
public:
    /**
     * @brief Constructor for Paddle class
     * @param x The initial x-coordinate position
     * @param on_the_left_side True if this paddle is on the left side, false if right
     */
    Paddle(int x, bool on_the_left_side);

    /**
     * @brief Updates the paddle's position based on keyboard input
     * @param travel_time Time delta since last update (in seconds)
     */
    void update(float travel_time);
    
    /**
     * @brief Renders the paddle on screen
     * @param renderer The SDL renderer to use for drawing
     */
    void render_object(SDL_Renderer *renderer);
    
    /**
     * @brief Gets the paddle's SDL rectangle for collision detection
     * @return SDL_Rect representing the paddle's position and dimensions
     */
    SDL_Rect rectangle() const;

    /**
     * @brief Checks if this is the left paddle
     * @return True if this is the left paddle, false if right
     */
    bool get_is_left() const { return is_left; }

    /**
     * @brief Gets the paddle's x-coordinate
     * @return The paddle's x position
     */
    float get_pos_x() const { return pos_x; }

    /**
     * @brief Gets the paddle's y-coordinate
     * @return The paddle's y position
     */
    float get_pos_y() const { return pos_y; }

    /**
     * @brief Gets the paddle's movement speed
     * @return The paddle's speed value
     */
    float get_racket_speed() const { return racket_speed; }

    /**
     * @brief Gets the paddle's height
     * @return The height of the paddle
     */
    float get_racket_height() const { return racket_height; }

    /**
     * @brief Gets the paddle's width
     * @return The width of the paddle
     */
    float get_racket_width() const { return racket_width; }

    bool get_inverse_power_active() const { return inverse_power_active; }

    /**
     * @brief Sets the paddle's x-coordinate
     * @param x The new x position
     */
    void set_pos_x(float x) { pos_x = x; }

    /**
     * @brief Sets the paddle's y-coordinate
     * @param y The new y position
     */
    void set_pos_y(float y) { pos_y = y; }

    /**
     * @brief Sets the paddle's height
     * @param height The new height for the paddle
     */
    void set_racket_height(float height) { racket_height = height; }

    /**
     * @brief Sets the inverse_power_active boolean
     * @param power_active Declaration of the state for the inverse_power_active boolean
     */
    void set_inverse_power_active(bool power_active) { inverse_power_active = power_active; }

private:
    float pos_y;         /**< The paddle's y position */
    float pos_x;         /**< The paddle's x position */
    float racket_height; /**< The paddle's height */
    const float racket_width;  /**< The paddle's width (constant) */
    const float racket_speed;  /**< The paddle's movement speed (constant) */
    bool is_left;        /**< Whether this paddle is on the left side */
    bool inverse_power_active; /**< Whether this paddle is affected by the inverse power-up */
    float multiplier; /**< multiplier for the paddle's direction mouvement using the keyboard */
};
#endif