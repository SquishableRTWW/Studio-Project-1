// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdlib.h>
#include "hunter.h"
#include "monster.h"
#include "atax.h"
#include "smeltor.h"
#include "NPC.h"
#include "Entity.h"

double  g_dElapsedTime;
double  g_dDeltaTime;
bool isCaught;
bool failedCatch;
bool isHunter;
bool warn;
int location;
int location2;
int boss;
int moveDecision;
int effective;
hunter jeff;
hunter Enemy[8];
monster wild, Null;
monster mon1, mon2, mon3, mon4, mon5, mon6;
NPC Advice[4];
NPC Nurse;
SKeyEvent g_skKeyEvent[K_COUNT + 2];
SMouseEvent g_mouseEvent;

// Game specific variables here
SGameChar   g_sChar;
EGAMESTATES g_eGameState = S_SPLASHSCREEN; // initial state
Entities Type = E_NULL;

// Console object
Console g_Console(80, 25, "SP1 Framework");

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init( void )
{
    srand((unsigned)time(0)); boss = 1;
    isCaught = false; failedCatch = false; moveDecision = 0; isHunter = false; effective = 2;
    float hpBarP = mon1.getHealth() / mon1.getMaxHealth(); float hpBarW = wild.getHealth() / wild.getMaxHealth();
    location = 1;
    // Set precision for floating point output
    g_dElapsedTime = 0.0;
    jeff.choosestarter(1);
    // sets the initial state for the game (which is the start screen).
    g_eGameState = S_SPLASHSCREEN;
    g_sChar.m_cLocation.X = 25;
    g_sChar.m_cLocation.Y = 8;
    g_sChar.m_bActive = true;
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");

    // remember to set your keyboard handler, so that your functions can be notified of input events
    g_Console.setKeyboardHandler(keyboardHandler);
    g_Console.setMouseHandler(mouseHandler);
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown( void )
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Get all the console input events
//            This function sets up the keyboard and mouse input from the console.
//            We will need to reset all the keyboard status, because no events will be sent if no keys are pressed.
//
//            Remember to set the handlers for keyboard and mouse events.
//            The function prototype of the handler is a function that takes in a const reference to the event struct
//            and returns nothing. 
//            void pfKeyboardHandler(const KEY_EVENT_RECORD&);
//            void pfMouseHandlerconst MOUSE_EVENT_RECORD&);
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput( void )
{
    // resets all the keyboard events
    memset(g_skKeyEvent, 0, K_COUNT * sizeof(*g_skKeyEvent));
    // then call the console to detect input from user
    g_Console.readConsoleInput();    
}

//--------------------------------------------------------------
// Purpose  : This is the handler for the keyboard input. Whenever there is a keyboard event, this function will be called.
//            Ideally, you should pass the key event to a specific function to handle the event.
//            This is because in some states, some keys would be disabled. Hence, to reduce your code complexity, 
//            it would be wise to split your keyboard input handlers separately.
//            
//            The KEY_EVENT_RECORD struct has more attributes that you can use, if you are adventurous enough.
//
//            In this case, we are not handling any keyboard event in the Splashscreen state
//            
// Input    : const KEY_EVENT_RECORD& keyboardEvent - reference to a key event struct
// Output   : void
//--------------------------------------------------------------
void keyboardHandler(const KEY_EVENT_RECORD& keyboardEvent)
{    
    switch (g_eGameState)
    {
    case S_SPLASHSCREEN: gameplayKBHandler(keyboardEvent);// handle gameplay keyboard event.
        break;
    case S_GAME: gameplayKBHandler(keyboardEvent); // handle gameplay keyboard event 
        break;
    case S_MENU: gameplayKBHandler(keyboardEvent); // handle gameplay keyboard event
        break;
    case S_ENCOUNTER: gameplayKBHandler(keyboardEvent);
        break;
    case S_TUTORIAL:gameplayKBHandler(keyboardEvent);
        break;
    case S_STARTER: gameplayKBHandler(keyboardEvent);
        break;
    case S_ROUTE2: gameplayKBHandler(keyboardEvent);
        break;
    case S_ROUTE3: gameplayKBHandler(keyboardEvent);
        break;
    case S_BOSSROUTE: gameplayKBHandler(keyboardEvent);
    }
}

//--------------------------------------------------------------
// Purpose  : This is the handler for the mouse input. Whenever there is a mouse event, this function will be called.
//            Ideally, you should pass the key event to a specific function to handle the event.
//            This is because in some states, some keys would be disabled. Hence, to reduce your code complexity, 
//            it would be wise to split your keyboard input handlers separately.
//            
//            For the mouse event, if the mouse is not moved, no event will be sent, hence you should not reset the mouse status.
//            However, if the mouse goes out of the window, you would not be able to know either. 
//
//            The MOUSE_EVENT_RECORD struct has more attributes that you can use, if you are adventurous enough.
//
//            In this case, we are not handling any mouse event in the Splashscreen state
//            
// Input    : const MOUSE_EVENT_RECORD& mouseEvent - reference to a mouse event struct
// Output   : void
//--------------------------------------------------------------
void mouseHandler(const MOUSE_EVENT_RECORD& mouseEvent)
{    
    switch (g_eGameState)
    {
    case S_SPLASHSCREEN: // don't handle anything for the splash screen
        break;
    case S_GAME: gameplayMouseHandler(mouseEvent); // handle gameplay mouse event
        break;
    case S_ENCOUNTER: gameplayMouseHandler(mouseEvent);
        break;
    case S_STARTER: gameplayMouseHandler(mouseEvent);
        break;
    case S_ENCOUNTERBOSS: gameplayMouseHandler(mouseEvent);
        break;
    }
    
}

//--------------------------------------------------------------
// Purpose  : This is the keyboard handler in the game state. Whenever there is a keyboard event in the game state, this function will be called.
//            
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : const KEY_EVENT_RECORD& keyboardEvent
// Output   : void
//--------------------------------------------------------------
void gameplayKBHandler(const KEY_EVENT_RECORD& keyboardEvent)
{
    // here, we map the key to our enums
    EKEYS key = K_COUNT;
    switch (keyboardEvent.wVirtualKeyCode)
    {
    case 0x57: key = K_UP; break;
    case 0x53: key = K_DOWN; break;
    case 0x41: key = K_LEFT; break; 
    case 0x44: key = K_RIGHT; break; 
    case VK_RETURN: key = K_ENTER; break;
    case 0x51: key = K_Q; break;
    case 0x46: key = K_F; break;
    case VK_ESCAPE: key = K_ESCAPE; break; 
    }
    // a key pressed event would be one with bKeyDown == true
    // a key released event would be one with bKeyDown == false
    // if no key is pressed, no event would be fired.
    // so we are tracking if a key is either pressed, or released
    if (key != K_COUNT)
    {
        g_skKeyEvent[key].keyDown = keyboardEvent.bKeyDown;
        g_skKeyEvent[key].keyReleased = !keyboardEvent.bKeyDown;
    }    
}

//--------------------------------------------------------------
// Purpose  : This is the mouse handler in the game state. Whenever there is a mouse event in the game state, this function will be called.
//            
//            If mouse clicks are detected, the corresponding bit for that mouse button will be set.
//            mouse wheel, 
//            
// Input    : const KEY_EVENT_RECORD& keyboardEvent
// Output   : void
//--------------------------------------------------------------
void gameplayMouseHandler(const MOUSE_EVENT_RECORD& mouseEvent)
{
    if (mouseEvent.dwEventFlags & MOUSE_MOVED) // update the mouse position if there are no events
    {
        g_mouseEvent.mousePosition = mouseEvent.dwMousePosition;
    }
    g_mouseEvent.buttonState = mouseEvent.dwButtonState;
    g_mouseEvent.eventFlags = mouseEvent.dwEventFlags;
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
    // get the delta time
    g_dElapsedTime += dt;
    g_dDeltaTime = dt;

    switch (g_eGameState)
    {
        case S_SPLASHSCREEN : splashScreenWait(); // game logic for the splash screen
            break;
        case S_GAME: updateGame(); // gameplay logic when we are in the game
            break;
        case S_MENU: menuScreenWait(); //game logic for menu screen
            break;
        case S_ENCOUNTERSPLASHSCREEN: wild.setWildMonster(wild, (rand() % 4) + 1); 
            if (isHunter == true)
            {
                wild.setLevel(9); 
                for (int i = 0; i < 3; i++)
                {
                    wild.setMove(wild, i);
                }
            }
            for (int i = 0; i < 2; i++)
            {
                wild.setMove(wild, i);
            } 
            encounterScreenWait();
            break;
        case S_ENCOUNTER: updateEncounter();
            break;
        case S_TUTORIAL: tutorialWait();
            break;
        case S_STARTER: starterScreenWait();
            break;
        case S_ROUTE2: updateGame();
            break;
        case S_ROUTE3: updateGame();
            break;
        case S_BOSSROUTE: updateGame();
            break;
        case S_INTERACT: interactionWait();
            break;
        case S_BOSSSPLASHSCREEN:
            if (boss == 1)
            {
                wild.setWildMonster(wild, 5);
                for (int i = 0; i < 4; i++)
                {
                    wild.setMove(wild, i);
                }
            }
            if (boss == 2)
            {
                wild.setWildMonster(wild, 6);
                for (int i = 0; i < 4; i++)
                {
                    wild.setMove(wild, i);
                }
            }
            bossSplashscreenWait();
            break;
        case S_ENCOUNTERBOSS:
            updateEncounter();
            break;
        case S_GAMEOVER:
            gameOverWait();
            break;
    }
}


void splashScreenWait()    // waits for user input in splash screen
{
    processUserInput();
    if (g_skKeyEvent[K_ENTER].keyReleased) // wait for user to press 'Enter' to go on to game screen.
        g_eGameState = S_TUTORIAL;
    if (g_skKeyEvent[K_F].keyReleased)
        g_eGameState = S_SPLASHSCREEN;
}

void encounterScreenWait()
{
    Sleep(2000);
    g_eGameState = S_ENCOUNTER;
}



void updateGame()       // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
                        // sound can be played here too.
}

void menuScreenWait()
{
    if (g_skKeyEvent[K_F].keyReleased)
        switch (location)
        {
        case 1: g_eGameState = S_GAME;
            break;
        case 2: g_eGameState = S_ROUTE2;
            break;
        case 3: g_eGameState = S_ROUTE3;
            break;
        case 4: g_eGameState = S_BOSSROUTE;
            break;
        }
    if (g_skKeyEvent[K_ESCAPE].keyReleased)
        g_bQuitGame = true;
}

void tutorialWait()
{
    if (g_skKeyEvent[K_ENTER].keyReleased) // wait for user to press 'Enter' to go on to game screen.
        g_eGameState = S_STARTER;
}

