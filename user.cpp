/**
 * @file user.cpp
 * @brief Implementation of the User class for player management
 * @authors Vasileios Filippos Skarleas, Dounia Bakalem, Yanis Sadoun
 * @copyright All rights reserved.
 */

#include "user.hpp"

/**
 * @brief Constructor for User class
 * 
 * Initializes a user with the given name and sets score and round to 0
 * 
 * @param name The name of the user
 */
User::User(const std::string &name) : name(name), score(0), round(0) {}

/**
 * @brief Increments the user's score by 1
 * 
 * Called when the user wins a round or scores a point
 */
void User::increment_score()
{
    score++;
}

/**
 * @brief Resets the user's score to 0
 * 
 * Used when the game is over or when a score reset is needed
 */
void User::reset_score()
{
    score = 0;
}

/**
 * @brief Gets the current score of the user
 * 
 * @return int The user's current score
 */
int User::get_user_score() const
{
    return score;
}

/**
 * @brief Gets the user's name
 * 
 * @return const std::string& The user's name as a constant reference
 */
const std::string &User::get_user_name() const
{
    return name;
}

/**
 * @brief Sets the user's name
 * 
 * @param newName The new name for the user
 */
void User::set_user_name(const std::string &newName)
{
    name = newName;
}