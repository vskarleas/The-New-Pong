/**
 * @file letter.cpp
 * @brief Implementation of the Letter class
 * @authors Dounia Bakalem, Vasileios Filippos Skarleas, Yanis Sadoun
 * @copyright All rights reserved.
 */

#include "letter.hpp"
#include "macros.hpp"

#include <SDL_image.h>
#include <vector>

/**
 * @brief Constructor for Letter class
 * 
 * Initializes a letter with position, speed, and selects the initial word and letter
 * 
 * @param index Initial index for word and letter selection
 * @param startX Starting X position
 * @param startY Starting Y position
 * @param velocity Movement speed
 * @param renderer SDL renderer to use
 * @param font TTF font to use
 */
Letter::Letter(int index, float startX, float startY, float velocity, SDL_Renderer *renderer, TTF_Font *font)
    : current_word_index(index), current_letter_index(index), x(startX), y(startY), speed(velocity), texture(nullptr),
      width(0), height(0), renderer(renderer), font(font)
{
    word = words[current_word_index];
    next_letter();
}

/**
 * @brief Resets word and letter indices
 * 
 * @param n New index to set
 */
void Letter::reset_word(int n)
{
    current_letter_index = n;
    current_word_index = n;
}

/**
 * @brief Destructor for Letter class
 * 
 * Cleans up the texture resource
 */
Letter::~Letter()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }
}

/**
 * @brief Advances to the next letter in the current word
 * 
 * Creates a new texture for the next letter or moves to next word if needed
 */
void Letter::next_letter()
{
    // Check if there's a next letter
    if (current_letter_index < word.length())
    {
        letter = word[current_letter_index];
        current_letter_index++;

        // Supprimer l'ancienne texture
        if (texture)
        {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }

        // Créer une nouvelle texture pour la lettre actuelle
        std::string letter_string(1, letter);
        SDL_Surface *surface = TTF_RenderText_Solid(font, letter_string.c_str(), white);

        if (surface)
        {
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            width = surface->w;
            height = surface->h;
            SDL_FreeSurface(surface);
        }
        else
        {
            SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
        }
    }
}

void Letter::update_letter(float time, int screen_height, User *player1, User *player2,
                           float ball_pos_x, float ball_pos_y, float ball_radius)
{
    // Letters mouvement
    y += speed * time;

    // Check if letter reaches the limits
    if (y + height >= screen_height || y <= 0)
    {
        speed = -speed;
    }

    if (collision_check(ball_pos_x, ball_pos_y, ball_radius)) // Check collision with ball
    {

        // Which player should take extra point ?
        if (ball_pos_x < x + width / 2)
        {
            player1->increment_score();
        }
        else
        {
            player2->increment_score();
        }
        lettersAtBottom.push_back(letter);

        // Check if it is the last letter of the word
        if (current_letter_index >= word.length())
        {
            lettersAtBottom.clear();
            next_word();
        }
        else
        {
            next_letter();
        }

        // Reset letter position
        y = 0;
        speed = abs(speed);
    }
}

/* Showing thhe letters on the screen afetr they have been touched from the ball */
void Letter::render(SDL_Renderer *renderer)
{
    if (texture)
    {
        SDL_Rect rectangle = {static_cast<int>(x), static_cast<int>(y), width * 3, height * 3};
        SDL_RenderCopy(renderer, texture, nullptr, &rectangle);
    }

    // Posiotining on the bottom of the screen
    int pos_x = 150;
    int pos_y = WINDOW_HEIGHT - 100;
    int spacing = width * 3 + 10;

    for (size_t i = 0; i < lettersAtBottom.size(); ++i)
    {
        std::string letter_string(1, lettersAtBottom[i]);
        SDL_Surface *surface = TTF_RenderText_Solid(font, letter_string.c_str(), orange);

        if (surface)
        {
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_Rect letterRect = {pos_x + static_cast<int>(i) * spacing, pos_y, width * 4, height * 4};
            SDL_RenderCopy(renderer, texture, nullptr, &letterRect);

            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }
    }
}

void Letter::next_word()
{
    current_word_index = (current_word_index + 1) % words.size(); // Going to the next word
    word = words[current_word_index];
    current_letter_index = 0;
    next_letter();
}

// VCollision verification with a ball object
bool Letter::collision_check(float ball_pos_x, float ball_pos_y, float ball_radius) const
{
    // Vérifier si le centre de la balle est dans la zone de la lettre
    float closestX = (ball_pos_x < x) ? x : (ball_pos_x > x + width * 3) ? x + width * 3
                                                               : ball_pos_x;
    float closestY = (ball_pos_y < y) ? y : (ball_pos_y > y + height * 3) ? y + height * 3
                                                                : ball_pos_y;

    float distanceX = ball_pos_x - closestX;
    float distanceY = ball_pos_y - closestY;

    return (distanceX * distanceX + distanceY * distanceY) < (ball_radius * ball_radius);
}