void starterScreenWait()
{
    if ((g_mouseEvent.mousePosition.X > 21 && g_mouseEvent.mousePosition.X < 33 && g_mouseEvent.mousePosition.Y == 12) && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
    {
        mon1.chooseStarter(mon1, 1);
        g_eGameState = S_GAME;
    }
    if ((g_mouseEvent.mousePosition.X > 36 && g_mouseEvent.mousePosition.X < 50 && g_mouseEvent.mousePosition.Y == 12) && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
    {
        mon1.chooseStarter(mon1, 2);
        g_eGameState = S_GAME;
    }
    if ((g_mouseEvent.mousePosition.X > 53 && g_mouseEvent.mousePosition.X < 69 && g_mouseEvent.mousePosition.Y == 12) && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
    {
        mon1.chooseStarter(mon1, 3);
        g_eGameState = S_GAME;
    }
}

void interactionWait()
{
    Sleep(2000);
    switch (location)
    {
    case 1: g_eGameState = S_GAME;
        break;
    case 2: g_eGameState = S_ROUTE2;
        break;
    case 3: g_eGameState = S_ROUTE3;
        break;
    case 4: g_eGameState = S_BOSSROUTE;
        break;
    }
}

void bossSplashscreenWait()
{
    Sleep(2000);
    g_eGameState = S_ENCOUNTERBOSS;
}

void gameOverWait()
{
    Sleep(2000);
    g_bQuitGame = true;
}


void updateEncounter()
{

    if ((g_mouseEvent.mousePosition.X > 67 && g_mouseEvent.mousePosition.X < 71 && g_mouseEvent.mousePosition.Y == 20) && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED && isHunter == false)
    {
        switch (location)
        {
        case 1: g_eGameState = S_GAME;
            break;
        case 2: g_eGameState = S_ROUTE2;
            break;
        case 3: g_eGameState = S_ROUTE3;
            break;
        }
    }
    if ((g_mouseEvent.mousePosition.X > 55 && g_mouseEvent.mousePosition.X < 61 && g_mouseEvent.mousePosition.Y == 20) && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
    {
        COORD c;
        c.X = 1; c.Y = 24;
        int yourDMG = mon1.getMoveDamage(0) * (mon1.getAttack() / wild.getDefence()) * 0.5;
        int wildDMG = wild.getMoveDamage(0) * ((wild.getAttack() / mon1.getDefence()) * 0.5);
        int caught = (rand() % 5) + 0;
        if (caught == 0)
        {
            if (mon2.getName() == "NULL")
            {
                mon2 = wild;
            }
            else if (mon2.getName() != "NULL" && mon3.getName() == "NULL" && mon4.getName() == "NULL" && mon5.getName() == "NULL" && mon6.getName() == "NULL")
            {
                mon3 = wild;
            }
            else if (mon3.getName() != "NULL" && mon4.getName() == "NULL" && mon5.getName() == "NULL" && mon6.getName() == "NULL")
            {
                mon4 = wild;
            }
            else if (mon4.getName() != "NULL" && mon5.getName() != "NULL" && mon6.getName() == "NULL")
            {
                mon5 = wild;
            }
            else if (mon5.getName() != "NULL" && mon2.getName() != "NULL" && mon3.getName() != "NULL" && mon4.getName() != "NULL" && mon5.getName() != "NULL")
            {
                mon6 = wild;
            }
            isCaught = true;
            switch (location)
            {
            case 1: g_eGameState = S_GAME;
                break;
            case 2: g_eGameState = S_ROUTE2;
                break;
            case 3: g_eGameState = S_ROUTE3;
                break;
            }
            isCaught = false;
        }
        else
        {
            mon1.setHealth(-wildDMG);
            if (mon1.getHealth() <= 0)
            {
                if (mon2.getName() == "NULL" && mon3.getName() == "NULL" && mon4.getName() == "NULL" && mon5.getName() == "NULL" && mon6.getName() == "NULL")
                {
                    g_eGameState = S_GAMEOVER;
                }
                else
                {
                    mon1 = mon2;
                    mon2 = mon3; mon3 = mon4; mon4 = mon5; mon5 = mon6; mon6 = Null;
                }
            }
        }
    }
    if ((mon1.getElement() == "fire" && wild.getElement() == "water") && (mon1.getElement() == "water" && wild.getElement() == "nature") &&
        (mon1.getElement() == "fire" && wild.getElement() == "earth") && (mon1.getElement() == "earth" && wild.getElement() == "water") && (mon1.getElement() == "earth" && wild.getElement() == "nature"))
    {
        effective = 1;
    }
    else if ((mon1.getElement() == "fire" && wild.getElement() == "nature") && (mon1.getElement() == "water" && wild.getElement() == "earth") && 
        (mon1.getElement() == "earth" && wild.getElement() == "fire") && (mon1.getElement() == "nature" && wild.getElement() == "water") && (mon1.getElement() == "water" && wild.getElement() == "water"))
    {
        effective = 3;
    }
    else
    {
        effective = 2;
    }
    //First skill
    if ((g_mouseEvent.mousePosition.X > 9 && g_mouseEvent.mousePosition.X < 17 && g_mouseEvent.mousePosition.Y == 19) && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
    {
        moveDecision = 0;
        int yourDMG = mon1.getMoveDamage(moveDecision) * (mon1.getAttack() / wild.getDefence() * 0.25 * effective);
        int wildDMG = wild.getMoveDamage(moveDecision) * ((wild.getAttack() / mon1.getDefence()) * 0.25 * effective);
        if (wild.getSpeed() >= mon1.getSpeed())
        {
            mon1.setHealth(-wildDMG);
            if (mon1.getHealth() <= 0)
            {
                if (mon2.getName() == "NULL" && mon3.getName() == "NULL" && mon4.getName() == "NULL" && mon5.getName() == "NULL" && mon6.getName() == "NULL")
                {
                    g_eGameState = S_GAMEOVER;
                }
                else
                {
                    mon1 = mon2;
                    mon2 = mon3; mon3 = mon4; mon4 = mon5; mon5 = mon6; mon6 = Null;
                }
            }
            wild.setHealth(-yourDMG);
            if (wild.getHealth() <= 0)
            {
                mon1.levelUp(mon1);
                switch (location)
                {
                case 1: g_eGameState = S_GAME;
                    break;
                case 2: g_eGameState = S_ROUTE2;
                    break;
                case 3: g_eGameState = S_ROUTE3;
                    break;
                case 4: g_eGameState = S_BOSSROUTE; g_sChar.m_cLocation.Y = 17;
                    break;
                }
                if (wild.getName() == "atax")
                {
                    boss++;
                }
                if (wild.getName() == "smeltor")
                {
                    g_eGameState = S_GAMEOVER;
                }
                isHunter = false;
            }
        }
        else
        {
            wild.setHealth(-yourDMG);
            if (wild.getHealth() <= 0)
            {
                mon1.levelUp(mon1);
                if (g_eGameState == S_ENCOUNTERBOSS)
                {
                    g_eGameState = S_BOSSROUTE;
                }
                switch (location)
                {
                case 1: g_eGameState = S_GAME;
                    break;
                case 2: g_eGameState = S_ROUTE2;
                    break;
                case 3: g_eGameState = S_ROUTE3;
                    break;
                case 4: g_eGameState = S_BOSSROUTE; g_sChar.m_cLocation.Y = 17;
                    break;
                }
                if (wild.getName() == "atax")
                {
                    boss++;
                }
                if (wild.getName() == "smeltor")
                {
                    g_eGameState = S_GAMEOVER;
                }
                isHunter = false;
            }
            mon1.setHealth(-wildDMG);
            if (mon1.getHealth() <= 0)
            {
                if (mon2.getName() == "NULL" && mon3.getName() == "NULL" && mon4.getName() == "NULL" && mon5.getName() == "NULL" && mon6.getName() == "NULL")
                {
                    g_eGameState = S_GAMEOVER;
                }

            }
        }
    }
    //Second skill
    if ((g_mouseEvent.mousePosition.X > 26 && g_mouseEvent.mousePosition.X < 34 && g_mouseEvent.mousePosition.Y == 19) && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
    {
        moveDecision = 1;
        int yourDMG = mon1.getMoveDamage(moveDecision) * (mon1.getAttack() / wild.getDefence()) * 0.5;
        int wildDMG = wild.getMoveDamage(moveDecision) * ((wild.getAttack() / mon1.getDefence()) * 0.5);
        if (wild.getSpeed() >= mon1.getSpeed())
        {
            mon1.setAttack(1);
            if (mon1.getHealth() <= 0)
            {
                if (mon2.getName() == "NULL" && mon3.getName() == "NULL" && mon4.getName() == "NULL" && mon5.getName() == "NULL" && mon6.getName() == "NULL")
                {
                    g_eGameState = S_GAMEOVER;
                }

            }
            wild.setAttack(1);
            if (wild.getHealth() <= 0)
            {
                mon1.levelUp(mon1);
                if (g_eGameState == S_ENCOUNTERBOSS)
                {
                    g_eGameState = S_BOSSROUTE;
                }
                switch (location)
                {
                case 1: g_eGameState = S_GAME;
                    break;
                case 2: g_eGameState = S_ROUTE2;
                    break;
                case 3: g_eGameState = S_ROUTE3;
                    break;
                case 4: g_eGameState = S_BOSSROUTE; g_sChar.m_cLocation.Y = 17;
                    break;
                }
                if (wild.getName() == "atax")
                {
                    boss++;
                }
                if (wild.getName() == "smeltor")
                {
                    g_eGameState = S_GAMEOVER;
                }
                isHunter = false;
            }
        }
        else
        {
            wild.setAttack(1);
            if (wild.getHealth() <= 0)
            {
                mon1.levelUp(mon1);
                if (g_eGameState == S_ENCOUNTERBOSS)
                {
                    g_eGameState = S_BOSSROUTE;
                }
                switch (location)
                {
                case 1: g_eGameState = S_GAME;
                    break;
                case 2: g_eGameState = S_ROUTE2;
                    break;
                case 3: g_eGameState = S_ROUTE3;
                    break;
                case 4: g_eGameState = S_BOSSROUTE; g_sChar.m_cLocation.Y = 17;
                    break;
                }
                if (wild.getName() == "atax")
                {
                    boss++;
                }
                if (wild.getName() == "smeltor")
                {
                    g_eGameState = S_GAMEOVER;
                }
                isHunter = false;
            }
            mon1.setAttack(1);
            if (mon1.getHealth() <= 0)
            {
                if (mon2.getName() == "NULL" && mon3.getName() == "NULL" && mon4.getName() == "NULL" && mon5.getName() == "NULL" && mon6.getName() == "NULL")
                {
                    g_eGameState = S_GAMEOVER;
                }

            }
        }
    }
    //Third skill
    if ((g_mouseEvent.mousePosition.X > 9 && g_mouseEvent.mousePosition.X < 17 && g_mouseEvent.mousePosition.Y == 22) && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
    {
        moveDecision = 2;
        int yourDMG = mon1.getMoveDamage(moveDecision) * (mon1.getAttack() / wild.getDefence() * 0.25 * effective);
        int wildDMG = wild.getMoveDamage(moveDecision) * ((wild.getAttack() / mon1.getDefence()) * 0.25 * effective);
        if (wild.getSpeed() >= mon1.getSpeed())
        {
            mon1.setHealth(-wildDMG);
            if (mon1.getHealth() <= 0)
            {
                if (mon2.getName() == "NULL" && mon3.getName() == "NULL" && mon4.getName() == "NULL" && mon5.getName() == "NULL" && mon6.getName() == "NULL")
                {
                    g_eGameState = S_GAMEOVER;
                }

            }
            wild.setHealth(-yourDMG);
            if (wild.getHealth() <= 0)
            {
                mon1.levelUp(mon1);
                if (g_eGameState == S_ENCOUNTERBOSS)
                {
                    g_eGameState = S_BOSSROUTE;
                }
                switch (location)
                {
                case 1: g_eGameState = S_GAME;
                    break;
                case 2: g_eGameState = S_ROUTE2;
                    break;
                case 3: g_eGameState = S_ROUTE3;
                    break;
                case 4: g_eGameState = S_BOSSROUTE; g_sChar.m_cLocation.Y = 17;
                    break;
                }
                if (wild.getName() == "atax")
                {
                    boss++;
                }
                if (wild.getName() == "smeltor")
                {
                    g_eGameState = S_GAMEOVER;
                }
                isHunter = false;
            }
        }
        else
        {
            wild.setHealth(-yourDMG);
            if (wild.getHealth() <= 0)
            {
                mon1.levelUp(mon1);
                if (g_eGameState == S_ENCOUNTERBOSS)
                {
                    g_eGameState = S_BOSSROUTE;
                }
                switch (location)
                {
                case 1: g_eGameState = S_GAME;
                    break;
                case 2: g_eGameState = S_ROUTE2;
                    break;
                case 3: g_eGameState = S_ROUTE3;
                    break;
                case 4: g_eGameState = S_BOSSROUTE; g_sChar.m_cLocation.Y = 17;
                    break;
                }
                if (wild.getName() == "atax")
                {
                    boss++;
                }
                if (wild.getName() == "smeltor")
                {
                    g_eGameState = S_GAMEOVER;
                }
                isHunter = false;
            }
            mon1.setHealth(-wildDMG);
            if (mon1.getHealth() <= 0)
            {
                if (mon2.getName() == "NULL" && mon3.getName() == "NULL" && mon4.getName() == "NULL" && mon5.getName() == "NULL" && mon6.getName() == "NULL")
                {
                    g_eGameState = S_GAMEOVER;
                }

            }
        }
    }
    //Fourth skill
    if ((g_mouseEvent.mousePosition.X > 27 && g_mouseEvent.mousePosition.X < 37 && g_mouseEvent.mousePosition.Y == 22) && g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
    {
        moveDecision = 3;
        int yourDMG = mon1.getMoveDamage(moveDecision) * (mon1.getAttack() / wild.getDefence() * 0.25 * effective);
        int wildDMG = wild.getMoveDamage(moveDecision) * ((wild.getAttack() / mon1.getDefence()) * 0.25 * effective);
        if (wild.getSpeed() >= mon1.getSpeed())
        {
            mon1.setHealth(-wildDMG);
            if (mon1.getHealth() <= 0)
            {
                if (mon2.getName() == "NULL" && mon3.getName() == "NULL" && mon4.getName() == "NULL" && mon5.getName() == "NULL" && mon6.getName() == "NULL")
                {
                    g_eGameState = S_GAMEOVER;
                }

            }
            wild.setHealth(-yourDMG);
            if (wild.getHealth() <= 0)
            {
                mon1.levelUp(mon1);
                if (g_eGameState == S_ENCOUNTERBOSS)
                {
                    g_eGameState = S_BOSSROUTE;
                }
                switch (location)
                {
                case 1: g_eGameState = S_GAME;
                    break;
                case 2: g_eGameState = S_ROUTE2;
                    break;
                case 3: g_eGameState = S_ROUTE3;
                    break;
                case 4: g_eGameState = S_BOSSROUTE; g_sChar.m_cLocation.Y = 17;
                    break;
                }
                if (wild.getName() == "atax")
                {
                    boss++;
                }
                if (wild.getName() == "smeltor")
                {
                    g_eGameState = S_GAMEOVER;
                }
                isHunter = false;
            }
        }
        else
        {
            wild.setHealth(-yourDMG);
            if (wild.getHealth() <= 0)
            {
                mon1.levelUp(mon1);
                if (g_eGameState == S_ENCOUNTERBOSS)
                {
                    g_eGameState = S_BOSSROUTE;
                }
                switch (location)
                {
                case 1: g_eGameState = S_GAME;
                    break;
                case 2: g_eGameState = S_ROUTE2;
                    break;
                case 3: g_eGameState = S_ROUTE3;
                    break;
                case 4: g_eGameState = S_BOSSROUTE; g_sChar.m_cLocation.Y = 17;
                    break;
                }
                if (wild.getName() == "atax")
                {
                    boss++;
                }
                if (wild.getName() == "smeltor")
                {
                    g_eGameState = S_GAMEOVER;
                }
                isHunter = false;
            }
            mon1.setHealth(-wildDMG);
            if (mon1.getHealth() <= 0)
            {
                if (mon2.getName() == "NULL" && mon3.getName() == "NULL" && mon4.getName() == "NULL" && mon5.getName() == "NULL" && mon6.getName() == "NULL")
                {
                    g_eGameState = S_GAMEOVER;
                }

            }
        }
    }
}

void moveSelection()
{
    // Updating the location of the character based on the key release
    // providing a beep sound whenver we shift the character
    COORD c;
    c.X = 20;
    c.Y = 20;
    if (g_skKeyEvent[K_UP].keyReleased && g_sChar.m_cLocation.Y > 0)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.Y--;
    }
    if (g_skKeyEvent[K_LEFT].keyReleased && g_sChar.m_cLocation.X > 0)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.X--;
    }
    if (g_skKeyEvent[K_DOWN].keyReleased && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.Y++;
    }
    if (g_skKeyEvent[K_RIGHT].keyReleased && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.X++;
    }
    if (g_skKeyEvent[K_Q].keyReleased)
    {
        g_sChar.m_bActive = !g_sChar.m_bActive;
    }

}


void moveCharacter()
{
    // Updating the location of the character based on the key release
    // providing a beep sound whenver we shift the character

    if (g_skKeyEvent[K_UP].keyDown && g_sChar.m_cLocation.Y > 0 || (g_skKeyEvent[K_UP].keyDown && g_sChar.m_cLocation.X >= 33 && g_sChar.m_cLocation.X < 44 && g_eGameState == S_ROUTE2) || (g_skKeyEvent[K_UP].keyDown && g_sChar.m_cLocation.X >= 33 && g_sChar.m_cLocation.X < 44 && g_eGameState == S_BOSSROUTE))
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.Y--;
    }
    if (g_skKeyEvent[K_LEFT].keyDown && g_sChar.m_cLocation.X > 0 || ((g_skKeyEvent[K_LEFT].keyDown && (g_sChar.m_cLocation.Y >= 12 && g_sChar.m_cLocation.Y < 16)) && g_eGameState == S_GAME))
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.X--;
    }
    if (g_skKeyEvent[K_DOWN].keyDown && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1 || (g_skKeyEvent[K_DOWN].keyDown && g_sChar.m_cLocation.X >= 33 && g_sChar.m_cLocation.X < 44 && (g_eGameState == S_ROUTE3 || g_eGameState == S_ROUTE2)))
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.Y++;
    }
    if (g_skKeyEvent[K_RIGHT].keyDown && (g_sChar.m_cLocation.X != 79 || (g_sChar.m_cLocation.Y >= 12 && g_sChar.m_cLocation.Y < 16 && g_eGameState != S_GAME)))
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.X++;
    }
    if (g_skKeyEvent[K_Q].keyReleased) //NPC interaction check
    {
        for (int i = 0; i < 4;i++ )//triggers NPC interaction
        {
            if (g_sChar.m_cLocation.X == Advice[i].getX() + 1 && g_sChar.m_cLocation.Y == Advice[i].getY() || g_sChar.m_cLocation.X == Advice[i].getX() - 1 && g_sChar.m_cLocation.Y == Advice[i].getY() ||
                g_sChar.m_cLocation.Y == Advice[i].getY() - 1 && g_sChar.m_cLocation.X == Advice[i].getX() || g_sChar.m_cLocation.Y == Advice[i].getY() + 1 && g_sChar.m_cLocation.X == Advice[i].getX())
            {
                Type = E_NPC;
                switch (g_eGameState)
                {
                case S_GAME: location = 1;
                    break;
                case S_ROUTE2: location = 2;
                    break;
                case S_ROUTE3: location = 3;
                    break;
                case S_BOSSROUTE: location = 4;
                    Type = E_Boss;
                    break;
                }
                g_eGameState = S_INTERACT;
            }
        }
        for (int i = 0; i < 8; i++)///triggers HUnter battle
        {
            if (g_sChar.m_cLocation.X == Enemy[i].getX() + 1 && g_sChar.m_cLocation.Y == Enemy[i].getY() || g_sChar.m_cLocation.X == Enemy[i].getX() - 1 && g_sChar.m_cLocation.Y == Enemy[i].getY() ||
                g_sChar.m_cLocation.Y == Enemy[i].getY() - 1 && g_sChar.m_cLocation.X == Enemy[i].getX() || g_sChar.m_cLocation.Y == Enemy[i].getY() + 1 && g_sChar.m_cLocation.X == Enemy[i].getX())
            {
                Type = E_Hunter;
                switch (g_eGameState)
                {
                case S_GAME: location = 1;
                    break;
                case S_ROUTE2: location = 2;
                    break;
                case S_ROUTE3: location = 3;
                    break;
                case S_BOSSROUTE:location = 4;
                    break;
                }
                g_eGameState = S_ENCOUNTERSPLASHSCREEN;
            }
        }
        //triggers Healer interctions
        if (g_sChar.m_cLocation.X == Nurse.getX() + 1 && g_sChar.m_cLocation.Y == Nurse.getY() || g_sChar.m_cLocation.X == Nurse.getX() - 1 && g_sChar.m_cLocation.Y == Nurse.getY() ||
            g_sChar.m_cLocation.Y == Nurse.getY() - 1 && g_sChar.m_cLocation.X == Nurse.getX() || g_sChar.m_cLocation.Y == Nurse.getY() + 1 && g_sChar.m_cLocation.X == Nurse.getX())
        {
            Type = E_Healer;
            g_eGameState = S_INTERACT;
        }
    }

    //Boss encounter check:
    if (g_eGameState == S_BOSSROUTE)
    {
        if ((g_sChar.m_cLocation.X >= 24 && g_sChar.m_cLocation.X < 51) && (g_sChar.m_cLocation.Y >= 18 && g_sChar.m_cLocation.Y < 22))
        {
            g_eGameState = S_BOSSSPLASHSCREEN;
        }
    }

    // map travelling check
    if ((g_sChar.m_cLocation.X < 0 && g_sChar.m_cLocation.Y >= 12 && g_sChar.m_cLocation.Y < 16) && g_eGameState == S_GAME)
    {
        g_sChar.m_cLocation.X = 79;
        g_eGameState = S_ROUTE2;
    }
    if ((g_sChar.m_cLocation.Y < 0 && g_sChar.m_cLocation.X >= 33 && g_sChar.m_cLocation.X < 44) && g_eGameState == S_ROUTE2)
    {
        g_sChar.m_cLocation.Y = 24;
        g_eGameState = S_ROUTE3;
    }
    if ((g_sChar.m_cLocation.X > 79 && g_sChar.m_cLocation.Y >= 12 && g_sChar.m_cLocation.Y < 16) && g_eGameState == S_ROUTE2)
    {
        g_sChar.m_cLocation.X = 0;
        g_eGameState = S_GAME;
    }
    if ((g_sChar.m_cLocation.Y > 24 && g_sChar.m_cLocation.X >= 33 && g_sChar.m_cLocation.X < 44) && g_eGameState == S_ROUTE2)
    {
        g_sChar.m_cLocation.Y = 0;
        g_eGameState = S_BOSSROUTE;
    }
    if ((g_sChar.m_cLocation.Y < 0 && g_sChar.m_cLocation.X >= 33 && g_sChar.m_cLocation.X < 44) && g_eGameState == S_BOSSROUTE)
    {
        g_sChar.m_cLocation.Y = 24;
        g_eGameState = S_ROUTE2;
    }
    if ((g_sChar.m_cLocation.Y > 24 && g_sChar.m_cLocation.X >= 33 && g_sChar.m_cLocation.X < 44) && g_eGameState == S_ROUTE3)
    {
        g_sChar.m_cLocation.Y = 0;
        g_eGameState = S_ROUTE2;
    }
    if (((g_sChar.m_cLocation.X >= 0 && g_sChar.m_cLocation.X < 13 && g_sChar.m_cLocation.Y > 4 && g_sChar.m_cLocation.Y < 12) ||
        (g_sChar.m_cLocation.X >= 61 && g_sChar.m_cLocation.X < 80 && g_sChar.m_cLocation.Y >=16 && g_sChar.m_cLocation.Y < 25) ||
        (g_sChar.m_cLocation.X >= 54 && g_sChar.m_cLocation.X < 70 && g_sChar.m_cLocation.Y >= 3 && g_sChar.m_cLocation.Y < 8) ||
        (g_sChar.m_cLocation.X >= 20 && g_sChar.m_cLocation.X < 36 && g_sChar.m_cLocation.Y >= 16 && g_sChar.m_cLocation.Y < 21)) && g_eGameState != S_ROUTE2 && g_eGameState == S_GAME)
    {
        switch (g_eGameState)
        {
        case S_GAME: location = 1;
            break;
        case S_ROUTE2: location = 2;
            break;
        case S_ROUTE3: location = 3;
            break;
        }
        if (rand() % 100 == 1)
        {
            g_eGameState = S_ENCOUNTERSPLASHSCREEN;
        }
    }
    if ((g_sChar.m_cLocation.X >= 0 && g_sChar.m_cLocation.X < 13 && g_sChar.m_cLocation.Y > 4 && g_sChar.m_cLocation.Y < 12) && g_eGameState != S_ROUTE2 && g_eGameState == S_ROUTE3)
    {
        switch (g_eGameState)
        {
        case S_GAME: location = 1;
            break;
        case S_ROUTE2: location = 2;
            break;
        case S_ROUTE3: location = 3;
            break;
        }
        if (rand() % 100 == 1)
        {
            g_eGameState = S_ENCOUNTERSPLASHSCREEN;
        }
    }
    if (g_skKeyEvent[K_F].keyReleased)
        g_eGameState = S_MENU;
        switch (g_eGameState)
        {
        case S_GAME: location = 1;
            break;
        case S_ROUTE2: location = 2;
            break;
        case S_ROUTE3: location = 3;
            break;
        case S_BOSSROUTE:location = 4;
            break;
    }
    collision();
    detection();
}

void collision()
{
    switch (location2)
    {
    case 1://collision start map
        for (int i = 0; i < 4; i++)//collision for NPC
        {
            if (g_skKeyEvent[K_UP].keyDown)
            {
                if (g_sChar.m_cLocation.X == Advice[i].getX() && g_sChar.m_cLocation.Y == Advice[i].getY())
                {
                    g_sChar.m_cLocation.Y++;
                }
            }
            if (g_skKeyEvent[K_LEFT].keyDown)
            {
                if (g_sChar.m_cLocation.X == Advice[i].getX() && g_sChar.m_cLocation.Y == Advice[i].getY())
                {
                    g_sChar.m_cLocation.X++;
                }
            }
            if (g_skKeyEvent[K_DOWN].keyDown)
            {
                if (g_sChar.m_cLocation.X == Advice[i].getX() && g_sChar.m_cLocation.Y == Advice[i].getY())
                {
                    g_sChar.m_cLocation.Y--;
                }
            }
            if (g_skKeyEvent[K_RIGHT].keyDown)
            {
                if (g_sChar.m_cLocation.X == Advice[i].getX() && g_sChar.m_cLocation.Y == Advice[i].getY())
                {
                    g_sChar.m_cLocation.X--;
                }
            }
        }
        for (int i = 0; i < 8; i++)//collision for Enemy
        {
            if (g_skKeyEvent[K_UP].keyDown)
            {
                if (g_sChar.m_cLocation.X == Enemy[i].getX() && g_sChar.m_cLocation.Y == Enemy[i].getY())
                {
                    g_sChar.m_cLocation.Y++;
                }
            }
            if (g_skKeyEvent[K_LEFT].keyDown)
            {
                if (g_sChar.m_cLocation.X == Enemy[i].getX() && g_sChar.m_cLocation.Y == Enemy[i].getY())
                {
                    g_sChar.m_cLocation.X++;
                }
            }
            if (g_skKeyEvent[K_DOWN].keyDown)
            {
                if (g_sChar.m_cLocation.X == Enemy[i].getX() && g_sChar.m_cLocation.Y == Enemy[i].getY())
                {
                    g_sChar.m_cLocation.Y--;
                }
            }
            if (g_skKeyEvent[K_RIGHT].keyDown)
            {
                if (g_sChar.m_cLocation.X == Enemy[i].getX() && g_sChar.m_cLocation.Y == Enemy[i].getY())
                {
                    g_sChar.m_cLocation.X--;
                }
            }
        }
        break;
    case 2://collision route 2
        for (int i = 1; i < 4; i++)//collision for NPC
        {
            if (g_skKeyEvent[K_UP].keyDown)
            {
                if (g_sChar.m_cLocation.X == Advice[i].getX() && g_sChar.m_cLocation.Y == Advice[i].getY())
                {
                    g_sChar.m_cLocation.Y++;
                }
            }
            if (g_skKeyEvent[K_LEFT].keyDown)
            {
                if (g_sChar.m_cLocation.X == Advice[i].getX() && g_sChar.m_cLocation.Y == Advice[i].getY())
                {
                    g_sChar.m_cLocation.X++;
                }
            }
            if (g_skKeyEvent[K_DOWN].keyDown)
            {
                if (g_sChar.m_cLocation.X == Advice[i].getX() && g_sChar.m_cLocation.Y == Advice[i].getY())
                {
                    g_sChar.m_cLocation.Y--;
                }
            }
            if (g_skKeyEvent[K_RIGHT].keyDown)
            {
                if (g_sChar.m_cLocation.X == Advice[i].getX() && g_sChar.m_cLocation.Y == Advice[i].getY())
                {
                    g_sChar.m_cLocation.X--;
                }
            }
        }
        for (int i = 2; i < 8; i++)//collision for Enemy
        {
            if (g_skKeyEvent[K_UP].keyDown)
            {
                if (g_sChar.m_cLocation.X == Enemy[i].getX() && g_sChar.m_cLocation.Y == Enemy[i].getY())
                {
                    g_sChar.m_cLocation.Y++;
                }
            }
            if (g_skKeyEvent[K_LEFT].keyDown)
            {
                if (g_sChar.m_cLocation.X == Enemy[i].getX() && g_sChar.m_cLocation.Y == Enemy[i].getY())
                {
                    g_sChar.m_cLocation.X++;
                }
            }
            if (g_skKeyEvent[K_DOWN].keyDown)
            {
                if (g_sChar.m_cLocation.X == Enemy[i].getX() && g_sChar.m_cLocation.Y == Enemy[i].getY())
                {
                    g_sChar.m_cLocation.Y--;
                }
            }
            if (g_skKeyEvent[K_RIGHT].keyDown)
            {
                if (g_sChar.m_cLocation.X == Enemy[i].getX() && g_sChar.m_cLocation.Y == Enemy[i].getY())
                {
                    g_sChar.m_cLocation.X--;
                }
            }
        }
        break;
    case 3://collision route 3
        for (int i = 2; i < 4; i++)//collision for NPC
        {
            if (g_skKeyEvent[K_UP].keyDown)
            {
                if (g_sChar.m_cLocation.X == Advice[i].getX() && g_sChar.m_cLocation.Y == Advice[i].getY())
                {
                    g_sChar.m_cLocation.Y++;
                }
            }
            if (g_skKeyEvent[K_LEFT].keyDown)
            {
                if (g_sChar.m_cLocation.X == Advice[i].getX() && g_sChar.m_cLocation.Y == Advice[i].getY())
                {
                    g_sChar.m_cLocation.X++;
                }
            }
            if (g_skKeyEvent[K_DOWN].keyDown)
            {
                if (g_sChar.m_cLocation.X == Advice[i].getX() && g_sChar.m_cLocation.Y == Advice[i].getY())
                {
                    g_sChar.m_cLocation.Y--;
                }
            }
            if (g_skKeyEvent[K_RIGHT].keyDown)
            {
                if (g_sChar.m_cLocation.X == Advice[i].getX() && g_sChar.m_cLocation.Y == Advice[i].getY())
                {
                    g_sChar.m_cLocation.X--;
                }
            }
        }
        for (int i = 4; i < 8; i++)//collision for Enemy
        {
            if (g_skKeyEvent[K_UP].keyDown)
            {
                if (g_sChar.m_cLocation.X == Enemy[i].getX() && g_sChar.m_cLocation.Y == Enemy[i].getY())
                {
                    g_sChar.m_cLocation.Y++;
                }
            }
            if (g_skKeyEvent[K_LEFT].keyDown)
            {
                if (g_sChar.m_cLocation.X == Enemy[i].getX() && g_sChar.m_cLocation.Y == Enemy[i].getY())
                {
                    g_sChar.m_cLocation.X++;
                }
            }
            if (g_skKeyEvent[K_DOWN].keyDown)
            {
                if (g_sChar.m_cLocation.X == Enemy[i].getX() && g_sChar.m_cLocation.Y == Enemy[i].getY())
                {
                    g_sChar.m_cLocation.Y--;
                }
            }
            if (g_skKeyEvent[K_RIGHT].keyDown)
            {
                if (g_sChar.m_cLocation.X == Enemy[i].getX() && g_sChar.m_cLocation.Y == Enemy[i].getY())
                {
                    g_sChar.m_cLocation.X--;
                }
            }
        }
        break;
    case 4://collision rout 4
        for (int i = 3; i < 4; i++)//collision for NPC
        {
            if (g_skKeyEvent[K_UP].keyDown)
            {
                if (g_sChar.m_cLocation.X == Advice[i].getX() && g_sChar.m_cLocation.Y == Advice[i].getY())
                {
                    g_sChar.m_cLocation.Y++;
                }
            }
            if (g_skKeyEvent[K_LEFT].keyDown)
            {
                if (g_sChar.m_cLocation.X == Advice[i].getX() && g_sChar.m_cLocation.Y == Advice[i].getY())
                {
                    g_sChar.m_cLocation.X++;
                }
            }
            if (g_skKeyEvent[K_DOWN].keyDown)
            {
                if (g_sChar.m_cLocation.X == Advice[i].getX() && g_sChar.m_cLocation.Y == Advice[i].getY())
                {
                    g_sChar.m_cLocation.Y--;
                }
            }
            if (g_skKeyEvent[K_RIGHT].keyDown)
            {
                if (g_sChar.m_cLocation.X == Advice[i].getX() && g_sChar.m_cLocation.Y == Advice[i].getY())
                {
                    g_sChar.m_cLocation.X--;
                }
            }
        }
        for (int i = 6; i < 8; i++)//collision for Enemy
        {
            if (g_skKeyEvent[K_UP].keyDown)
            {
                if (g_sChar.m_cLocation.X == Enemy[i].getX() && g_sChar.m_cLocation.Y == Enemy[i].getY())
                {
                    g_sChar.m_cLocation.Y++;
                }
            }
            if (g_skKeyEvent[K_LEFT].keyDown)
            {
                if (g_sChar.m_cLocation.X == Enemy[i].getX() && g_sChar.m_cLocation.Y == Enemy[i].getY())
                {
                    g_sChar.m_cLocation.X++;
                }
            }
            if (g_skKeyEvent[K_DOWN].keyDown)
            {
                if (g_sChar.m_cLocation.X == Enemy[i].getX() && g_sChar.m_cLocation.Y == Enemy[i].getY())
                {
                    g_sChar.m_cLocation.Y--;
                }
            }
            if (g_skKeyEvent[K_RIGHT].keyDown)
            {
                if (g_sChar.m_cLocation.X == Enemy[i].getX() && g_sChar.m_cLocation.Y == Enemy[i].getY())
                {
                    g_sChar.m_cLocation.X--;
                }
            }
        }
        break;
    }
    // Collision for house walls and nurse NPC
    if (g_eGameState == S_GAME)
    {
        if (g_skKeyEvent[K_UP].keyDown)
        {
            if ((g_sChar.m_cLocation.X == 21 && g_sChar.m_cLocation.Y > 5 && g_sChar.m_cLocation.Y < 11) || (g_sChar.m_cLocation.X == 34 && g_sChar.m_cLocation.Y > 5 && g_sChar.m_cLocation.Y < 11) ||
                (g_sChar.m_cLocation.Y == 6 && g_sChar.m_cLocation.X > 20 && g_sChar.m_cLocation.X < 35) || (g_sChar.m_cLocation.Y == 10 && g_sChar.m_cLocation.X > 20 && g_sChar.m_cLocation.X < 27) ||
                (g_sChar.m_cLocation.Y == 10 && g_sChar.m_cLocation.X > 31 && g_sChar.m_cLocation.X < 35) || (g_sChar.m_cLocation.X == Nurse.getX() && g_sChar.m_cLocation.Y == Nurse.getY()))
            {
                g_sChar.m_cLocation.Y++;
            }
        }
        if (g_skKeyEvent[K_LEFT].keyDown)
        {
            if ((g_sChar.m_cLocation.X == 21 && g_sChar.m_cLocation.Y > 5 && g_sChar.m_cLocation.Y < 11) || (g_sChar.m_cLocation.X == 34 && g_sChar.m_cLocation.Y > 5 && g_sChar.m_cLocation.Y < 11) ||
                (g_sChar.m_cLocation.Y == 6 && g_sChar.m_cLocation.X > 20 && g_sChar.m_cLocation.X < 35) || (g_sChar.m_cLocation.Y == 10 && g_sChar.m_cLocation.X > 20 && g_sChar.m_cLocation.X < 27) ||
                (g_sChar.m_cLocation.Y == 10 && g_sChar.m_cLocation.X > 31 && g_sChar.m_cLocation.X < 35) || (g_sChar.m_cLocation.X == Nurse.getX() && g_sChar.m_cLocation.Y == Nurse.getY()))
            {
                g_sChar.m_cLocation.X++;
            }
        }
        if (g_skKeyEvent[K_DOWN].keyDown)
        {
            if ((g_sChar.m_cLocation.X == 21 && g_sChar.m_cLocation.Y > 5 && g_sChar.m_cLocation.Y < 11) || (g_sChar.m_cLocation.X == 34 && g_sChar.m_cLocation.Y > 5 && g_sChar.m_cLocation.Y < 11) ||
                (g_sChar.m_cLocation.Y == 6 && g_sChar.m_cLocation.X > 20 && g_sChar.m_cLocation.X < 35) || (g_sChar.m_cLocation.Y == 10 && g_sChar.m_cLocation.X > 20 && g_sChar.m_cLocation.X < 27) ||
                (g_sChar.m_cLocation.Y == 10 && g_sChar.m_cLocation.X > 31 && g_sChar.m_cLocation.X < 35) || (g_sChar.m_cLocation.X == Nurse.getX() && g_sChar.m_cLocation.Y == Nurse.getY()))
            {
                g_sChar.m_cLocation.Y--;
            }
        }
        if (g_skKeyEvent[K_RIGHT].keyDown)
        {
            if ((g_sChar.m_cLocation.X == 21 && g_sChar.m_cLocation.Y > 5 && g_sChar.m_cLocation.Y < 11) || (g_sChar.m_cLocation.X == 34 && g_sChar.m_cLocation.Y > 5 && g_sChar.m_cLocation.Y < 11) ||
                (g_sChar.m_cLocation.Y == 6 && g_sChar.m_cLocation.X > 20 && g_sChar.m_cLocation.X < 35) || (g_sChar.m_cLocation.Y == 10 && g_sChar.m_cLocation.X > 20 && g_sChar.m_cLocation.X < 27) ||
                (g_sChar.m_cLocation.Y == 10 && g_sChar.m_cLocation.X > 31 && g_sChar.m_cLocation.X < 35) || (g_sChar.m_cLocation.X == Nurse.getX() && g_sChar.m_cLocation.Y == Nurse.getY()))
            {
                g_sChar.m_cLocation.X--;
            }
        }
    }
}

void detection()
{
    switch (location2)
    {
    case 1://detect main map
        for (int i = 0; i < 8; i++)
        {
            if (Enemy[i].getcheck() == false)
            {
                switch (Enemy[i].getdirection())
                {
                case(1)://detects vertically
                    for (int j = 0; j <= Enemy[i].getrange(); j++)
                    {
                        if ((g_sChar.m_cLocation.Y == Enemy[i].getY() - j || g_sChar.m_cLocation.Y == Enemy[i].getY() + j) && g_sChar.m_cLocation.X == Enemy[i].getX())
                        {
                            Type = E_Hunter;
                            g_eGameState = S_ENCOUNTERSPLASHSCREEN;
                            Enemy[i].setcheck(true);
                        }
                    }
                    break;
                case(2)://detects horizontally
                    for (int j = 0; j <= Enemy[i].getrange(); j++)
                    {
                        if (g_sChar.m_cLocation.Y == Enemy[i].getY() && (g_sChar.m_cLocation.X == Enemy[i].getX() - j || g_sChar.m_cLocation.X == Enemy[i].getX() + j))
                        {
                            Type = E_Hunter;
                            g_eGameState = S_ENCOUNTERSPLASHSCREEN;
                            Enemy[i].setcheck(true);
                        }
                    }
                    break;
                }
            }
        }
        break;
    case 2://detect route 2
        for (int i = 2; i < 8; i++)
        {
            if (Enemy[i].getcheck() == false)
            {
                switch (Enemy[i].getdirection())
                {
                case(1)://detects vertically
                    for (int j = 0; j <= Enemy[i].getrange(); j++)
                    {
                        if ((g_sChar.m_cLocation.Y == Enemy[i].getY() - j || g_sChar.m_cLocation.Y == Enemy[i].getY() + j) && g_sChar.m_cLocation.X == Enemy[i].getX())
                        {
                            Type = E_Hunter;
                            g_eGameState = S_ENCOUNTERSPLASHSCREEN;
                            Enemy[i].setcheck(true);
                        }
                    }
                    break;
                case(2)://detects horizontally
                    for (int j = 0; j <= Enemy[i].getrange(); j++)
                    {
                        if (g_sChar.m_cLocation.Y == Enemy[i].getY() && (g_sChar.m_cLocation.X == Enemy[i].getX() - j || g_sChar.m_cLocation.X == Enemy[i].getX() + j))
                        {
                            Type = E_Hunter;
                            g_eGameState = S_ENCOUNTERSPLASHSCREEN;
                            Enemy[i].setcheck(true);
                        }
                    }
                    break;
                }
            }
        }
        break;
    case 3://detect route 3
        for (int i = 4; i < 8; i++)
        {
            if (Enemy[i].getcheck() == false)
            {
                switch (Enemy[i].getdirection())
                {
                case(1)://detects vertically
                    for (int j = 0; j <= Enemy[i].getrange(); j++)
                    {
                        if ((g_sChar.m_cLocation.Y == Enemy[i].getY() - j || g_sChar.m_cLocation.Y == Enemy[i].getY() + j) && g_sChar.m_cLocation.X == Enemy[i].getX())
                        {
                            Type = E_Hunter;
                            g_eGameState = S_ENCOUNTERSPLASHSCREEN;
                            Enemy[i].setcheck(true);
                        }
                    }
                    break;
                case(2)://detects horizontally
                    for (int j = 0; j <= Enemy[i].getrange(); j++)
                    {
                        if (g_sChar.m_cLocation.Y == Enemy[i].getY() && (g_sChar.m_cLocation.X == Enemy[i].getX() - j || g_sChar.m_cLocation.X == Enemy[i].getX() + j))
                        {
                            Type = E_Hunter;
                            g_eGameState = S_ENCOUNTERSPLASHSCREEN;
                            Enemy[i].setcheck(true);
                        }
                    }
                    break;
                }
            }
        }
        break;
    case 4://detect bossmap
        for (int i = 6; i < 8; i++)
        {
            if (Enemy[i].getcheck() == false)
            {
                switch (Enemy[i].getdirection())
                {
                case(1)://detects vertically
                    for (int j = 0; j <= Enemy[i].getrange(); j++)
                    {
                        if ((g_sChar.m_cLocation.Y == Enemy[i].getY() - j || g_sChar.m_cLocation.Y == Enemy[i].getY() + j) && g_sChar.m_cLocation.X == Enemy[i].getX())
                        {
                            Type = E_Hunter;
                            g_eGameState = S_ENCOUNTERSPLASHSCREEN;
                            Enemy[i].setcheck(true);
                        }
                    }
                    break;
                case(2)://detects horizontally
                    for (int j = 0; j <= Enemy[i].getrange(); j++)
                    {
                        if (g_sChar.m_cLocation.Y == Enemy[i].getY() && (g_sChar.m_cLocation.X == Enemy[i].getX() - j || g_sChar.m_cLocation.X == Enemy[i].getX() + j))
                        {
                            Type = E_Hunter;
                            g_eGameState = S_ENCOUNTERSPLASHSCREEN;
                            Enemy[i].setcheck(true);
                        }
                    }
                    break;
                }
            }
        }
        break;
    }
    if (g_eGameState == S_BOSSROUTE)
    {
        if (g_sChar.m_cLocation.Y == Advice[3].getY())
        {
            if (warn == false)
            {
                Type = E_Boss;
                location = 4;
                g_eGameState = S_INTERACT;
                warn = true;
            }
        }
    }
}

void processUserInput()
{
    // quits the game if player hits the escape key
    if (g_skKeyEvent[K_ESCAPE].keyReleased)
        g_bQuitGame = true;

}

//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render()
{
    clearScreen();      // clears the current screen and draw from scratch 
    switch (g_eGameState)
    {
    case S_SPLASHSCREEN: renderSplashScreen();
        break;
    case S_GAME: renderGame();
        break;
    case S_MENU: renderMenu(); renderInstructions();
        break;
    case S_ENCOUNTERSPLASHSCREEN: renderEncounterSplashScreen();
        break;
    case S_ENCOUNTER:renderEncounter();
        break;
    case S_BOSSSPLASHSCREEN: renderBossSS();
        break;
    case S_ENCOUNTERBOSS: renderEncounterBoss();
        break;
    case S_TUTORIAL: renderTutorial();
        break;
    case S_STARTER: renderStarterScreen();
        break;
    case S_ROUTE2: renderGame2();
        break;
    case S_ROUTE3: renderGame3();
        break;
    case S_BOSSROUTE: renderBossRoute();
        break;
    case S_INTERACT: 
        switch (location)
        {
        case 1: renderGame(); renderInteract(); break;
        case 2: renderGame2(); renderInteract(); break;
        case 3: renderGame3(); renderInteract(); break;
        case 4: renderBossMap(); renderInteract(); break;
        }
        break;
    case S_GAMEOVER: renderGameOver();
        break;
    }
    renderInputEvents();
    renderToScreen();       // dump the contents of the buffer to the screen, one frame worth of game
}

void renderInstructions()
{
    COORD c;
    c.X = 0; c.Y = 19; g_Console.writeToBuffer(c, "WASD for movement", 0x0F);
    c.Y++; g_Console.writeToBuffer(c, "F for party menu", 0x0F);
    c.Y++; g_Console.writeToBuffer(c, "ESC for exit", 0x0F);
    c.Y++; g_Console.writeToBuffer(c, "Left click to select attacks and encounter decisions", 0x0F);
    c.Y++; g_Console.writeToBuffer(c, "Press Q near NPCs to talk to them");
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(0x1F);
}

void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}

void renderSplashScreen()  // renders the splash screen
{
    COORD c = g_Console.getConsoleSize();
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 80; j++)
        {
            c.Y = i; c.X = j;
            if ((c.X % 2 == 0 && c.Y % 2 == 0) || (c.X % 2 != 0 && c.Y % 2 != 0))
            {
                g_Console.writeToBuffer(c, " ", 0xB0);
            }
            else
            {
                g_Console.writeToBuffer(c, ' ', 0xA0);
            }
        }
    }
    c.X = 27;
    c.Y = 9;
    g_Console.writeToBuffer(c, "'Ele-beast Hunters.'  ", 0xA4);
    c.Y = 13;
    c.X = 25;
    g_Console.writeToBuffer(c, " Press 'Enter' to start", 0xA0);
    c.Y += 1;
    g_Console.writeToBuffer(c, " Press 'Esc' to quit    ", 0xA0);
}

