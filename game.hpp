// #############################################################################
// # File game.hpp
// # Project in C++ - Polytech Sorbonne - 2024/2025 - S8
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem - All rights reserved.
// #############################################################################

#ifndef GAME_HPP
#define GAME_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "paddle.hpp"
#include "ball_base.hpp"

#include "page_3b.hpp"
#include "page_3b_0t.hpp"
#include "page_3b_1t.hpp"
#include "page_4b_1t.hpp"
#include "page_2b_1t.hpp"

#include "game_over.hpp"

#include "ai.hpp"
#include "user.hpp"
#include "network.hpp"

#include "power.hpp"
#include "invisible_power.hpp"
#include "inverse_power.hpp"

#include "gui.hpp"
#include "letter.hpp"

enum class game_state
{
    Notice_Menu,
    Menu,
    Middle_menu,
    Choose_Mode, // this is used as our main menu where players can choose what they want to do
    AI_playing,
    Remote_playing,
    Fun_playing,
    Storytime_playing,
    Playing, // playing classic with two players (first implementation with high score [the goal])
    Paused,
    GameOver,
    Set_up
};

class Game
{
public:
    Game();
    ~Game();
    bool initialise();
    void loop();
    void close();

    static Mix_Chunk *racket_hit_sound;
    static Mix_Chunk *mWallHitSound;
    static Mix_Chunk *mScoreSound;

private:
    void game_logic();
    void game();
    void output();
    void ball_creation(int type);
    void update_background_color();

    // SDL objects for the game window and renderer
    SDL_Window *mWindow;
    SDL_Renderer *renderer;

    // Game loop variable allowing to control either if we stay on the modes loop or not
    bool mIsRunning;

    // This is used to track the time since the last frame was drawn
    /* We need that to calculate velocities and position */
    Uint32 mTicksCount;

    // Every game needs two paddles and one ball as expected
    Paddle *racket1;
    Paddle *racket2;
    BallBase *mBall;

    AI *mAI; // the AI player

    // The scores of the two players
    // int mScore1;
    // int mScore2;

    // The font used on the whole game
    TTF_Font *police;

    // Adding the different page structures on the app
    page_2b_1t *mNoticeMenu;
    page_3b_0t *mMenu;
    page_3b *mPauseMenu;
    page_3b_1t *mMiddleMenu;
    page_4b_1t *mModeMenu;

    // Network game
    NetworkManager *network; // NOT USED YET
    bool is_network_game;

    GameOver *mGameOver; // This is used when the game is over

    // This allows us to control on which state we are and make the appropriate UI and action decisons
    game_state mGameState;

    // For the background music
    Mix_Music *mBackgroundMusic;
    Mix_Chunk *mNewRoundSound;
    Mix_Chunk *mGameOverSound;
    Mix_Music *mPauseMusic;
    Mix_Music *mOnHoldMusic;

    // Background color for the two sides
    SDL_Color background_color_left;
    SDL_Color background_color_right;

    // The pause button object declared here
    SDL_Rect mPauseButtonRect;
    bool pause_button();

    User *player1;
    User *player2;
    std::string winner; // To store winner's name

    int last_highscore;
    char last_highscore_name[20]; // To store the name of the last high score player

    Letter *mletter;
    Power *mpower;
    InvisiblePower *minvisible;
    InversiblePower *minverse;
};

#endif