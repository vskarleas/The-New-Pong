/**
 * @file page_2b_1t.cpp
 * @brief Implementation of the notice screen page_2b_1t class
 * @authors Yanis Sadoun, Vasileios Filippos Skarleas, Dounia Bakalem
 * @copyright All rights reserved.
 */

#include "page_2b_1t.hpp"
#include "renderers.hpp"
#include "macros.hpp"
#include "game.hpp"

/**
 * @brief Constructor for the notice page
 * 
 * Initializes the notice screen with navigation buttons
 * 
 * @param _renderer The SDL renderer to use for drawing
 * @param font The TTF font to use for text display
 */
page_2b_1t::page_2b_1t(SDL_Renderer *_renderer, TTF_Font *font) : 
    texture_menu(nullptr),
    renderer(_renderer),
    police(font),
    next_view(false),
    go_back(false), //be default we don't go back on the modes menu
    notice_id(-1) //be default we display the general notice
{
    const int button_width = 200;
    const int button_height = 50;
    const int base_y = WINDOW_WIDTH - 400;
    const int center_x = WINDOW_HEIGHT / 2;

    // "Go back" button above "Let's go" button
    button_back = SDL_Rect{center_x, base_y, button_width, button_height};
    button_lets_go = SDL_Rect{center_x, base_y + 70, button_width, button_height};
}

/**
 * @brief Destructor for the notice page
 * 
 * Cleans up allocated resources
 */
page_2b_1t::~page_2b_1t()
{
    if (texture_menu)
    {
        SDL_DestroyTexture(texture_menu);
        texture_menu = nullptr;
    }
}

/**
 * @brief Handles events for the notice screen buttons
 * 
 * Processes SDL events to detect button clicks
 * 
 * @param event The SDL event to process
 * @return true if a button was clicked, false otherwise
 */
bool page_2b_1t::action_handler(const SDL_Event &event)
{
    next_view = false;

    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        SDL_Point point = {event.button.x, event.button.y};

        if (SDL_PointInRect(&point, &button_lets_go))
        {
            Mix_PlayChannel(-1, Game::racket_hit_sound, 0);
            next_view = true;
            return true;
        }

        if (SDL_PointInRect(&point, &button_back))
        {
            Mix_PlayChannel(-1, Game::racket_hit_sound, 0);
            go_back = true;
            return true;
        }
    }

    return false;
}

/**
 * @brief Renders the notice screen
 * 
 * Displays different notice text based on the current notice_id
 * and renders the navigation buttons
 */