// --------------------------GAME RENDERING---------------------------------
void renderGame()
{
    renderMap();        // renders the map to the buffer first
    renderCharacter();  // renders the character into the buffer
}
void renderGame2() //While in route 2
{
    renderRoute2(); // render mao of route 2.
    renderCharacter();  // renders the character into the buffer
}
void renderGame3()
{
    renderRoute3(); // render map if route 3
    renderCharacter();  // renders the character into the buffer
}
void renderBossRoute() //while in the boss map
{
    renderBossMap(); // renders map of boss route
    renderCharacter();
}
void renderGameOver()
{
    renderGameOverScreen();
}
// -------------------------------------------------------------------------

void renderMap()
{
    // Set up sample colours, and output shadings
    const WORD colors[] = {
        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
    };

    COORD c;
    for (int i = 0; i < 80; i++)
    {
        c.X = i;
        for (int j = 0; j < 25; j++)
        {
            c.Y = j;
            g_Console.writeToBuffer(c, "*", 0xE0);
        }
    }
    for (int i = 12; i < 16; i++)
    {
        c.Y = i;
        for (int j = 0; j < 80; j++)
        {
            c.X = j;
            colour(colors[5]);
            g_Console.writeToBuffer(c, "+", 0x60);
        }
    }
    //House.
    for (int i = 21; i < 35; i++)
    {
        c.X = i;
        for (int j = 6; j < 11; j++)
        {
            c.Y = j;
            colour(colors[5]);
            if (c.X == 21 || c.X == 34 || c.Y == 6 || c.Y == 10)
            {
                g_Console.writeToBuffer(c, " ", 0x00);
            }
            else
            {
                g_Console.writeToBuffer(c, " ", 0xD0);
            }
        }
        c.Y = 11;
        for (int i = 27; i < 32; i++)
        {
            c.X = i;
                g_Console.writeToBuffer(c, " ", 0xD2);
        }
        for (int i = 27; i < 32; i++)
        {
            c.X = i; c.Y = 10;
            g_Console.writeToBuffer(c, " ", 0xD2);
        }
    }
    //Nurse NPC to heal monster
    Nurse.setposition(29, 7);
    g_Console.writeToBuffer(Nurse.getposition(), char(3), 0x0C);
    //NPC
    Advice[0].setposition(44, 11);
    g_Console.writeToBuffer(Advice[0].getposition(), char(2), 0x0B);
    //Hunter
    Enemy[0].setposition(5, 16);
    Enemy[0].setDirRange(1, 4);
    g_Console.writeToBuffer(Enemy[0].getposition(), char(2), 0xC0);
    Enemy[1].setposition(59, 11);
    Enemy[1].setDirRange(1, 4);
    g_Console.writeToBuffer(Enemy[1].getposition(), char(2), 0xC0);
    location2 = 1;
    //Grasspatch test
    for (int i = 0; i < 13; i++)
    {
        c.X = i;
        for (int j = 5; j < 12; j++)
        {
            c.Y = j;
            colour(colors[1]);
            g_Console.writeToBuffer(c, "&", 0xA0);
        }
    }
    for (int i = 61; i < 80; i++) //patch 2
    {
        c.X = i;
        for (int j = 16; j < 25; j++)
        {
            c.Y = j;
            colour(colors[1]);
            g_Console.writeToBuffer(c, "&", 0xA0);
        }
    }
    for (int i = 54; i < 70; i++) //patch 3
    {
        c.X = i;
        for (int j = 3; j < 8; j++)
        {
            c.Y = j;
            colour(colors[1]);
            g_Console.writeToBuffer(c, "&", 0xA0);
        }
    }
    for (int i = 20; i < 36; i++) //patch 4
    {
        c.X = i;
        for (int j = 16; j < 21; j++)
        {
            c.Y = j;
            colour(colors[1]);
            g_Console.writeToBuffer(c, "&", 0xA0);
        }
    }
}

