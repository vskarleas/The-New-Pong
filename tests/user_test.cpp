/**
 * @file user_test.cpp
 * @brief Test suite for the User class functionality
 * @authors Vasileios Filippos Skarleas
 * @copyright All rights reserved.
 *
 * Ttests for verifying the proper functionality of our User class. 
 * We are testing the constructor, score management, name operations, 
 * and round incrementation.
 */

#include "../user.hpp"

#include <cassert>
#include <iostream>

/**
 * @brief Tests the User class constructors
 *
 * Makes sure both the default and parameterized constructors
 * initialize the values correctly. The default constructor should
 * set "Player" as the name, while the named constructor should
 * use the provided name. Both should initialize score and rounds to 0.
 */
void test_constructor()
{
    // Test default constructor
    User defaultUser;
    assert(defaultUser.get_user_name() == "Player");
    assert(defaultUser.get_user_score() == 0);
    assert(defaultUser.get_round() == 0);
    std::cout << "Default constructor test passed!" << std::endl;

    // Test constructor with name
    User namedUser("TestUser");
    assert(namedUser.get_user_name() == "TestUser");
    assert(namedUser.get_user_score() == 0);
    assert(namedUser.get_round() == 0);
    std::cout << "Named constructor test passed!" << std::endl;
}

/**
 * @brief Tests score manipulation operations
 *
 * Verifies that we can properly increment scores, directly
 * set score values, and reset scores back to zero. This covers
 * the core gameplay functionality needed for tracking player points.
 */
void test_score_operations()
{
    User user;

    // Test initial score
    assert(user.get_user_score() == 0);

    // Test increment
    user.increment_score();
    assert(user.get_user_score() == 1);

    user.increment_score();
    user.increment_score();
    assert(user.get_user_score() == 3);

    // Test set_user_score
    user.set_user_score(10);
    assert(user.get_user_score() == 10);

    // Test reset
    user.reset_score();
    assert(user.get_user_score() == 0);

    std::cout << "Score operations tests passed!" << std::endl;
}

/**
 * @brief Tests user name operations
 *
 * Checks if we can properly get and change player names.
 * Names are important for the multiplayer experience and
 * for displaying high scores in our game.
 */
void test_name_operations()
{
    User user("Initial");

    // Test get_user_name
    assert(user.get_user_name() == "Initial");

    // Test set_user_name
    user.set_user_name("Changed");
    assert(user.get_user_name() == "Changed");

    std::cout << "Name operations tests passed!" << std::endl;
}

/**
 * @brief Tests round tracking functionality
 *
 * Validates that the round counter can be properly
 * set and retrieved. This is essential for tracking
 * game progress and managing multi-round matches.
 */
void test_round_operations()
{
    User user;

    // Test initial round
    assert(user.get_round() == 0);

    // Test set_round
    user.set_round(3);
    assert(user.get_round() == 3);

    std::cout << "Round operations tests passed!" << std::endl;
}

/**
 * @brief Main test runner function
 *
 * Executes all User class tests and reports results.
 * If all tests pass without assertion failures, we can
 * be confident that the User class works as expected.
 *
 * @return 0 on successful test completion
 */
int main()
{
    std::cout << "Running User class tests..." << std::endl;

    test_constructor();
    test_score_operations();
    test_name_operations();
    test_round_operations();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}