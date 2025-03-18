/**
 * @file triangle_ball.hpp
 * @brief Header defining the TriangleBall class
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#ifndef TRIANGLE_BALL_HPP
#define TRIANGLE_BALL_HPP

#include "ball_base.hpp"

/**
 * @class TriangleBall
 * @brief Triangle shaped ball implementation inheriting from BallBase
 *
 * This class implements a triangle-shaped ball for the game by 
 * overriding the render_object method from the base class.
 */
class TriangleBall : public BallBase
{
public:
    /**
     * @brief Constructor for TriangleBall
     * 
     * Initializes a triangle ball with a default size of 20.0f
     */
    TriangleBall() : BallBase(20.0f) {}
    
    /**
     * @brief Renders the triangle ball on screen
     * 
     * Overrides the base class method to render a triangle shape
     * using the triangle_renderer function
     * 
     * @param renderer The SDL renderer to use for drawing
     */
    void render_object(SDL_Renderer *renderer) override;
};

#endif