void renderRoute2()
{
    // Set up sample colours, and output shadings
    const WORD colors[] = {
        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
    };

    COORD c;
    for (int i = 0; i < 80; i++)
    {
        c.X = i;
        for (int j = 0; j < 25; j++)
        {
            c.Y = j;
            colour(colors[10]);
            g_Console.writeToBuffer(c, "*", 0xE0);
        }
    }
    for (int i = 33; i < 44; i++)
    {
        c.X = i;
        for (int j = 0; j < 25; j++)
        {
            c.Y = j;
            colour(colors[5]);
            g_Console.writeToBuffer(c, "+", 0x60);
        }
    }
    for (int i = 44; i < 80; i++)
    {
        c.X = i;
        for (int j = 11; j < 15; j++)
        {
            c.Y = j;
            colour(colors[5]);
            g_Console.writeToBuffer(c, "+", 0x60);
        }
    }
    location2 = 2;
}

void renderRoute3()
{
    // Set up sample colours, and output shadings
    const WORD colors[] = {
        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
    };

    COORD c;
    for (int i = 0; i < 80; i++)
    {
        c.X = i;
        for (int j = 0; j < 25; j++)
        {
            c.Y = j;
            colour(colors[10]);
            g_Console.writeToBuffer(c, "*", 0xE0);
        }
    }
    for (int i = 33; i < 44; i++)
    {
        c.X = i;
        for (int j = 0; j < 25; j++)
        {
            c.Y = j;
            colour(colors[5]);
            g_Console.writeToBuffer(c, "+", 0x60);
        }
    }
    location2 = 3;
    //Grasspatch test
    for (int i = 0; i < 13; i++) //patch 1
    {
        c.X = i;
        for (int j = 5; j < 12; j++)
        {
            c.Y = j;
            colour(colors[1]);
            g_Console.writeToBuffer(c, "&", 0xA0);
        }
    }

}

