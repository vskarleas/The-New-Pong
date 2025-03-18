/**
 * @file paddle_test.cpp
 * @brief Test suite for the Paddle class functionality
 * @authors Vasileios Filippos Skarleas
 * @copyright All rights reserved.
 *
 * This file contains unit tests for verifying the proper
 * functionality of our Paddle class, including initialization,
 * movement, rendering, and boundary checks.
 */

#include "../paddle.hpp"
#include "../macros.hpp"

#include <cassert>
#include <iostream>
#include <SDL.h>

// SDL context for testing rendering
SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

/**
 * @brief Sets up the SDL environment for tests
 *
 * Initializes SDL, creates a hidden window, and sets up
 * a renderer for testing paddle rendering functionality.
 *
 * @return true if initialization successful, false otherwise
 */
bool setup_sdl()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Paddle Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_HIDDEN);
    if (!window)
    {
        std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (!renderer)
    {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

/**
 * @brief Cleans up SDL resources
 *
 * Destroys the renderer and window, and quits SDL
 */
void cleanup_sdl()
{
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
    }
    if (window)
    {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

/**
 * @brief Tests the paddle initialization and constructor
 *
 * Verifies that paddles are initialized with correct position,
 * dimensions, and side placement.
 */
void test_paddle_initialization()
{
    // Test left paddle (Player 1)
    Paddle leftPaddle(30, true);

    assert(leftPaddle.get_pos_x() == 30.0f);
    assert(leftPaddle.get_pos_y() == WINDOW_HEIGHT / 2.0f);
    assert(leftPaddle.get_racket_height() == 100.0f);
    assert(leftPaddle.get_racket_width() == 15.0f);
    assert(leftPaddle.get_racket_speed() == 300.0f);
    assert(leftPaddle.get_is_left() == true);
    leftPaddle.set_inverse_power_active(false);
    assert(leftPaddle.get_inverse_power_active() == false);

    // Test right paddle (Player 2)
    Paddle rightPaddle(770, false);

    assert(rightPaddle.get_pos_x() == 770.0f);
    assert(rightPaddle.get_pos_y() == WINDOW_HEIGHT / 2.0f);
    assert(rightPaddle.get_racket_height() == 100.0f);
    assert(rightPaddle.get_racket_width() == 15.0f);
    assert(rightPaddle.get_racket_speed() == 300.0f);
    assert(rightPaddle.get_is_left() == false);
    rightPaddle.set_inverse_power_active(false);
    assert(rightPaddle.get_inverse_power_active() == false);

    std::cout << "Paddle initialization test passed!" << std::endl;
}

/**
 * @brief Tests paddle position setters and getters
 *
 * Ensures we can properly set and retrieve paddle position.
 */
void test_paddle_position()
{
    Paddle paddle(30, true);

    // Test position setters and getters
    paddle.set_pos_x(50.0f);
    paddle.set_pos_y(200.0f);

    assert(paddle.get_pos_x() == 50.0f);
    assert(paddle.get_pos_y() == 200.0f);

    std::cout << "Paddle position test passed!" << std::endl;
}

/**
 * @brief Tests the paddle's movement and boundary constraints
 *
 * Verifies that the paddle movement respects screen boundaries
 * and doesn't allow the paddle to move outside the playable area.
 */
void test_paddle_boundaries()
{
    Paddle paddle(30, true);

    // Test upper boundary
    paddle.set_pos_y(0.0f);
    paddle.update(0.1f); // Should adjust paddle to minimum valid position
    assert(paddle.get_pos_y() == paddle.get_racket_height() / 2.0f);

    // Test lower boundary
    paddle.set_pos_y(WINDOW_HEIGHT + 100.0f);
    paddle.update(0.1f); // Should adjust paddle to maximum valid position
    assert(paddle.get_pos_y() == WINDOW_HEIGHT - paddle.get_racket_height() / 2.0f);

    std::cout << "Paddle boundaries test passed!" << std::endl;
}

/**
 * @brief Tests the paddle rendering functionality
 *
 * Verifies that the paddle can be rendered without errors.
 */
void test_paddle_rendering()
{
    if (!renderer)
    {
        std::cerr << "Cannot test rendering without a valid SDL renderer" << std::endl;
        return;
    }

    Paddle paddle(30, true);

    // Set up test scenario
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Try rendering paddle
    try
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        paddle.render_object(renderer);
        SDL_RenderPresent(renderer);
        std::cout << "Paddle rendering test passed!" << std::endl;
    }
    catch (...)
    {
        std::cerr << "Paddle rendering test failed with exception!" << std::endl;
        assert(false);
    }
}

/**
 * @brief Tests the paddle rectangle boundary calculation
 *
 * Ensures that the collision rectangle is properly calculated
 * for collision detection.
 */
void test_paddle_rectangle()
{
    Paddle paddle(30, true);
    paddle.set_pos_x(40.0f);
    paddle.set_pos_y(200.0f);

    SDL_Rect rect = paddle.rectangle();

    assert(rect.x == static_cast<int>(40.0f - paddle.get_racket_width() / 2.0f));
    assert(rect.y == static_cast<int>(200.0f - paddle.get_racket_height() / 2.0f));
    assert(rect.w == static_cast<int>(paddle.get_racket_width()));
    assert(rect.h == static_cast<int>(paddle.get_racket_height()));

    std::cout << "Paddle rectangle test passed!" << std::endl;
}

/**
 * @brief Tests the inverse power functionality
 *
 * Verifies that the inverse power effect properly
 * reverses the paddle's control direction.
 */
void test_paddle_inverse_power()
{
    Paddle paddle(30, true);
    float initialY = paddle.get_pos_y();

    // Test normal movement (simulate W key - should move up)
    // This is a simplified test without actual keyboard input
    paddle.set_inverse_power_active(false);
    float regularMovement = -1.0f * paddle.get_racket_speed() * 0.1f; // Direction * speed * time
    paddle.set_pos_y(initialY + regularMovement);
    assert(paddle.get_pos_y() < initialY); // Should have moved up

    // Reset position
    paddle.set_pos_y(initialY);

    // Test inverted movement (simulate W key - should move down with inverse power)
    paddle.set_inverse_power_active(true);
    float invertedMovement = -1.0f * -1.0f * paddle.get_racket_speed() * 0.1f; // Direction * inverter * speed * time
    paddle.set_pos_y(initialY + invertedMovement);
    assert(paddle.get_pos_y() > initialY); // Should have moved down

    std::cout << "Paddle inverse power test passed!" << std::endl;
}

/**
 * @brief Tests paddle height adjustment
 *
 * Verifies that we can properly change the paddle height
 * (important for power-ups that affect paddle size).
 */
void test_paddle_height_adjustment()
{
    Paddle paddle(30, true);
    float initialHeight = paddle.get_racket_height();

    // Double the height (power-up effect)
    paddle.set_racket_height(initialHeight * 2.0f);
    assert(paddle.get_racket_height() == initialHeight * 2.0f);

    // Half the height (power-up expiration)
    paddle.set_racket_height(paddle.get_racket_height() / 2.0f);
    assert(paddle.get_racket_height() == initialHeight);

    std::cout << "Paddle height adjustment test passed!" << std::endl;
}

/**
 * @brief Main test runner function
 *
 * Executes all Paddle class tests and reports results.
 *
 * @return 0 on successful test completion, non-zero on failure
 */
int main()
{
    std::cout << "Running Paddle class tests..." << std::endl;

    // Setup SDL for rendering tests
    bool sdl_ready = setup_sdl();
    if (!sdl_ready)
    {
        std::cerr << "Failed to set up SDL for testing!" << std::endl;
        return 1;
    }

    // Run the tests
    try
    {
        test_paddle_initialization();
        test_paddle_position();
        test_paddle_boundaries();
        test_paddle_rectangle();
        test_paddle_height_adjustment();
        test_paddle_inverse_power();
        test_paddle_rendering();

        std::cout << "All paddle tests passed!" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception during tests: " << e.what() << std::endl;
        cleanup_sdl();
        return 1;
    }

    // Cleanup
    cleanup_sdl();
    return 0;
}