/**
 * @file game_save.cpp
 * @brief Implementation of save game functionality for Saving class
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#include <fstream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <SDL.h>

#include "game_save.hpp"

/**
 * @namespace
 * @brief Anonymous namespace for file-specific constants and utility functions
 *
 * Contains constants and helper functions for encoding and decoding save data.
 * These are kept private to this file for security purposes.
 */
namespace
{
    const unsigned char KEY = 0x83;                      /**< XOR encryption key */
    const char *SAVE_FILENAME = "game_pong-save_849374.txt";  /**< Save game file name */
    const char *HIGHSCCORE_FILENAME = "game_pong-highscore_849216.txt"; /**< High score file name */

    /**
     * @brief Encrypts/decrypts a single byte using XOR
     * 
     * Inspired from https://www.101computing.net/xor-encryption-algorithm/
     * Using XOR allows the same operation to both encrypt and decrypt
     * 
     * @param byte The byte to encode/decode
     * @return The encoded/decoded byte
     */
    unsigned char codec_byte(unsigned char byte)
    {
        return byte ^ KEY; // XOR operation
    }

    /**
     * @brief Encrypts/decrypts a float value
     * 
     * @param value The float value to encode/decode (modified in-place)
     */
    void codec_float(float &value)
    {
        unsigned char *bytes = reinterpret_cast<unsigned char *>(&value); // casting to return a float value to byte representation
        for (size_t i = 0; i < sizeof(float); ++i)
        {
            bytes[i] = codec_byte(bytes[i]);
        }
    }

    /**
     * @brief Encrypts/decrypts an integer value
     * 
     * @param value The integer value to encode/decode (modified in-place)
     */
    void codec_int(int &value)
    {
        unsigned char *bytes = reinterpret_cast<unsigned char *>(&value);
        for (size_t i = 0; i < sizeof(int); ++i)
        {
            bytes[i] = codec_byte(bytes[i]);
        }
    }

    /**
     * @brief Encrypts/decrypts a character string
     * 
     * @param str The string to encode/decode (modified in-place)
     * @param length The length of the string
     */
    void codec_string(char *str, size_t length)
    {
        for (size_t i = 0; i < length; ++i)
        {
            str[i] = codec_byte(str[i]);
        }
    }
}

/**
 * @brief Deletes the save game file
 */
void Saving::delete_save()
{
    std::remove(SAVE_FILENAME);
}

/**
 * @brief Deletes the high score file
 */
void Saving::delete_highscore()
{
    std::remove(HIGHSCCORE_FILENAME);
}

/**
 * @brief Saves the current high score to a file
 * 
 * Appends the high score to the file in binary format after encoding
 * 
 * @param score HighScore structure containing the score data to save
 * @return true if save was successful, false otherwise
 */
bool Saving::save_highscore(const HighScore &score)
{
    std::ofstream file(HIGHSCCORE_FILENAME, std::ios::binary | std::ios::app); // open the file in binary and append mode

    if (!file)
    {
        return false;
    }

    // Create a copy of the score to encode
    HighScore encode_score = score;

    // Encrypting the ints and floats of the HighScore structure
    codec_int(encode_score.score);
    codec_string(encode_score.name, 20);

    // Creating the file
    file.write(reinterpret_cast<const char *>(&encode_score), sizeof(HighScore));

    return file.good();
}

/**
 * @brief Saves the current game state to a file
 * 
 * Creates or overwrites the save file with the current game state in binary format after encoding
 * 
 * @param state SaveState structure containing the game state to save
 * @return true if save was successful, false otherwise
 */
bool Saving::save_game(const SaveState &state)
{
    std::ofstream file(SAVE_FILENAME, std::ios::binary);

    if (!file)
    {
        return false;
    }

    // Create a copy of the state to encode
    SaveState encode_state = state;

    // Encrypting the ints and floats of the SaveState structure
    codec_int(encode_state.score1);
    codec_int(encode_state.score2);
    codec_float(encode_state.paddle1_y);
    codec_float(encode_state.paddle2_y);
    codec_float(encode_state.ball_x);
    codec_float(encode_state.ball_y);
    codec_float(encode_state.ball_vel_x);
    codec_float(encode_state.ball_vel_y);
    codec_int(encode_state.ball_type);
    codec_string(encode_state.player1_name, 20);
    codec_string(encode_state.player2_name, 20);

    // Creating the file
    file.write(reinterpret_cast<const char *>(&encode_state), sizeof(SaveState));

    return file.good(); // returns true if write operation was successful
}

/**
 * @brief Loads a game state from file
 * 
 * Reads and decodes the saved game state from the save file
 * 
 * @param state SaveState structure to populate with the loaded data
 * @return true if load was successful, false otherwise
 */
bool Saving::load_game(SaveState &state)
{
    std::ifstream file(SAVE_FILENAME, std::ios::binary); // opening the file in binary mode

    // TEST 1 (file existence)
    if (!file) // if the file does not exist returns false
    {
        return false;
    }
    else
    {
        // Read encrypted content
        SaveState encode_state;
        file.read(reinterpret_cast<char *>(&encode_state), sizeof(SaveState));

        // TEST 2 (file reading rights)
        if (!file.good())
        {
            return false; // if the file is not readable returns false
        }

        // Decode all values
        codec_int(encode_state.score1);
        codec_int(encode_state.score2);
        codec_float(encode_state.paddle1_y);
        codec_float(encode_state.paddle2_y);
        codec_float(encode_state.ball_x);
        codec_float(encode_state.ball_y);
        codec_float(encode_state.ball_vel_x);
        codec_float(encode_state.ball_vel_y);
        codec_int(encode_state.ball_type);
        codec_string(encode_state.player1_name, 20);
        codec_string(encode_state.player2_name, 20);

        state = encode_state; // Copy decoded state back

        return true;
    }
}

/**
 * @brief Loads high score data from file
 * 
 * Reads and decodes the latest high score from the high score file
 * 
 * @param score HighScore structure to populate with the loaded data
 * @return true if load was successful, false otherwise
 */
bool Saving::load_highscore(HighScore &score)
{
    std::ifstream file(HIGHSCCORE_FILENAME, std::ios::binary);

    if (!file)
    {
        return false;
    }

    // Read the latest high score (at the end of file)
    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    if (fileSize < sizeof(HighScore))
    {
        return false;
    }
    // Move to the last record
    file.seekg(-static_cast<int>(sizeof(HighScore)), std::ios::end);

    HighScore encode_score;
    file.read(reinterpret_cast<char *>(&encode_score), sizeof(HighScore));

    if (!file.good())
    {
        return false;
    }

    codec_int(encode_score.score);
    codec_string(encode_score.name, 20);

    score = encode_score;

    SDL_Log("Loaded high score - Name: %s, Score: %d", score.name, score.score);
    return true;
}

/**
 * @brief Checks if a save file exists
 * 
 * @return true if a save file exists, false otherwise
 */
bool Saving::save_exists()
{
    std::ifstream file(SAVE_FILENAME);
    return file.good();
}

/**
 * @brief Checks if a high score file exists
 * 
 * @return true if a high score file exists, false otherwise
 */
bool Saving::highscore_exists()
{
    std::ifstream file(HIGHSCCORE_FILENAME);
    return file.good();
}