void renderBossMap()
{
    // Set up sample colours, and output shadings
    const WORD colors[] = {
        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
    };

    COORD c;
    for (int i = 0; i < 80; i++)
    {
        c.X = i;
        for (int j = 0; j < 25; j++)
        {
            c.Y = j;
            colour(colors[10]);
            g_Console.writeToBuffer(c, "*", 0xE0);
        }
    }
    for (int i = 33; i < 44; i++)
    {
        c.X = i;
        for (int j = 0; j < 23; j++)
        {
            c.Y = j;
            g_Console.writeToBuffer(c, "+", 0x60);
        }
    }
    for (int i = 23; i < 52; i++) //Boss cave layer 1.
    {
        c.X = i;
        for (int j = 18; j < 23; j++)
        {
            c.Y = j;
            g_Console.writeToBuffer(c, "||", 0x60);
            if (c.Y == 22 && c.X >23)
            {
                g_Console.writeToBuffer(c, "=", 0x60);
            }
        }
    }
    for (int i = 25; i < 51; i++) //Boss cave layer 2.
    {
        c.X = i;
        for (int j = 18; j < 22; j++)
        {
            c.Y = j;
            g_Console.writeToBuffer(c, "/", 0x06);
        }
    }
    //NPC
    Advice[3].setposition(47, 13);
    g_Console.writeToBuffer(Advice[3].getposition(), char(2), 0x0B);
    location2 = 4;
}

