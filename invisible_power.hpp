/**
 * @file invisible_power.hpp
 * @brief Header defining the InvisiblePower class for ball visibility effects
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#ifndef INVISIBLE_POWER_HPP
#define INVISIBLE_POWER_HPP
#include <SDL.h>
#include <SDL_ttf.h>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "ball_base.hpp"
#include "power.hpp"

/**
 * @class InvisiblePower
 * @brief Power-up that makes the ball temporarily invisible
 *
 * This class implements a special star-shaped power-up that, when collected,
 * makes the ball invisible for a period of time.
 */
class InvisiblePower : public Power
{
public:
    /**
     * @brief Constructor for the InvisiblePower class
     * @param screen_width The width of the game screen
     * @param screen_height The height of the game screen
     */
    InvisiblePower(int screen_width, int screen_height);

    /**
     * @brief Updates the power's position and the ball's visibility
     * 
     * @param time Time delta since last update
     * @param Ball Pointer to the ball object
     * @param renderer SDL renderer for drawing
     */
    void update(float time, BallBase *Ball, SDL_Renderer *renderer); // no need for override becase the declaration is completly different (do not share the same arguments structure)
    
    /**
     * @brief Renders the power as a star on screen
     * @param renderer SDL renderer for drawing
     */
    void render(SDL_Renderer *renderer) override;
    
    /**
     * @brief Resets the power to a new random position
     * @param screen_width The width of the game screen
     */
    void reset(int screen_width) override;

    /**
     * @brief Sets the initialization flag
     * @param init The initialization state to set
     */
    void set_initialisation(bool init) { initialisation = init; }

private:
    float repeat;                /**< Timer for power-up respawn */
    bool initialisation;         /**< Flag for first-time initialization */
};

#endif
