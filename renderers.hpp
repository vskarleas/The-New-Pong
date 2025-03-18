/**
 * @file renderers.hpp
 * @brief Header defining renderers for various game shapes
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#ifndef RENDER_HPP
#define RENDER_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <algorithm>

/**
 * @namespace Utilities
 * @brief Utility functions for rendering common UI elements
 */
namespace Utilities
{
    /**
     * @brief Renders a text button on screen
     *
     * @param renderer The SDL renderer used for drawing
     * @param font The TTF font used for rendering text
     * @param text The text to display on the button
     * @param button The rectangle defining the button's position and size
     * @param color The color of the text
     */
    void render_button(SDL_Renderer *renderer, TTF_Font *font, const char *text,
                       const SDL_Rect &button, const SDL_Color &color);
}

/**
 * @struct circle_renderer
 * @brief Functor for rendering circular shapes
 *
 * This struct provides an operator to render filled circles at specified positions
 */
struct circle_renderer
{
    /**
     * @brief Renders a circular shape at the specified position
     *
     * @param renderer The SDL renderer used for drawing
     * @param pos_x The x coordinate of the circle's center
     * @param pos_y The y coordinate of the circle's center
     * @param size The diameter of the circle
     * @param color The color to fill the circle with
     */
    void operator()(SDL_Renderer *renderer, float pos_x, float pos_y, float size, SDL_Color color) const;

private:
    /**
     * @brief Helper method to draw a filled circle
     *
     * @param renderer The SDL renderer used for drawing
     * @param center_x The x coordinate of the circle's center
     * @param center_y The y coordinate of the circle's center
     * @param radius The radius of the circle
     */
    void DrawFilledCircle(SDL_Renderer *renderer, int32_t center_x, int32_t center_y, int32_t radius) const;
};

/**
 * @struct square_renderer
 * @brief Functor for rendering square shapes
 *
 * This struct provides an operator to render filled squares at specified positions
 */
struct square_renderer
{
    /**
     * @brief Renders a square shape at the specified position
     *
     * @param renderer The SDL renderer used for drawing
     * @param pos_x The x coordinate of the square's center
     * @param pos_y The y coordinate of the square's center
     * @param size The side length of the square
     * @param color The color to fill the square with
     */
    void operator()(SDL_Renderer *renderer, float pos_x, float pos_y, float size, SDL_Color color) const;
};

/**
 * @struct triangle_renderer
 * @brief Functor for rendering triangle shapes
 *
 * This struct provides an operator to render filled triangles at specified positions
 */
struct triangle_renderer
{
    /**
     * @brief Renders a triangle shape at the specified position
     *
     * @param renderer The SDL renderer used for drawing
     * @param pos_x The x coordinate of the triangle's center
     * @param pos_y The y coordinate of the triangle's center
     * @param size The size of the triangle (height)
     * @param color The color to fill the triangle with
     */
    void operator()(SDL_Renderer *renderer, float pos_x, float pos_y, float size, SDL_Color color) const;
};

#endif