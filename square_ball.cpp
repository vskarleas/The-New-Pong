/**
 * @file square_ball.cpp
 * @brief Implementation of the SquareBall class
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#include "square_ball.hpp"
#include "renderers.hpp"

/**
 * @brief Renders the square ball on screen
 * 
 * Uses the square_renderer function to draw a square shape
 * at the ball's current position with the specified size and color
 * 
 * @param renderer The SDL renderer used for drawing
 */
void SquareBall::render_object(SDL_Renderer *renderer)
{
    square_renderer()(renderer, pos_x, pos_y, ball_size, color);
}