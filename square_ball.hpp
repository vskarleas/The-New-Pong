/**
 * @file square_ball.hpp
 * @brief Header defining the SquareBall class
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#ifndef SQUARE_BALL_HPP
#define SQUARE_BALL_HPP

#include "ball_base.hpp"

/**
 * @class SquareBall
 * @brief Square shaped ball implementation inheriting from BallBase
 *
 * This class implements a square-shaped ball for the game by 
 * overriding the render_object method from the base class.
 */
class SquareBall : public BallBase
{
public:
    /**
     * @brief Constructor for SquareBall
     * 
     * Initializes a square ball with a default size of 20.0f
     */
    SquareBall() : BallBase(20.0f) {}
    
    /**
     * @brief Renders the square ball on screen
     * 
     * Overrides the base class method to render a square shape
     * using the square_renderer function
     * 
     * @param renderer The SDL renderer to use for drawing
     */
    void render_object(SDL_Renderer *renderer) override;
};

#endif