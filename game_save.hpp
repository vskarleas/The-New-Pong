/**
 * @file game_save.hpp
 * @brief Header defining the save game and highscore functionaloty from the Saving class
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#ifndef GAME_SAVE_HPP
#define GAME_SAVE_HPP

#include <string>

/**
 * @struct SaveState
 * @brief Structure representing the complete game state for saving/loading
 *
 * Contains all data required to reconstruct the state of a game session
 * when loading a saved game.
 */
struct SaveState
{
    int score1;            /**< Player 1's score */
    int score2;            /**< Player 2's score */
    float paddle1_y;       /**< Position of paddle 1 (only y-coordinate since x is fixed) */
    float paddle2_y;       /**< Position of paddle 2 (only y-coordinate since x is fixed) */
    float ball_x;          /**< Ball's x position */
    float ball_y;          /**< Ball's y position */
    float ball_vel_x;      /**< Ball's x velocity */
    float ball_vel_y;      /**< Ball's y velocity */
    int ball_type;         /**< Ball type (0=classic, 1=square, 2=triangle) */

    char player1_name[20]; /**< Player 1's name */
    char player2_name[20]; /**< Player 2's name */
};

/**
 * @struct HighScore
 * @brief Structure representing a high score record
 *
 * Contains the player's score and name for high score recording
 */
struct HighScore
{
    int score;             /**< Player's score */
    char name[20];         /**< Player's name */
};

/**
 * @class Saving
 * @brief Utility class for managing save game and high score functionality
 *
 * This class handles saving and loading game states and high scores,
 * including file operations and data encoding/decoding.
 */
class Saving
{
public:
    /**
     * @brief Deletes the save game file
     */
    static void delete_save();

    /**
     * @brief Deletes the high score file
     */
    static void delete_highscore();

    /**
     * @brief Saves the current game state to a file
     * @param state SaveState structure containing the game state to save
     * @return true if save was successful, false otherwise
     */
    static bool save_game(const SaveState &state);

    /**
     * @brief Loads a game state from file
     * @param state SaveState structure to populate with the loaded data
     * @return true if load was successful, false otherwise
     */
    static bool load_game(SaveState &state);

    /**
     * @brief Checks if a save file exists
     * @return true if a save file exists, false otherwise
     */
    static bool save_exists();

    /**
     * @brief Saves a high score to a file
     * @param score HighScore structure containing the score data to save
     * @return true if save was successful, false otherwise
     */
    static bool save_highscore(const HighScore &score);

    /**
     * @brief Loads high score data from file
     * @param score HighScore structure to populate with the loaded data
     * @return true if load was successful, false otherwise
     */
    static bool load_highscore(HighScore &score);

    /**
     * @brief Checks if a high score file exists
     * @return true if a high score file exists, false otherwise
     */
    static bool highscore_exists();
};

#endif