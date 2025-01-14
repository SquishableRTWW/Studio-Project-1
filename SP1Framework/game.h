#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"

extern CStopWatch g_swTimer;
extern bool g_bQuitGame;

// struct to store keyboard events
// a small subset of KEY_EVENT_RECORD
struct SKeyEvent
{
    bool keyDown;
    bool keyReleased;
};

// struct to store mouse events
// a small subset of MOUSE_EVENT_RECORD
struct SMouseEvent
{
    COORD mousePosition;
    DWORD buttonState;
    DWORD eventFlags;
};

// Enumeration to store the control keys that your game will have
enum EKEYS
{
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
    K_Q,
    K_F,
    K_ENTER,
    K_COUNT
};

// Enumeration for the different screen states
enum EGAMESTATES
{
    S_SPLASHSCREEN,
    S_ENCOUNTERSPLASHSCREEN,
    S_ENCOUNTER,
    S_ENCOUNTERBOSS,
    S_BOSSSPLASHSCREEN,
    S_MENU,
    S_GAME,
    S_ROUTE2,
    S_ROUTE3,
    S_BOSSROUTE,
    S_INTERACT,
    S_TUTORIAL,
    S_STARTER,
    S_GAMEOVER,
    S_COUNT
};

enum Entities//enumeration to store the types of entities
{
    E_Hunter,
    E_Healer,
    E_NPC,
    E_Boss,
    E_NULL
};

// struct for the game character
struct SGameChar
{
    COORD m_cLocation;
    bool  m_bActive;
};

void init        ( void );      // initialize your variables, allocate memory, etc
void getInput    ( void );      // get input from player
void update      ( double dt ); // update the game and the state of the game
void render      ( void );      // renders the current state of the game to the console
void shutdown    ( void );      // do clean up, free memory

void splashScreenWait();    // waits for time to pass in splash screen
void updateGame();          // gameplay logic
void updateEncounter();     // combat logic
void menuScreenWait();      // menu screen logic
void tutorialWait();        // tutorial screen logic.
void starterScreenWait();   // starter screen game logic
void interactionWait();     // interaction screen logic
void bossSplashscreenWait();//Boss splash screen logic.
void gameOverWait();

void moveCharacter();       // moves the character, collision detection, physics, etc
void collision();           // collision check for buildings and npc
void detection();           // detection check for hunters
void moveSelection();       // checks which moves the user selects
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch 

void renderSplashScreen();  // renders the splash screen
void renderGame();          // renders the game stuff
void renderGame2();         // renders the route 2 stuff.
void renderGame3();         // renders the route 3 stuff.
void renderBossRoute();     // renders boss route to the buffer.
void renderGameOver();      //renders game over stuff
void renderInteract();      //renders the interaction onto the map.
void renderMap();           // renders the map to the buffer first
void renderRoute2();        // renders route 2 map to the buffer.
void renderRoute3();        // renders route 3 map to the buffer.
void renderBossMap();       // renders the boss route
void renderMenu();          // renders the pause menu screen.
void renderTutorial();      // renders the tutorial screen.
void renderStarterScreen(); // renders the screen for user to pick starter ele-beast.
void renderInstructions();  // renders the instruction on screen for users to know
void renderGameOverScreen();// renders the game over screen.

void renderCharacter();     // renders the character into the buffer
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game
void renderInputEvents();   // renders the status of input events
void encounterScreenWait(); // set timer for the encounter splash screen
void renderEncounterSplashScreen();     // renders the encounter splash screen
void renderEncounter();     // renders the encounter screen
void renderEncounterBoss(); // renders the encounter boss screen
void renderBossSS();        // renders boss splash screen

// keyboard and mouse input event managers
void keyboardHandler(const KEY_EVENT_RECORD& keyboardEvent);  // define this function for the console to call when there are keyboard events
void mouseHandler(const MOUSE_EVENT_RECORD& mouseEvent);      // define this function for the console to call when there are mouse events

void gameplayKBHandler(const KEY_EVENT_RECORD& keyboardEvent);   // handles keyboard events for gameplay
void gameplayMouseHandler(const MOUSE_EVENT_RECORD& mouseEvent); // handles mouse events for gameplay 


#endif  _GAME_H