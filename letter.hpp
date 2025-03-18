/**
 * @file letter.hpp
 * @brief Header defining the Letter class for story mode
 * @authors Vasileios Filippos Skarleas, Dounia Bakalem, Yanis Sadoun
 * @copyright All rights reserved.
 */

#ifndef LETTER_HPP
#define LETTER_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <string>

#include "user.hpp"
#include "macros.hpp"

/**
 * @class Letter
 * @brief Represents a letter in the storytime game mode
 *
 * This class handles the display and interaction of letters that
 * move across the screen in the story mode. Players can collect
 * these letters by hitting them with the ball.
 */
class Letter
{
private:
    std::vector<std::string> words = {"Polytech", "Sorbonne", "2025"}; /**< Words to display letter by letter */
    std::vector<char> lettersAtBottom;      /**< Letters collected at the bottom of screen */
    std::string word;                       /**< Current word being displayed */
    int current_word_index;                 /**< Index of current word in the words array */
    int current_letter_index;               /**< Index of current letter in the current word */
    char letter;                            /**< Current letter being displayed */
    float x, y;                             /**< Position of the letter */
    float speed;                            /**< Movement speed of the letter */
    SDL_Texture *texture;                   /**< Texture for rendering the letter */
    int width, height;                      /**< Dimensions of the letter texture */
    SDL_Renderer *renderer;                 /**< SDL renderer reference */
    TTF_Font *font;                         /**< TTF font for rendering text */

public:
    /**
     * @brief Constructor for Letter class
     * @param index Initial index for word and letter selection
     * @param startX Starting X position
     * @param startY Starting Y position
     * @param velocity Movement speed
     * @param renderer SDL renderer to use
     * @param font TTF font to use
     */
    Letter(int index, float startX, float startY, float velocity, SDL_Renderer *renderer, TTF_Font *font);
    
    /**
     * @brief Destructor for Letter class
     */
    ~Letter();

    /**
     * @brief Updates the letter position and checks for collisions
     * @param time Time delta since last update
     * @param screen_height Window height for boundary checking
     * @param player1 Pointer to first player
     * @param player2 Pointer to second player
     * @param ball_pos_x Ball's X position
     * @param ball_pos_y Ball's Y position
     * @param ball_radius Ball's radius
     */
    void update_letter(float time, int screen_height, User *player1, User *player2, float ball_pos_x, float ball_pos_y, float ball_radius);
    
    /**
     * @brief Renders the letter on screen
     * @param renderer SDL renderer to use for drawing
     */
    void render(SDL_Renderer *renderer);
    
    /**
     * @brief Checks if the ball collides with the letter
     * @param ball_pos_x Ball's X position
     * @param ball_pos_y Ball's Y position
     * @param ball_radius Ball's radius
     * @return true if collision detected, false otherwise
     */
    bool collision_check(float ball_pos_x, float ball_pos_y, float ball_radius) const;
    
    /**
     * @brief Advances to the next letter in the current word
     */
    void next_letter();
    
    /**
     * @brief Advances to the next word in the words array
     */
    void next_word();
    
    /**
     * @brief Resets word and letter indices
     * @param n New index to set
     */
    void reset_word(int n);

    /**
     * @brief Gets the X position of the letter
     * @return Current X coordinate
     */
    float get_pos_x() const { return x; }
    
    /**
     * @brief Gets the Y position of the letter
     * @return Current Y coordinate
     */
    float get_pos_y() const { return y; }
};

#endif