void renderInteract()
{
    COORD c;
    c.X = g_sChar.m_cLocation.X - 28;
    c.Y = g_sChar.m_cLocation.Y - 1;
    switch (Type)
    {
    case E_NPC: g_Console.writeToBuffer(c, Advice[0].interact(), 0x0B); break;
    case E_Healer: g_Console.writeToBuffer(c, Nurse.Healquote(), 0x0B);
            mon1.setHealth(mon1.getMaxHealth() - mon1.getHealth());
            break;
    case E_Boss: g_Console.writeToBuffer(c, Advice[3].warning(), 0x0B); break;
    }
}

void renderEncounter()
{
    string name1 = mon1.getName(), level1 = to_string(mon1.getLevel()), hp1 = to_string(mon1.getHealth()), atk1 = to_string(mon1.getAttack()), def1 = to_string(mon1.getDefence()), spd1 = to_string(mon1.getSpeed()),
        name2 = mon2.getName(), level2 = to_string(mon2.getLevel()), hp2 = to_string(mon2.getHealth()), atk2 = to_string(mon2.getAttack()), def2 = to_string(mon2.getDefence()), spd2 = to_string(mon2.getSpeed()),
        name3 = mon3.getName(), level3 = to_string(mon3.getLevel()), hp3 = to_string(mon3.getHealth()), atk3 = to_string(mon3.getAttack()), def3 = to_string(mon3.getDefence()), spd3 = to_string(mon3.getSpeed()),
        name4 = mon4.getName(), level4 = to_string(mon4.getLevel()), hp4 = to_string(mon4.getHealth()), atk4 = to_string(mon4.getAttack()), def4 = to_string(mon4.getDefence()), spd4 = to_string(mon4.getSpeed()),
        name5 = mon5.getName(), level5 = to_string(mon5.getLevel()), hp5 = to_string(mon5.getHealth()), atk5 = to_string(mon5.getAttack()), def5 = to_string(mon5.getDefence()), spd5 = to_string(mon5.getSpeed()),
        name6 = mon6.getName(), level6 = to_string(mon6.getLevel()), hp6 = to_string(mon6.getHealth()), atk6 = to_string(mon6.getAttack()), def6 = to_string(mon6.getDefence()), spd6 = to_string(mon6.getSpeed());
    string nameWild = wild.getName(), levelWild = to_string(wild.getLevel()), hpWild = to_string(wild.getHealth()), atkWild = to_string(wild.getAttack()), defWild = to_string(wild.getDefence()), spdWild = to_string(wild.getSpeed());
    const WORD colors[] = {
        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
    };

    COORD c;

    for (int i = 0; i < 80; i++)
    {
        c.X = i;
        for (int j = 0; j < 16; j++)
        {
            c.Y = j;
            colour(colors[11]);
            g_Console.writeToBuffer(c, " ", 0xB0);
        }
    }

    //Cardview for elebeast status
    for (int i = 1; i < 28; i++)
    {
        c.X = i;
        for (int j = 7; j < 12; j++)
        {
            c.Y = j;
            g_Console.writeToBuffer(c, " ", 0x60);
        }
    }

    //Cardview for wild elebeast status
    for (int i = 42; i < 65; i++)
    {
        c.X = i;
        for (int j = 7; j < 12; j++)
        {
            c.Y = j;
            g_Console.writeToBuffer(c, " ", 0x60);
        }
    }

    c.X = 7; c.Y = 8;
    g_Console.writeToBuffer(c, "Ele-beast: ", 0x60); c.Y++; g_Console.writeToBuffer(c, "Level: ", 0x60); c.Y++; g_Console.writeToBuffer(c, "HP: ", 0x60); c.Y++; c.X -= 6;
    for (float i = 0; i < mon1.getHealth() / 2; i++) //health bar test
    {
        g_Console.writeToBuffer(c, " ", 0xA0); c.X++;
    }
    c.Y = 8;
    c.X = 17;
    g_Console.writeToBuffer(c, name1, 0x60); c.Y++; g_Console.writeToBuffer(c, level1, 0x60); c.Y++; g_Console.writeToBuffer(c, hp1, 0x60); c.Y = 8;
    c.X = 44;
    g_Console.writeToBuffer(c, "Ele-beast: ", 0x60); c.Y++; g_Console.writeToBuffer(c, "Level: ", 0x60); c.Y++; g_Console.writeToBuffer(c, "HP: ", 0x60); c.Y++; c.X--;
    for (float i = 0; i < wild.getHealth() / 2; i++) //health bar test
    {
        g_Console.writeToBuffer(c, " ", 0xA0); c.X++;
    }
    c.X = 54; c.Y = 8;
    g_Console.writeToBuffer(c, nameWild, 0x60); c.Y++; g_Console.writeToBuffer(c, levelWild, 0x60); c.Y++; g_Console.writeToBuffer(c, hpWild, 0x60); c.Y = 8;
    c.X = 1; c.Y = 24;

    for (int i = 0; i < 80; i++)
    {
        c.X = i;
        c.Y = 16;
        colour(colors[5]);
        g_Console.writeToBuffer(c, " ", colors[5]);
    }

    for (int i = 0; i < 80; i++)
    {
        c.X = i;
        for (int j = 17; j < 25; j++)
        {
            c.Y = j;
            colour(colors[10]);
            g_Console.writeToBuffer(c, " ", colors[10]);
        }
    }

    c.X = 56;
    c.Y = 20;
    g_Console.writeToBuffer(c, "Catch");
    c.X = 68;
    c.Y = 20;
    g_Console.writeToBuffer(c, "Run");

    for (int i = 50; i < 51; i++)
    {
        c.X = i;
        for (int j = 17; j < 25; j++)
        {
            c.Y = j;
            colour(colors[5]);
            g_Console.writeToBuffer(c, " ", colors[5]);
        }
    }
    c.X = 10; c.Y = 12;
    g_Console.writeToBuffer(c, "    .", 0xB0); c.Y += 1;
    g_Console.writeToBuffer(c, "   (>", 0xB0); c.Y += 1;
    g_Console.writeToBuffer(c, "~(##)", 0xB0); c.Y += 1;
    g_Console.writeToBuffer(c, " // | ", 0XB0);
    c.X = 50; c.Y = 12;
    g_Console.writeToBuffer(c, ".    ", 0xB0); c.Y += 1;
    g_Console.writeToBuffer(c, "<)   ", 0xB0); c.Y += 1;
    g_Console.writeToBuffer(c, "(##)~", 0xB0); c.Y += 1;
    g_Console.writeToBuffer(c, "| \\ ", 0XB0);

    c.X = 10, c.Y = 19;
    g_Console.writeToBuffer(c, mon1.getMove(0));
    c.X = 27, c.Y = 19;
    g_Console.writeToBuffer(c, mon1.getMove(1));
    c.X = 10, c.Y = 22;
    g_Console.writeToBuffer(c, mon1.getMove(2));
    c.X = 27, c.Y = 22;
    g_Console.writeToBuffer(c, mon1.getMove(3));
    c.X = 10, c.Y = 10;



}

