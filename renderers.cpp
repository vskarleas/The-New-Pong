/**
 * @file renderers.cpp
 * @brief Implementation of rendering functions for various game shapes
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#include "renderers.hpp"
#include <iostream>

namespace Utilities
{
    /**
     * @brief Renders a text button on screen
     *
     * Creates a text surface, converts it to a texture, and renders it
     * centered on the provided button rectangle.
     *
     * @param renderer The SDL renderer used for drawing
     * @param font The TTF font used for rendering text
     * @param text The text to display on the button
     * @param button The rectangle defining the button's position and size
     * @param color The color of the text
     */
    void render_button(SDL_Renderer *renderer, TTF_Font *font, const char *text,
                       const SDL_Rect &button, const SDL_Color &color)
    {
        SDL_Surface *text_surface = TTF_RenderText_Solid(font, text, color);
        if (text_surface)
        {
            SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
            if (text_texture)
            {
                SDL_Rect textRect = {
                    button.x + (button.w - text_surface->w) / 2,
                    button.y + (button.h - text_surface->h) / 2,
                    text_surface->w,
                    text_surface->h};
                SDL_RenderCopy(renderer, text_texture, nullptr, &textRect);
                SDL_DestroyTexture(text_texture);
            }
            SDL_FreeSurface(text_surface);
        }
    }
}

/**
 * @brief Helper method to draw a filled circle
 *
 * Uses the midpoint circle algorithm to efficiently render a filled circle.
 *
 * @param renderer The SDL renderer used for drawing
 * @param center_x The x coordinate of the circle's center
 * @param center_y The y coordinate of the circle's center
 * @param radius The radius of the circle
 */
void circle_renderer::DrawFilledCircle(SDL_Renderer *renderer, int32_t center_x, int32_t center_y, int32_t radius) const
{
    const int32_t diameter = (radius * 2);
    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        SDL_RenderDrawLine(renderer, center_x - x, center_y + y, center_x + x, center_y + y);
        SDL_RenderDrawLine(renderer, center_x - x, center_y - y, center_x + x, center_y - y);
        SDL_RenderDrawLine(renderer, center_x - y, center_y + x, center_x + y, center_y + x);
        SDL_RenderDrawLine(renderer, center_x - y, center_y - x, center_x + y, center_y - x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }
        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

/**
 * @brief Functors encapsulate the shape rendering logic
 * 
 * Using functors allows us to easily add new shape types and test them individually.
 * This approach greatly accelerated development by enabling isolated testing of renderers.
 */

/**
 * @brief Renders a circular shape at the specified position
 *
 * @param renderer The SDL renderer used for drawing
 * @param pos_x The x coordinate of the circle's center
 * @param pos_y The y coordinate of the circle's center
 * @param size The diameter of the circle
 * @param color The color to fill the circle with
 */
void circle_renderer::operator()(SDL_Renderer *renderer, float pos_x, float pos_y, float size, SDL_Color color) const
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    DrawFilledCircle(renderer,
                     static_cast<int32_t>(pos_x),
                     static_cast<int32_t>(pos_y),
                     static_cast<int32_t>(size / 2.0f));
}

/**
 * @brief Renders a square shape at the specified position
 *
 * @param renderer The SDL renderer used for drawing
 * @param pos_x The x coordinate of the square's center
 * @param pos_y The y coordinate of the square's center
 * @param size The side length of the square
 * @param color The color to fill the square with
 */
void square_renderer::operator()(SDL_Renderer *renderer, float pos_x, float pos_y, float size, SDL_Color color) const
{
    SDL_Rect ball = {
        static_cast<int>(pos_x - size / 2.0f),
        static_cast<int>(pos_y - size / 2.0f),
        static_cast<int>(size),
        static_cast<int>(size)};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &ball);
}

/**
 * @brief Renders a triangle shape at the specified position
 *
 * Uses scan-line algorithm to fill the triangle efficiently.
 *
 * @param renderer The SDL renderer used for drawing
 * @param pos_x The x coordinate of the triangle's center
 * @param pos_y The y coordinate of the triangle's center
 * @param size The size of the triangle (height)
 * @param color The color to fill the triangle with
 */
void triangle_renderer::operator()(SDL_Renderer *renderer, float pos_x, float pos_y, float size, SDL_Color color) const
{
    SDL_Point points[3] = {
        {static_cast<int>(pos_x), static_cast<int>(pos_y - size / 2)},
        {static_cast<int>(pos_x - size / 2), static_cast<int>(pos_y + size / 2)},
        {static_cast<int>(pos_x + size / 2), static_cast<int>(pos_y + size / 2)}};

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    int min_y = points[0].y;
    int max_y = points[1].y;

    for (int y = min_y; y <= max_y; y++)
    {
        float alpha = static_cast<float>(y - min_y) / (max_y - min_y);
        int x1 = static_cast<int>(points[0].x + alpha * (points[1].x - points[0].x));
        int x2 = static_cast<int>(points[0].x + alpha * (points[2].x - points[0].x));
        SDL_RenderDrawLine(renderer, std::min(x1, x2), y, std::max(x1, x2), y);
    }
}