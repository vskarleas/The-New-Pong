/**
 * @file power.hpp
 * @brief Header defining the Power class for special game effects
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#ifndef POWER_HPP
#define POWER_HPP

#include <SDL.h>
#include <cstdlib>
#include <ctime>

#include "paddle.hpp"
#include "macros.hpp"
#include "ball_base.hpp"

/**
 * @class Power
 * @brief Class representing power-up items that affect gameplay
 *
 * This class defines powerups that can be collected during gameplay 
 * to modify game elements like paddle size.
 */
class Power
{
public:
    /**
     * @brief Constructor for the Power class
     * @param screen_width The width of the game screen
     * @param screen_height The height of the game screen
     */
    Power(int screen_width, int screen_height);

    /**
     * @brief Updates the power's position and effect
     * 
     * Virtual method that updates the game's parameters based on power effects
     * 
     * @param time Time delta since last update
     * @param racket1 Pointer to first paddle
     * @param racket2 Pointer to second paddle
     * @param ball_pos_x Ball's X position
     * @param ball_pos_y Ball's Y position
     * @param ball_radius Ball's radius
     * @param renderer SDL renderer for drawing
     */
    virtual void update(float time, Paddle *racket1, Paddle *racket2, SDL_Renderer *renderer, BallBase *ball);
    
    /**
     * @brief Renders the power on screen
     * @param renderer SDL renderer for drawing
     */
    virtual void render(SDL_Renderer *renderer);

    /**
     * @brief Checks for collision between the power and the ball
     * 
     * @param ball_type The ball object
     * @return true if collision detected, false otherwise
     */
    bool collision(BallBase *ball_type) const;
    
    /**
     * @brief Resets the power-up to a new random position
     * @param screen_width The width of the game screen
     */
    virtual void reset(int screen_width);
    
    /**
     * @brief Sets the active state of the power-up
     * @param active The new active state
     */
    void set_is_active(bool active) { is_active = active; }

    /**
     * @brief 
     * 
     */
    void set_effect_is_active(bool active) { effect_is_active = active; }
    

protected:
    float x = 0;                  /**< X position of the power-up */
    float y = 0;                  /**< Y position of the power-up */
    bool play = true;                    /**< Flag to determine which player gets the effect. It is used only on power.cpp but not on the herited classes */
    int width, height;            /**< Dimensions of the power-up */
    float speed;                  /**< Movement speed */
    float duration_effect = 0.0f; /**< Time remaining until effect ends */
    bool effect_is_active = false;/**< Whether the power's effect is currently active */
    SDL_Color color;              /**< Color of the power-up */
    bool is_active = false; /**< Used to determine if the power is currently visible and active */
    SDL_Texture* power_texture = nullptr; /**< Texture of the power-up as an image */
};

#endif
