/**
 * @file macros.hpp
 * @brief Defines macros and constants used throughout the project
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#ifndef MACROS_HPP
#define MACROS_HPP

#include <string>

/**
 * @brief Window dimensions constants
 */
const int WINDOW_WIDTH = 800;   /**< Window width in pixels */
const int WINDOW_HEIGHT = 600;  /**< Window height in pixels */

/**
 * @brief Game name constant
 */
#define GAME_NAME "The NEW Pong"

/**
 * @brief Game mode constants
 */
#define AI_MODE 1               /**< AI player mode (single player) */
#define TWO_PLAYERS_MODE 2      /**< Two human players mode */
#define STORYTIME_MODE 3        /**< Story mode with words to collect */
#define FUN_MODE 4              /**< Fun mode with special features */
#define GAME_SAVED 5            /**< Game saved state flag */

/**
 * @brief Menu type constants
 */
#define BALL_TYPE_SELECTION 2   /**< Ball type selection menu */
#define AI_MODE_SELECTION 1     /**< AI difficulty selection menu */

/**
 * @brief AI difficulty level constants
 */
#define AI_MODE_EASY 0          /**< Easy AI difficulty (slower) */
#define AI_MODE_NORMAL 1        /**< Normal AI difficulty */
#define AI_MODE_HARD 2          /**< Hard AI difficulty (faster) */

/**
 * @brief Color constants
 */
const SDL_Color white = {255, 255, 255, 255};    /**< White color */
const SDL_Color black = {0, 0, 0, 255};          /**< Black color */
const SDL_Color yellow = {255, 255, 0, 255};     /**< Yellow color */
const SDL_Color orange = {255, 165, 0, 255};     /**< Orange color */
const SDL_Color red = {220, 20, 60, 255};        /**< Red color */
const SDL_Color green = {34, 139, 34, 255};      /**< Green color */
const SDL_Color blue = {0, 0, 255, 255};         /**< Blue color */
const SDL_Color purple = {128, 0, 128, 255};     /**< Purple color */

#endif