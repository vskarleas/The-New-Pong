/**
 * @file classic_ball.hpp
 * @brief Header defining the classic circular ball ClassicBall class
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#ifndef CLASSIC_BALL_HPP
#define CLASSIC_BALL_HPP

#include "ball_base.hpp"

/**
 * @class ClassicBall
 * @brief Classic circular ball implementation inheriting from BallBase
 *
 * This class implements a circular ball, the standard ball type in Pong,
 * by overriding the render_object method from the base class.
 */
class ClassicBall : public BallBase
{
public:
    /**
     * @brief Constructor for ClassicBall
     * 
     * Initializes a classic circular ball with a default size of 15.0f
     */
    ClassicBall() : BallBase(24.0f) {}

    /**
     * @brief Renders the classic ball on screen
     * 
     * Overrides the base class method to render a circular shape
     * using the circle_renderer function
     * 
     * @param renderer The SDL renderer to use for drawing
     */
    void render_object(SDL_Renderer *renderer) override;

    private:
        SDL_Texture* ball_texture = nullptr;
};

#endif