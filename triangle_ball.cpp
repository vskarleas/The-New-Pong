/**
 * @file triangle_ball.cpp
 * @brief Implementation of the TriangleBall class
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#include "triangle_ball.hpp"
#include "renderers.hpp"

#include <algorithm>

/**
 * @brief Renders the triangle ball on screen
 * 
 * Uses the triangle_renderer function to draw a triangle shape
 * at the ball's current position with the specified size and color
 * 
 * @param renderer The SDL renderer used for drawing
 */
void TriangleBall::render_object(SDL_Renderer *renderer)
{
    triangle_renderer()(renderer, pos_x, pos_y, ball_size, color);
}