void page_2b_1t::render_object()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Add notice text
    TTF_SetFontStyle(police, TTF_STYLE_NORMAL);
    TTF_SetFontSize(police, 14);

    const char* notice_text[20]; // Define a fixed size array
    int text_size = 0; // To keep track of array size

    /**
     * @brief Select notice text based on notice_id 
     * 
     * Different game modes have different instructions that are displayed
     * based on the currently selected notice_id
     */
    switch(notice_id) // a great way to add more notices without creatign new files for the same fuctionality
    {
        case TWO_PLAYERS_MODE:
            notice_text[0] = "Default Pong Game instructions";
            notice_text[1] = "";
            notice_text[2] = "Player 1 Controls:";
            notice_text[3] = "- Use W/S to move paddle up/down";
            notice_text[4] = "";
            notice_text[5] = "Player 2 Controls:";
            notice_text[6] = "- Use UP/DOWN ARROW to move paddle up/down";
            notice_text[7] = "";
            notice_text[8] = "Other Controls:";
            notice_text[9] = "- Press Pause to see the inner game menu";
            notice_text[10] = "- Click the Save button to save your game in progress";
            notice_text[11] = "";
            notice_text[12] = "THE GOAL IS TO ACHIEVE THE GRETEST SCORE POSSIBLE !";
            notice_text[13] = "WHO IS GOIG TO BYPASS THE PREVIOYS HIGHSCORE ? ";
            text_size = 14;
            break;

        case AI_MODE:
            notice_text[0] = "AI Mode Instructions";
            notice_text[1] = "";
            notice_text[2] = "In this mode, you'll play against the computer!";
            notice_text[3] = "";
            notice_text[4] = "Controls:";
            notice_text[5] = "- Use W/S keys to move your paddle";
            notice_text[6] = "- The AI will control the other paddle";
            notice_text[7] = "";
            notice_text[8] = "Wins the players that reaches 10 points first!";
            text_size = 9;
            break;

        case STORYTIME_MODE:
            notice_text[0] = "Story Mode Instructions";
            notice_text[1] = "";
            notice_text[2] = "Hit the letters to see the story!";
            notice_text[3] = "Every letter is an extra point for you.";
            notice_text[4] = "";
            notice_text[5] = "Wins the player that reaches 8 points first!";
            notice_text[6] = "The game is completed at 3 rounds";
            text_size = 7;
            break;

        case FUN_MODE:
            notice_text[0] = "Fun Mode Instructions";
            notice_text[1] = "";
            notice_text[2] = "There are power cubes that change the rules of the game !";
            notice_text[3] = "The ball may disappear, the paddle may increase, who know ?";
            notice_text[4] = "";
            notice_text[5] = "Controls:";
            notice_text[6] = "- Use W/S keys to move your paddle on the left";
            notice_text[7] = "- Use UP/DOWN ARROW keys to move your paddle on the right";
            notice_text[8] = "";
            notice_text[9] = "Wins the player that reaches 5 points first on the round!";
            notice_text[10] = "The game is completed after 3 rounds. The player with the most rounds wins!";
            text_size = 11;
            break;
        case GAME_SAVED:
            notice_text[0] = "Game has been saved! succesfully !";
            notice_text[1] = "";
            notice_text[2] = "Please note that you can Continue the game only when you are on the Classic Pong Game mode";
            text_size = 3;
            break;

        case -1:
            notice_text[0] = "Welcome to the Pong Game!";
            notice_text[1] = "";
            notice_text[2] = "This game was developed using the SDL library and OOP principles.";
            notice_text[3] = "It was developed with inheritance, polymorphisms, lamda functions and functors in mind.";
            notice_text[4] = "";
            notice_text[5] = "There are four game modes available. Each mode has its own set of instructions for you to discover.";
            notice_text[6] = "";
            notice_text[7] = "Let's go and select a mode to start playing!";
            notice_text[8] = "";
            notice_text[9] = "Informatory:";
            TTF_SetFontStyle(police, TTF_STYLE_BOLD);
            notice_text[10] = "The game comes with its integrated UI, but in order to set up the players names";
            notice_text[11] = "you need to use the terminal, so keep an eye open for that!";
            TTF_SetFontStyle(police, TTF_STYLE_NORMAL); 
            text_size = 12;
            break;


        default:
            notice_text[0] = "Invalid mode selected";
            text_size = 1;
            break;
    }
    

    int y_position = 100;
    for (int i = 0; i < text_size; i++)
    {
        SDL_Rect text_rect = {WINDOW_WIDTH / 4, y_position, 400, 18};
        Utilities::render_button(renderer, police, notice_text[i], text_rect, black);
        y_position += 20;
    }

    // Render Let's Go button
    TTF_SetFontSize(police, 24);
    TTF_SetFontStyle(police, TTF_STYLE_BOLD);
    Utilities::render_button(renderer, police,"Alright", button_lets_go, black);

    // if (!(notice_id != -1 || notice_id == GAME_SAVED)) // hide the go back button if we are in the game saved notice
    // {
    //     TTF_SetFontStyle(police, TTF_STYLE_NORMAL);
    //     Utilities::render_button(renderer, police,"Go back", button_back, text_color);
    // }

    if (notice_id != -1 && notice_id != GAME_SAVED) // show the go back button only if we are not in the general notice
    {
        TTF_SetFontStyle(police, TTF_STYLE_NORMAL);
        Utilities::render_button(renderer, police,"Go back", button_back, black);
    }

    SDL_RenderPresent(renderer);
}