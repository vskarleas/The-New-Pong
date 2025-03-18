/**
 * @file ai.hpp
 * @brief Header defining the AI class for computer-controlled paddle
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#ifndef AI_HPP
#define AI_HPP

#include "paddle.hpp"
#include "ball_base.hpp"

/**
 * @class AI
 * @brief Artificial Intelligence for controlling a paddle
 *
 * This class manages computer-controlled paddles, providing different
 * difficulty levels to adjust how well the AI tracks and responds to the ball.
 */
class AI
{
public:
    /**
     * @brief Constructor for AI class
     * @param controlledPaddle Pointer to the paddle that will be controlled by the AI
     */
    AI(Paddle* controlledPaddle);

    /**
     * @brief Updates the AI-controlled paddle's position
     * 
     * Called each frame in AI mode to move the paddle to attempt to hit the ball
     * based on the current difficulty setting
     * 
     * @param ball Pointer to the ball to track
     * @param dt Time delta since last update (in seconds)
     */
    void updateAI(BallBase* ball, float dt);

    /**
     * @brief Sets the AI difficulty level
     * 
     * @param difficulty The difficulty level (0=easy, 1=normal, 2=hard)
     */
    void set_difficulty(int difficulty);

private:
    Paddle* racket;     /**< Pointer to the paddle controlled by the AI */
    int ai_difficulty;    /**< Current difficulty level (0=easy, 1=normal, 2=hard) */
};

#endif