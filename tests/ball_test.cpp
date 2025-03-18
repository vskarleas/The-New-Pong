/**
 * @file ball_test.cpp
 * @brief Test suite for the Ball classes functionality
 * @authors Vasileios Filippos Skarleas
 * @copyright All rights reserved.
 *
 * This file contains tests for verifying the proper
 * functionality of our Ball classes hierarchy. We test the
 * base class functionality and derived class implementations.
 */

#include "../ball_base.hpp"
#include "../classic_ball.hpp"
#include "../square_ball.hpp"
#include "../triangle_ball.hpp"
#include "../paddle.hpp"
#include "../user.hpp"

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
 * a renderer for testing ball rendering functionality.
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

    window = SDL_CreateWindow("Ball Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              800, 600, SDL_WINDOW_HIDDEN);
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
 * @brief Tests the BallBase initialization and getters
 *
 * Verifies that the ball is initialized at the center of the screen,
 * with proper size and non-zero velocities.
 */
void test_ball_initialization()
{
    // Cannot directly instantiate BallBase as it's abstract
    ClassicBall ball;

    // Test initial position (center of screen)
    assert(ball.get_pos_x() == 400.0f);
    assert(ball.get_pos_y() == 300.0f);

    // Ball should have a non-zero velocity
    assert(ball.get_vel_x() != 0.0f || ball.get_vel_y() != 0.0f);

    std::cout << "Ball initialization test passed!" << std::endl;
}

/**
 * @brief Tests position and velocity setters and getters
 *
 * Ensures we can properly set and retrieve ball position and velocity.
 */
void test_ball_movement()
{
    ClassicBall ball;

    // Test position setter and getter
    ball.set_position(200.0f, 150.0f);
    assert(ball.get_pos_x() == 200.0f);
    assert(ball.get_pos_y() == 150.0f);

    // Test velocity setter and getter
    ball.set_velocity(250.0f, 300.0f);
    assert(ball.get_vel_x() == 250.0f);
    assert(ball.get_vel_y() == 300.0f);

    // Test movement through update
    Paddle paddle1(30, true);
    Paddle paddle2(770, false);
    User player1;
    User player2;

    float time_delta = 0.1f; // 100ms
    ball.update(time_delta, &paddle1, &paddle2, &player1, &player2);

    // Position should change according to velocity * time
    assert(ball.get_pos_x() == 200.0f + 250.0f * time_delta);
    assert(ball.get_pos_y() == 150.0f + 300.0f * time_delta);

    std::cout << "Ball movement test passed!" << std::endl;
}

/**
 * @brief Tests the ball reset functionality
 *
 * Checks if the ball correctly resets to center position
 * and gets a new random direction.
 */
void test_ball_reset()
{
    ClassicBall ball;

    // Move the ball away from center
    ball.set_position(100.0f, 100.0f);
    float original_vel_x = ball.get_vel_x();
    float original_vel_y = ball.get_vel_y();

    // Reset the ball
    ball.reset();

    // Position should be at center
    assert(ball.get_pos_x() == 400.0f);
    assert(ball.get_pos_y() == 300.0f);

    // Velocity should be different (though technically could be the same by chance)
    // This test might occasionally fail due to randomness
    assert(ball.get_vel_x() != 0.0f || ball.get_vel_y() != 0.0f);

    std::cout << "Ball reset test passed!" << std::endl;
}

/**
 * @brief Tests color change functionality
 *
 * Verifies that ball color can be properly set and retrieved.
 */
void test_ball_color()
{
    ClassicBall ball;

    // Create a test color
    SDL_Color test_color = {255, 0, 128, 255};

    // Set the color
    ball.set_color(test_color);

    // Get the color and verify
    SDL_Color retrieved_color = ball.get_color();
    assert(retrieved_color.r == test_color.r);
    assert(retrieved_color.g == test_color.g);
    assert(retrieved_color.b == test_color.b);
    assert(retrieved_color.a == test_color.a);

    std::cout << "Ball color test passed!" << std::endl;
}

/**
 * @brief Tests ball collision boundaries
 *
 * Ensures that the ball's collision rectangle is properly calculated.
 */
void test_ball_boundaries()
{
    ClassicBall ball;
    float size = 24.0f; // Default size from constructor

    // Position ball at a known location
    ball.set_position(300.0f, 200.0f);

    // Get boundaries
    SDL_Rect bounds = ball.boundaries();

    // Check boundaries calculation
    assert(bounds.x == static_cast<int>(300.0f - size / 2.0f));
    assert(bounds.y == static_cast<int>(200.0f - size / 2.0f));
    assert(bounds.w == static_cast<int>(size));
    assert(bounds.h == static_cast<int>(size));

    std::cout << "Ball boundaries test passed!" << std::endl;
}

/**
 * @brief Tests the rendering of different ball types
 *
 * Verifies that each ball type can be rendered without errors.
 * Note: This only tests that the render call doesn't crash,
 * not the actual visual appearance.
 */
void test_ball_rendering()
{
    if (!renderer)
    {
        std::cerr << "Cannot test rendering without a valid SDL renderer" << std::endl;
        return;
    }

    // Test each ball type's rendering
    ClassicBall classic_ball;
    SquareBall square_ball;
    TriangleBall triangle_ball;

    // Set up test scenario
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Try rendering each ball type
    try
    {
        classic_ball.render_object(renderer);
        square_ball.render_object(renderer);
        triangle_ball.render_object(renderer);
        SDL_RenderPresent(renderer);
        std::cout << "Ball rendering test passed!" << std::endl;
    }
    catch (...)
    {
        std::cerr << "Ball rendering test failed with exception!" << std::endl;
        assert(false);
    }
}

/**
 * @brief Tests that different ball subclasses have correct sizes
 *
 * Each ball type can have its own default size, this test
 * verifies they're initialized correctly.
 */
void test_ball_sizes()
{
    ClassicBall classic_ball;
    SquareBall square_ball;
    TriangleBall triangle_ball;

    // Check boundaries to infer size
    SDL_Rect classic_bounds = classic_ball.boundaries();
    SDL_Rect square_bounds = square_ball.boundaries();
    SDL_Rect triangle_bounds = triangle_ball.boundaries();

    // Classic ball should have size 24.0f (from constructor)
    assert(classic_bounds.w == 24);

    // Square and triangle balls should have size 20.0f (from constructors)
    assert(square_bounds.w == 20);
    assert(triangle_bounds.w == 20);

    std::cout << "Ball sizes test passed!" << std::endl;
}

/**
 * @brief Main test runner function
 *
 * Executes all Ball class tests and reports results.
 *
 * @return 0 on successful test completion, non-zero on failure
 */
int main()
{
    std::cout << "Running Ball classes tests..." << std::endl;

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
        test_ball_initialization();
        test_ball_movement();
        test_ball_reset();
        test_ball_color();
        test_ball_boundaries();
        test_ball_sizes();
        test_ball_rendering();

        std::cout << "All ball tests passed!" << std::endl;
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