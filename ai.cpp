/**
 * @file ai.cpp
 * @brief Implementation of the AI class for computer-controlled paddle
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#include "ai.hpp"
#include "macros.hpp"

#include <cmath> // pour fabs si besoin

/**
 * @brief Constructor for AI class
 * 
 * Initializes the AI controller with a pointer to the paddle it will control
 * and sets default difficulty to normal
 * 
 * @param controlledPaddle Pointer to the paddle to be controlled by the AI
 */
AI::AI(Paddle* controlledPaddle)
    : racket(controlledPaddle),
      ai_difficulty(1) // Niveau normal par défaut
{
}

/**
 * @brief Sets the AI difficulty level
 * 
 * @param difficulty The difficulty level (0=easy, 1=normal, 2=hard)
 */
void AI::set_difficulty(int difficulty)
{
    ai_difficulty = difficulty;
}

/**
 * @brief Updates the AI-controlled paddle's position based on the ball
 * 
 * This method calculates where to move the paddle based on the ball's position
 * and the current difficulty setting. Higher difficulty makes the AI react faster.
 * 
 * @param ball Pointer to the ball to track
 * @param dt Time delta since last update (in seconds)
 */
void AI::updateAI(BallBase* ball, float dt)
{
    if (!racket || !ball)
        return; // sécurité

    // On récupère la position de la raquette et de la balle
    float paddleY = racket->get_pos_y();
    float ball_pos_y = ball->get_pos_y();
    float speed = racket->get_racket_speed(); // ex: 300

    // offset : pour ne pas être parfait
    float offset = 10.0f;

    /**
     * @brief Adjust reaction speed based on difficulty level
     * 
     * Easy: 60% speed - easier for player to win
     * Normal: 100% speed - balanced
     * Hard: 140% speed - more challenging for the player
     */
    float reactionFactor = 1.0f;
    switch (ai_difficulty)
    {
    case AI_MODE_EASY: // facile
        reactionFactor = 0.6f; // plus lent => plus simple de passer
        break;
    case AI_MODE_NORMAL: // normal
        reactionFactor = 1.0f;
        break;
    case AI_MODE_HARD: // difficile
        reactionFactor = 1.4f; // plus rapide => plus dur pour le joueur
        break;
    }

    /**
     * @brief Move the paddle based on ball position
     */
    // Si la balle est au-dessus de la raquette, on monte
    if (ball_pos_y < paddleY - offset)
    {
        racket->set_pos_y(paddleY - speed * reactionFactor * dt);
    }
    // Si la balle est en dessous, on descend
    else if (ball_pos_y > paddleY + offset)
    {
        racket->set_pos_y(paddleY + speed * reactionFactor * dt);
    }

    /**
     * @brief Keep the paddle within screen bounds
     */
    float halfH = racket->get_racket_height() / 2.0f;
    if (racket->get_pos_y() < halfH)
    {
        racket->set_pos_y(halfH);
    }
    else if (racket->get_pos_y() > (600.0f - halfH))
    {
        racket->set_pos_y(600.0f - halfH);
    }
}
