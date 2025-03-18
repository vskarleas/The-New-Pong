/**
 * @file inverse_power.cpp
 * @brief Header defining the InversiblePower class for paddles' temporary arrows control effect
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#ifndef INVERSE_POWER_HPP
#define INVERSE_POWER_HPP

#include "power.hpp"
#include "macros.hpp"

/**
 * @class InversiblePower
 * @brief Power-up that inverts paddle controls temporarily
 * 
 * This power-up appears as an arrow on screen. When a player hits it with the ball,
 * that player's paddle controls are inverted (up becomes down and vice versa) for a 
 * short period of time.
 */
class InversiblePower : public Power {
    public:
        /**
         * @brief Constructor for InversiblePower
         * @param screen_width Width of the game screen
         * @param screen_height Height of the game screen
         */
        InversiblePower(int screen_width, int screen_height);
        
        /**
         * @brief Updates the power-up state
         * @param time Delta time since last update
         * @param racket1 Pointer to the first paddle
         * @param racket2 Pointer to the second paddle
         * @param renderer SDL renderer to draw effects
         * @param ball Pointer to the game ball
         */
        void update(float time, Paddle* racket1, Paddle* racket2, SDL_Renderer* renderer, BallBase *ball) override;
        
        /**
         * @brief Renders the power-up on screen
         * @param renderer SDL renderer to draw the power-up
         */
        void render(SDL_Renderer* renderer) override;
        
        /**
         * @brief Resets the power-up position
         * @param screen_width Width of the game screen for positioning
         */
        void reset(int screen_width) override;

    private:
        bool inverse_paddle = false; /**< Whether the power is currently active for a specific paddle */
        float repeat;                /**< Timer for power-up respawn */
    };

#endif