void renderEncounterSplashScreen()
{
    COORD c;
    c.X = 27;
    c.Y = 18;
    if (Type == E_Hunter)
    {
        g_Console.writeToBuffer(c, "You have been challenged to a battle!");
        Type = E_NULL;
    }
    else
    {
        g_Console.writeToBuffer(c, "Wild Elebeasts Appears!");
    }
}


//Render boss splash screen
void renderBossSS()
{
    COORD c;
    c.X = 0; c.Y = 0;

    //Background
    for (int i = 0; i < 80; i++)
    {
        c.X = i;
        for (int j = 0; j < 25; j++)
        {
            c.Y = j;
            g_Console.writeToBuffer(c, " ", 0x00);
        }
    }
    //Letter B (vertical lines)
    for (int i = 8; i < 16; i++)
    {
        c.Y = i;
        c.X = 19;
        g_Console.writeToBuffer(c, " ", 0xC0);
    }

    for (int i = 9; i < 12; i++)
    {
        c.Y = i;
        c.X = 24;
        g_Console.writeToBuffer(c, " ", 0xC0);
    }

    for (int i = 12; i < 15; i++)
    {
        c.Y = i;
        c.X = 27;
        g_Console.writeToBuffer(c, " ", 0xC0);
    }
    //Letter B (horizontal lines)
    for (int i = 20; i < 25; i++)
    {
        c.X = i;
        c.Y = 8;
        g_Console.writeToBuffer(c, " ", 0xC0);
    }

    for (int i = 20; i < 28; i++)
    {
        c.X = i;
        c.Y = 11;
        g_Console.writeToBuffer(c, " ", 0xC0);
    }

    for (int i = 20; i < 28; i++)
    {
        c.X = i;
        c.Y = 15;
        g_Console.writeToBuffer(c, " ", 0xC0);
    }
    
    //For letter O
    for (int i = 30; i < 38; i++)
    {
        c.X = i;
        c.Y = 11;
        g_Console.writeToBuffer(c, " ", 0xC0);
    }
    for (int i = 30; i < 38; i++)
    {
        c.X = i;
        c.Y = 15;
        g_Console.writeToBuffer(c, " ", 0xC0);
    }
    for (int i = 12; i < 15; i++)
    {
        c.Y = i;
        c.X = 30;
        g_Console.writeToBuffer(c, " ", 0xC0);
    }

    for (int i = 12; i < 15; i++)
    {
        c.Y = i;
        c.X = 37;
        g_Console.writeToBuffer(c, " ", 0xC0);
    }

    //For first S
    for (int i = 40; i < 47; i++)
    {
        c.X = i;
        c.Y = 11;
        g_Console.writeToBuffer(c, " ", 0xC0);
    }
    for (int i = 40; i < 47; i++)
    {
        c.X = i;
        c.Y = 13;
        g_Console.writeToBuffer(c, " ", 0xC0);
    }
    for (int i = 40; i < 47; i++)
    {
        c.X = i;
        c.Y = 15;
        g_Console.writeToBuffer(c, " ", 0xC0);
    }

    c.X = 40, c.Y = 12; g_Console.writeToBuffer(c, " ", 0xC0);
    c.X = 46, c.Y = 14; g_Console.writeToBuffer(c, " ", 0xC0);

    //for second s
    for (int i = 49; i < 56; i++)
    {
        c.X = i;
        c.Y = 11;
        g_Console.writeToBuffer(c, " ", 0xC0);
    }
    for (int i = 49; i < 56; i++)
    {
        c.X = i;
        c.Y = 13;
        g_Console.writeToBuffer(c, " ", 0xC0);
    }
    for (int i = 49; i < 56; i++)
    {
        c.X = i;
        c.Y = 15;
        g_Console.writeToBuffer(c, " ", 0xC0);
    }

    c.X = 49, c.Y = 12; g_Console.writeToBuffer(c, " ", 0xC0);
    c.X = 55, c.Y = 14; g_Console.writeToBuffer(c, " ", 0xC0);

    //For exclamation mark
    for (int i = 10; i < 14; i++)
    {
        c.X = 58;
        c.Y = i;
        g_Console.writeToBuffer(c, " ", 0xC0);
    }
    c.X = 58; c.Y = 15; g_Console.writeToBuffer(c, " ", 0xC0);

    //For exclamation mark
    for (int i = 10; i < 14; i++)
    {
        c.X = 60;
        c.Y = i;
        g_Console.writeToBuffer(c, " ", 0xC0);
    }
    c.X = 60; c.Y = 15; g_Console.writeToBuffer(c, " ", 0xC0);

    //For exclamation mark
    for (int i = 10; i < 14; i++)
    {
        c.X = 62;
        c.Y = i;
        g_Console.writeToBuffer(c, " ", 0xC0);
    }
    c.X = 62; c.Y = 15; g_Console.writeToBuffer(c, " ", 0xC0);
}

//When encounter boss
void renderEncounterBoss()
{
    string name1 = mon1.getName(), level1 = to_string(mon1.getLevel()), hp1 = to_string(mon1.getHealth()), atk1 = to_string(mon1.getAttack()), def1 = to_string(mon1.getDefence()), spd1 = to_string(mon1.getSpeed()),
        name2 = mon2.getName(), level2 = to_string(mon2.getLevel()), hp2 = to_string(mon2.getHealth()), atk2 = to_string(mon2.getAttack()), def2 = to_string(mon2.getDefence()), spd2 = to_string(mon2.getSpeed()),
        name3 = mon3.getName(), level3 = to_string(mon3.getLevel()), hp3 = to_string(mon3.getHealth()), atk3 = to_string(mon3.getAttack()), def3 = to_string(mon3.getDefence()), spd3 = to_string(mon3.getSpeed()),
        name4 = mon4.getName(), level4 = to_string(mon4.getLevel()), hp4 = to_string(mon4.getHealth()), atk4 = to_string(mon4.getAttack()), def4 = to_string(mon4.getDefence()), spd4 = to_string(mon4.getSpeed()),
        name5 = mon5.getName(), level5 = to_string(mon5.getLevel()), hp5 = to_string(mon5.getHealth()), atk5 = to_string(mon5.getAttack()), def5 = to_string(mon5.getDefence()), spd5 = to_string(mon5.getSpeed()),
        name6 = mon6.getName(), level6 = to_string(mon6.getLevel()), hp6 = to_string(mon6.getHealth()), atk6 = to_string(mon6.getAttack()), def6 = to_string(mon6.getDefence()), spd6 = to_string(mon6.getSpeed());

    string nameBoss = wild.getName(), levelBoss = to_string(wild.getLevel()), hpBoss = to_string(wild.getHealth()), atkBoss = to_string(wild.getAttack()), defBoss = to_string(wild.getDefence()), spdBoss = to_string(wild.getSpeed());
    const WORD colors[] = {
        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
    };

    COORD c;

    for (int i = 0; i < 80; i++)
    {
        c.X = i;
        for (int j = 0; j < 16; j++)
        {
            c.Y = j;
            colour(colors[11]);
            g_Console.writeToBuffer(c, " ", 0xC0);
        }
    }
    c.X = 1; c.Y = 8;
    g_Console.writeToBuffer(c, "Ele-beast: ", 0xC0); c.Y++; g_Console.writeToBuffer(c, "Level: ", 0xC0); c.Y++; g_Console.writeToBuffer(c, "HP: ", 0xC0); c.Y++; c.X++;
    for (float i = 0; i < mon1.getHealth() / 2; i++) //health bar test
    {
        g_Console.writeToBuffer(c, " ", 0xA0); c.X++;
    }
    c.Y = 8;
    c.X = 11;
    g_Console.writeToBuffer(c, name1, 0xC0); c.Y++; g_Console.writeToBuffer(c, level1, 0xC0); c.Y++; g_Console.writeToBuffer(c, hp1, 0xC0); c.Y = 8;
    c.X = 48;
    g_Console.writeToBuffer(c, "Ele-beast: ", 0xC0); c.Y++; g_Console.writeToBuffer(c, "Level: ", 0xC0); c.Y++; g_Console.writeToBuffer(c, "HP: ", 0xC0); c.Y++; c.X -= 8;
    for (float i = 0; i < wild.getHealth() / 2; i++) //health bar test
    {
        g_Console.writeToBuffer(c, " ", 0xA0); c.X++;
    }
    c.X = 59; c.Y = 8;
    g_Console.writeToBuffer(c, nameBoss, 0xC0); c.Y++; g_Console.writeToBuffer(c, levelBoss, 0xC0); c.Y++; g_Console.writeToBuffer(c, hpBoss, 0xC0); c.Y = 9;
    c.X = 1; c.Y = 24;

    for (int i = 0; i < 80; i++)
    {
        c.X = i;
        c.Y = 16;
        g_Console.writeToBuffer(c, " ", 0x00);
    }

    for (int i = 0; i < 80; i++)
    {
        c.X = i;
        for (int j = 17; j < 25; j++)
        {
            c.Y = j;
            g_Console.writeToBuffer(c, " ", 0x80);
        }
    }

    for (int i = 50; i < 51; i++)
    {
        c.X = i;
        for (int j = 17; j < 25; j++)
        {
            c.Y = j;

            g_Console.writeToBuffer(c, " ");
        }
    }
    c.X = 10; c.Y = 12;
    g_Console.writeToBuffer(c, "    .", 0xC0); c.Y += 1;
    g_Console.writeToBuffer(c, "   (>", 0xC0); c.Y += 1;
    g_Console.writeToBuffer(c, "~(##)", 0xC0); c.Y += 1;
    g_Console.writeToBuffer(c, " // | ", 0XC0);
    c.X = 50; c.Y = 12;
    g_Console.writeToBuffer(c, ".    ", 0xC0); c.Y += 1;
    g_Console.writeToBuffer(c, "<)   ", 0xC0); c.Y += 1;
    g_Console.writeToBuffer(c, "(##)~", 0xC0); c.Y += 1;
    g_Console.writeToBuffer(c, "| \\ ", 0XC0);

    c.X = 10, c.Y = 19;
    g_Console.writeToBuffer(c, mon1.getMove(0));
    c.X = 27, c.Y = 19;
    g_Console.writeToBuffer(c, mon1.getMove(1));
    c.X = 10, c.Y = 22;
    g_Console.writeToBuffer(c, mon1.getMove(2));
    c.X = 27, c.Y = 22;
    g_Console.writeToBuffer(c, mon1.getMove(3));
    c.X = 10, c.Y = 10;



}


