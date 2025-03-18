/**
 * @file user.hpp
 * @brief Header defining the User class for player management
 * @authors Vasileios Filippos Skarleas, Dounia Bakalem, Yanis Sadoun
 * @copyright All rights reserved.
 */

#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

/**
 * @class User
 * @brief Represents a player in the game with name and score tracking
 *
 * This class manages player information including their name, score,
 * and round tracking for story mode.
 */
class User
{
public:
    /**
     * @brief Constructor for User class
     * @param name The name of the user (defaults to "Player")
     */
    User(const std::string &name = "Player");

    /**
     * @brief Increments the user's score by 1
     */
    void increment_score();

    /**
     * @brief Resets the user's score to 0
     *
     * Used when the game is over or when a reset is needed
     */
    void reset_score();

    /**
     * @brief Gets the current score of the user
     * @return The user's current score
     */
    int get_user_score() const;

    /**
     * @brief Sets the user's score to a specific value
     * @param _score The new score to set
     */
    void set_user_score(int _score) { score = _score; };

    /**
     * @brief Gets the user's name
     * @return The user's name as a constant reference
     */
    const std::string &get_user_name() const; // It is a contstant since once it is set, it doesn't change afterward
    
    /**
     * @brief Sets the user's name
     * @param name The new name for the user
     */
    void set_user_name(const std::string &name);

    /**
     * @brief Sets the current round number
     * @param _round The round number to set
     */
    void set_round(int _round) { round = _round; }
    
    /**
     * @brief Gets the current round number
     * @return The current round number
     */
    int get_round() const { return round; }

private:
    std::string name;  /**< The user's name */
    int score;         /**< The user's current score */
    int round;         /**< The current round number (used for story mode) */
};

#endif