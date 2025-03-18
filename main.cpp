/**
 * @file main.cpp
 * @brief Main entry point for the Pong game
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#include "game.hpp"

/**
 * @brief Main function that initializes and runs the game
 * 
 * Creates a game object and runs the game's loop until termination
 * 
 * @param argc Number of command line arguments
 * @param argv Array of command line argument strings
 * @return int Program exit code
 */
int main(int argc, char *argv[])
{
    Game game;

    if (game.initialise())
    {
        game.loop();
    }

    game.close();
    return 0;
}