void renderMenu()
{
    string name1 = mon1.getName(), level1 = to_string(mon1.getLevel()), hp1 = to_string(mon1.getHealth()), atk1 = to_string(mon1.getAttack()), def1 = to_string(mon1.getDefence()), spd1 = to_string(mon1.getSpeed()),
        name2 = mon2.getName(), level2 = to_string(mon2.getLevel()), hp2 = to_string(mon2.getHealth()), atk2 = to_string(mon2.getAttack()), def2 = to_string(mon2.getDefence()), spd2 = to_string(mon2.getSpeed()),
        name3 = mon3.getName(), level3 = to_string(mon3.getLevel()), hp3 = to_string(mon3.getHealth()), atk3 = to_string(mon3.getAttack()), def3 = to_string(mon3.getDefence()), spd3 = to_string(mon3.getSpeed()),
        name4 = mon4.getName(), level4 = to_string(mon4.getLevel()), hp4 = to_string(mon4.getHealth()), atk4 = to_string(mon4.getAttack()), def4 = to_string(mon4.getDefence()), spd4 = to_string(mon4.getSpeed()),
        name5 = mon5.getName(), level5 = to_string(mon5.getLevel()), hp5 = to_string(mon5.getHealth()), atk5 = to_string(mon5.getAttack()), def5 = to_string(mon5.getDefence()), spd5 = to_string(mon5.getSpeed()),
        name6 = mon6.getName(), level6 = to_string(mon6.getLevel()), hp6 = to_string(mon6.getHealth()), atk6 = to_string(mon6.getAttack()), def6 = to_string(mon6.getDefence()), spd6 = to_string(mon6.getSpeed());
    COORD c;
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 80; j++)
        {
            c.X = j; c.Y = i;
                g_Console.writeToBuffer(c, " ", 0xC2);
        }
    }
    c.X = 1; c.Y = 1;
    g_Console.writeToBuffer(c, "This is the pause menu.", 0xC0);
    c.Y += 2;
    g_Console.writeToBuffer(c, "Ele-beast 1:          Lv:   HP:   Atk:   Def:  Spd: ", 0xC0); c.X += 12;
    g_Console.writeToBuffer(c, name1, 0xC0); c.X += 13; g_Console.writeToBuffer(c, level1, 0xC0); c.X += 6; g_Console.writeToBuffer(c, hp1, 0xC0); c.X += 7; g_Console.writeToBuffer(c, atk1, 0xC0); c.X += 7;
    g_Console.writeToBuffer(c, def1, 0xC0); c.X += 6; g_Console.writeToBuffer(c, spd1, 0xC0); c.X = 1;
    c.Y += 2;
    g_Console.writeToBuffer(c, "Ele-beast 2:          Lv:   HP:   Atk:   Def:  Spd: : ", 0xC0); c.X += 12;
    g_Console.writeToBuffer(c, name2, 0xC0); c.X += 13; g_Console.writeToBuffer(c, level2, 0xC0); c.X += 6; g_Console.writeToBuffer(c, hp2, 0xC0); c.X += 7; g_Console.writeToBuffer(c, atk2, 0xC0); c.X += 7;
    g_Console.writeToBuffer(c, def2, 0xC0); c.X += 6; g_Console.writeToBuffer(c, spd2, 0xC0); c.X = 1;
    c.Y += 2;
    g_Console.writeToBuffer(c, "Ele-beast 3:          Lv:   HP:   Atk:   Def:  Spd: : ", 0xC0); c.X += 12;
    g_Console.writeToBuffer(c, name3, 0xC0); c.X += 13; g_Console.writeToBuffer(c, level3, 0xC0); c.X += 6; g_Console.writeToBuffer(c, hp3, 0xC0); c.X += 7; g_Console.writeToBuffer(c, atk3, 0xC0); c.X += 7;
    g_Console.writeToBuffer(c, def3, 0xC0); c.X += 6; g_Console.writeToBuffer(c, spd3, 0xC0); c.X = 1;
    c.Y += 2;
    g_Console.writeToBuffer(c, "Ele-beast 4:          Lv:   HP:   Atk:   Def:  Spd: : ", 0xC0); c.X += 12;
    g_Console.writeToBuffer(c, name4, 0xC0); c.X += 13; g_Console.writeToBuffer(c, level4, 0xC0); c.X += 6; g_Console.writeToBuffer(c, hp4, 0xC0); c.X += 7; g_Console.writeToBuffer(c, atk4, 0xC0); c.X += 7;
    g_Console.writeToBuffer(c, def4, 0xC0); c.X += 6; g_Console.writeToBuffer(c, spd4, 0xC0); c.X = 1;
    c.Y += 2;
    g_Console.writeToBuffer(c, "Ele-beast 5:          Lv:   HP:   Atk:   Def:  Spd: : ", 0xC0); c.X += 12;
    g_Console.writeToBuffer(c, name5, 0xC0); c.X += 13; g_Console.writeToBuffer(c, level5, 0xC0); c.X += 6; g_Console.writeToBuffer(c, hp5, 0xC0); c.X += 7; g_Console.writeToBuffer(c, atk5, 0xC0); c.X += 7;
    g_Console.writeToBuffer(c, def1, 0xC0); c.X += 6; g_Console.writeToBuffer(c, spd1, 0xC0); c.X = 1;
    c.Y += 2;
    g_Console.writeToBuffer(c, "Ele-beast 6:          Lv:   HP:   Atk:   Def:  Spd: : ", 0xC0); c.X += 12;
    g_Console.writeToBuffer(c, name6, 0xC0); c.X += 13; g_Console.writeToBuffer(c, level6, 0xC0); c.X += 6; g_Console.writeToBuffer(c, hp6, 0xC0); c.X += 7; g_Console.writeToBuffer(c, atk6, 0xC0); c.X += 7;
    g_Console.writeToBuffer(c, def6, 0xC0); c.X += 6; g_Console.writeToBuffer(c, spd6, 0xC0); c.X = 1;
    c.Y += 3; c.X += 28;
    g_Console.writeToBuffer(c, "Press F to EXIT PAUSE MENU.", 0xC0);
    c.Y++;
    g_Console.writeToBuffer(c, "Press 'ESC' to EXIT THE GAME.", 0xC0);
    c.Y++;
}

void renderTutorial()
{
    COORD c;
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 80; j++)
        {
            c.X = j; c.Y = i;
            g_Console.writeToBuffer(c, " ", 0xB0);
        }
    }
    c.X = 0; c.Y = 5; 
    g_Console.writeToBuffer(c, "Welcome to the world of ele-beasts! Adventure and challenges await during your ", 0xB0); c.Y++;
    g_Console.writeToBuffer(c, "journey. When you start, you will be prompted to select a starting ele-beast to", 0xB0); c.Y++;
    g_Console.writeToBuffer(c, "accompany you in your travels. Fight and catch other ele-beasts to make yours ", 0xB0); c.Y++;
    g_Console.writeToBuffer(c, "stronger, and defeat the two mysterious ele-beast in cave near your home to", 0xB0); c.Y++;
    g_Console.writeToBuffer(c, "free yourself and explore the rest of the world.", 0xB0); c.Y += 3;
    c.X = 19; c.Y = 18; g_Console.writeToBuffer(c, "Press [ENTER] to start your adventure!", 0xB0);
}

void renderStarterScreen()
{
    COORD c;
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 80; j++)
        {
            c.X = j; c.Y = i;
            g_Console.writeToBuffer(c, " ", 0xC0);
        }
    }
    c.X = 12; c.Y = 10; g_Console.writeToBuffer(c, "Please choose your starting ele-beast (Left click to choose): ", 0xC0); c.X += 7;
    c.Y += 2; g_Console.writeToBuffer(c, "1: ignis(fire) ", 0xC0); c.X += 15; g_Console.writeToBuffer(c, "2: typhis(water) ", 0xC0); c.X += 17; g_Console.writeToBuffer(c, "3: vitalus(nature)", 0xC0);
}

void renderCharacter()
{
    // Draw the location of the character
    WORD charColor = 0x0C;
    if (g_sChar.m_bActive)
    {
        charColor = 0x0A;
    }
    g_Console.writeToBuffer(g_sChar.m_cLocation, (char)1, charColor);
}

void renderGameOverScreen()
{
    COORD c;
    for (int i = 0; i < 80; i++)
    {
        c.X = i;
        for (int j = 0; j < 25; j++)
        {
            c.Y = j;
            g_Console.writeToBuffer(c, ".", 0x0F);
        }
    }
    c.X = 40; c.Y = 12;
    g_Console.writeToBuffer(c, "Game over...", 0x0F);
}

void renderFramerate()
{
    COORD c;
    // displays the framerate
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << 1.0 / g_dDeltaTime << "fps";
    c.X = g_Console.getConsoleSize().X - 9;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str());

    // displays the elapsed time
    ss.str("");
    ss << g_dElapsedTime << "secs";
    c.X = 0;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str(), 0x59);
}

// this is an example of how you would use the input events
void renderInputEvents()
{
    // keyboard events
    COORD startPos = {50, 2};
    std::ostringstream ss;
    std::string key;

    // mouse events    
    ss.str("");
    ss << "Mouse position (" << g_mouseEvent.mousePosition.X << ", " << g_mouseEvent.mousePosition.Y << ")";
    g_Console.writeToBuffer(g_mouseEvent.mousePosition, ss.str(), 0x59);
    ss.str("");
    switch (g_mouseEvent.eventFlags)
    {
    case 0:
        if (g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
        {
            ss.str("Left Button Pressed");
            g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 1, ss.str(), 0x59);
        }
        else if (g_mouseEvent.buttonState == RIGHTMOST_BUTTON_PRESSED)
        {
            ss.str("Right Button Pressed");
            g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 2, ss.str(), 0x59);
        }
        else
        {
            ss.str("Some Button Pressed");
            g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 3, ss.str(), 0x59);
        }
        break;
    case DOUBLE_CLICK:
        ss.str("Double Clicked");
        g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 4, ss.str(), 0x59);
        break;        
    case MOUSE_WHEELED:
        if (g_mouseEvent.buttonState & 0xFF000000)
            ss.str("Mouse wheeled down");
        else
            ss.str("Mouse wheeled up");
        g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 5, ss.str(), 0x59);
        break;
    default:        
        break;
    }
    
}



