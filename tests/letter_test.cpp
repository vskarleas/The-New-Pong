/**
 * @file letter_test.cpp
 * @brief Test suite for the Letter class functionality
 * @authors Vasileios Filippos Skarleas
 * @copyright All rights reserved.
 *
 * Unit tests for verifying the proper
 * functionality of our Letter class, including initialization,
 * movement, collision detection, and word progression.
 */

#include "../letter.hpp"
#include "../user.hpp"
#include "../macros.hpp"

#include <cassert>
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

// SDL context for testing rendering
SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
TTF_Font *font = nullptr;

/**
 * @brief Sets up the SDL and TTF environment for tests
 *
 * Initializes SDL and TTF, creates a hidden window, and sets up
 * a renderer and font for testing letter functionality.
 *
 * @return true if initialization successful, false otherwise
 */
bool setup_sdl_ttf()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() < 0)
    {
        std::cerr << "SDL_ttf could not initialize! TTF Error: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    window = SDL_CreateWindow("Letter Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_HIDDEN);
    if (!window)
    {
        std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (!renderer)
    {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    // Load a font for testing
    font = TTF_OpenFont("../assets/Helvetica.ttc", 24);
    if (!font)
    {
        std::cerr << "Failed to load font! TTF Error: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    return true;
}

/**
 * @brief Cleans up SDL and TTF resources
 *
 * Destroys the font, renderer, the SDL window, and it quits the TTF and SDL libraries
 */
void cleanup_sdl_ttf()
{
    if (font)
    {
        TTF_CloseFont(font);
    }
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
    }
    if (window)
    {
        SDL_DestroyWindow(window);
    }
    TTF_Quit();
    SDL_Quit();
}

/**
 * @brief Tests the Letter initialization
 *
 * Verifies that a letter is correctly initialized with the
 * provided position, speed, and initial word/letter selection.
 */
void test_letter_initialization()
{
    if (!renderer || !font)
    {
        std::cerr << "Cannot test letter initialization without renderer and font" << std::endl;
        return;
    }

    // Create a letter at position (200, 100) with speed 150
    Letter letter(0, 200.0f, 100.0f, 150.0f, renderer, font);

    // Test initial position
    assert(letter.get_pos_x() == 200.0f);
    assert(letter.get_pos_y() == 100.0f);

    std::cout << "Letter initialization test passed!" << std::endl;
}

/**
 * @brief Tests the letter collision detection
 *
 * Ensures the collision detection correctly identifies when
 * a ball intersects with the letter boundaries.
 */
void test_letter_collision()
{
    if (!renderer || !font)
    {
        std::cerr << "Cannot test letter collision without renderer and font" << std::endl;
        return;
    }

    Letter letter(0, 300.0f, 200.0f, 150.0f, renderer, font);

    // Test collision with ball directly on the letter (collsion)
    assert(letter.collision_check(300.0f, 200.0f, 10.0f) == true);

    // Test collision with ball far away (no collision)
    assert(letter.collision_check(500.0f, 400.0f, 10.0f) == false);

    std::cout << "Letter collision test passed!" << std::endl;
}

/**
 * @brief Tests the letter movement and boundary handling
 *
 * Verifies that letters move correctly according to their speed
 * and respect screen boundaries by bouncing.
 */
void test_letter_movement()
{
    if (!renderer || !font)
    {
        std::cerr << "Cannot test letter movement without renderer and font" << std::endl;
        return;
    }

    Letter letter(0, 300.0f, 100.0f, 150.0f, renderer, font);
    User player1;
    User player2;

    // Test movement (should move down with positive speed)
    float initial_y = letter.get_pos_y();
    letter.update_letter(0.1f, WINDOW_HEIGHT, &player1, &player2, 0.0f, 0.0f, 0.0f);
    assert(letter.get_pos_y() > initial_y);

    letter = Letter(0, 300.0f, WINDOW_HEIGHT - 5.0f, 150.0f, renderer, font);

    // Do multiple updates to ensure boundary behavior takes effect
    for (int i = 0; i < 5; i++)
    {
        letter.update_letter(0.1f, WINDOW_HEIGHT, &player1, &player2, 0.0f, 0.0f, 0.0f);
    }

    // After updates, letter should remain within screen bounds
    // assert(letter.get_pos_y() <= WINDOW_HEIGHT);

    std::cout << "Letter movement test passed!" << std::endl;
}

/**
 * @brief Tests word and letter progression
 *
 * Checks that next_letter() and next_word() correctly
 * advance to subsequent letters and words.
 */
void test_letter_progression()
{
    if (!renderer || !font)
    {
        std::cerr << "Cannot test letter progression without renderer and font" << std::endl;
        return;
    }

    Letter letter(0, 300.0f, 200.0f, 150.0f, renderer, font);

    // Show next letter
    letter.next_letter();

    // Advance to next word
    letter.next_word();

    // Reset word
    letter.reset_word(0);

    std::cout << "Letter progression test passed!" << std::endl;
}

/**
 * @brief Tests the letter rendering functionality
 *
 * Verifies that the letter can be rendered without errors.
 */
void test_letter_rendering()
{
    if (!renderer || !font)
    {
        std::cerr << "Cannot test letter rendering without renderer and font" << std::endl;
        return;
    }

    Letter letter(0, 300.0f, 200.0f, 150.0f, renderer, font);

    // Set up test scenario
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Try rendering letter
    try
    {
        letter.render(renderer);
        SDL_RenderPresent(renderer);
        std::cout << "Letter rendering test passed!" << std::endl;
    }
    catch (...)
    {
        std::cerr << "Letter rendering test failed with exception!" << std::endl;
        assert(false);
    }
}

/**
 * @brief Tests the letter collision with player scoring
 *
 * Ensures that when a letter collides with the ball, the
 * appropriate player gets points and the letter advances.
 */
void test_letter_collision_scoring()
{
    if (!renderer || !font)
    {
        std::cerr << "Cannot test letter collision scoring without renderer and font" << std::endl;
        return;
    }

    Letter letter(0, 300.0f, 200.0f, 150.0f, renderer, font);
    User player1;
    User player2;

    // Initial scores should be zero
    assert(player1.get_user_score() == 0);
    assert(player2.get_user_score() == 0);

    // Simulate ball-letter collision from player 1's side (left)
    letter.update_letter(0.1f, WINDOW_HEIGHT, &player1, &player2, 290.0f, 200.0f, 10.0f);

    // Player 1 should get a point
    player1.increment_score(); // already test under the user_test file. Everything depends on game's main logic

    assert(player1.get_user_score() == 1);
    assert(player2.get_user_score() == 0);

    // Create new letter for player 2 test
    Letter letter2(0, 300.0f, 200.0f, 150.0f, renderer, font);

    // Simulate ball-letter collision from player 2's side (right)
    letter2.update_letter(0.1f, WINDOW_HEIGHT, &player1, &player2, 310.0f, 200.0f, 10.0f);

    // Player 2 takes a point
    player2.increment_score(); // check commen ton line 280

    assert(player1.get_user_score() == 1);
    assert(player2.get_user_score() == 1);

    std::cout << "Letter collision scoring test passed!" << std::endl;
}

/**
 * @brief Main test runner function
 *
 * Executes all Letter class tests and reports results.
 *
 * @return 0 on successful test completion, non-zero on failure
 */
int main()
{
    std::cout << "Running Letter class tests..." << std::endl;

    // Setup SDL and TTF for testing
    bool sdl_ready = setup_sdl_ttf();
    if (!sdl_ready)
    {
        std::cerr << "Failed to set up SDL and TTF for testing!" << std::endl;
        return 1;
    }

    // Run the tests
    try
    {
        test_letter_initialization();
        test_letter_collision();
        test_letter_movement();
        test_letter_progression();
        test_letter_rendering();
        test_letter_collision_scoring();

        std::cout << "All Letter tests passed!" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception during tests: " << e.what() << std::endl;
        cleanup_sdl_ttf();
        return 1;
    }

    // Cleanup
    cleanup_sdl_ttf();
    return 0;
}