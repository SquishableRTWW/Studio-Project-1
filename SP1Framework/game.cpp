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

double  g_dElapsedTime;
bool testing = false;
double  g_dDeltaTime;
hunter jeff;
SKeyEvent g_skKeyEvent[K_COUNT + 2];
SMouseEvent g_mouseEvent;

// Game specific variables here
SGameChar   g_sChar;
EGAMESTATES g_eGameState = S_SPLASHSCREEN; // initial state

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
    // Set precision for floating point output
    g_dElapsedTime = 0.0;    
    jeff.choosestarter(1);
    // sets the initial state for the game (which is the start screen).
    g_eGameState = S_SPLASHSCREEN;
    g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
    g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y / 2;
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
        case S_ENCOUNTERSPLASHSCREEN: encounterScreenWait();
            break;
        case S_ENCOUNTER: updateEncounter();
            break;
        case S_TUTORIAL: tutorialWait();
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
        g_eGameState = S_GAME;
    if (g_skKeyEvent[K_ESCAPE].keyReleased)
        g_bQuitGame = true;
}

void tutorialWait()
{
    if (g_skKeyEvent[K_ENTER].keyReleased) // wait for user to press 'Enter' to go on to game screen.
        g_eGameState = S_GAME;
}

void updateEncounter()
{
    processUserInput();
    moveSelection();
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

    if (g_sChar.m_cLocation.X > 29 && g_sChar.m_cLocation.X < 40 && g_sChar.m_cLocation.Y > 4 && g_sChar.m_cLocation.Y < 10)
    {
        g_eGameState = S_ENCOUNTERSPLASHSCREEN;
    }

}
void processUserInput()
{
    // quits the game if player hits the escape key
    if (g_skKeyEvent[K_ESCAPE].keyReleased)
        g_bQuitGame = true;
    if (g_skKeyEvent[K_F].keyReleased)
        g_eGameState = S_MENU;
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
    case S_MENU: renderMenu();
        break;
    case S_ENCOUNTERSPLASHSCREEN: renderEncounterSplashScreen();
        break;
    case S_ENCOUNTER: renderEncounter();
        break;
    case S_TUTORIAL: renderTutorial();
        break;
    }
    renderFramerate();      // renders debug information, frame rate, elapsed time, etc
    renderInputEvents();    // renders status of input events
    renderToScreen();       // dump the contents of the buffer to the screen, one frame worth of game
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

void renderGame()
{
    renderMap();        // renders the map to the buffer first
    renderCharacter();  // renders the character into the buffer
}

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
            colour(colors[11]);
            g_Console.writeToBuffer(c, " ", colors[11]);
        }
    }

    //Grasspatch test
    for (int i = 30; i < 40; i++)
    {
        c.X = i;
        for (int j = 5; j < 10; j++)
        {
            c.Y = j;
            colour(colors[1]);
            g_Console.writeToBuffer(c, " ", colors[1]);
        }
    }
}

void renderEncounter()
{
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
            colour(colors[11]);
            g_Console.writeToBuffer(c, " ", colors[10]);
        }

    }

    c.X = 56;
    c.Y = 19;                          //Background - Text
    g_Console.writeToBuffer(c, "Attack", 0x51);
    c.X = 66;
    c.Y = 19;
    g_Console.writeToBuffer(c, "Catch");
    c.X = 55;
    c.Y = c.Y + 2;
    g_Console.writeToBuffer(c, "EleBeast");
    c.X = 67;
    c.Y = c.Y;
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
    g_Console.writeToBuffer(c, "| // ", 0XB0);

}

void renderEncounterSplashScreen()
{
    COORD c;
    c.X = g_Console.getConsoleSize().X / 2;
    c.Y = g_Console.getConsoleSize().Y / 2;
    g_Console.writeToBuffer(c, "Wild Elebeasts Appears!");
}


void renderMenu()
{
    COORD c;
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 80; j++)
        {
            c.X = j; c.Y = i;
                g_Console.writeToBuffer(c, " ", 0xC2);
        }
    }
    string name1 = jeff.getMname(0), level1 = to_string(jeff.getMlvl(0)), hp1 = to_string(jeff.getMhealth(0)), atk1 = to_string(jeff.getMattack(0)), def1 = to_string(jeff.getMdefense(0)), spd1 = to_string(jeff.getMspeed(0)),
        name2 = jeff.getMname(1), level2 = to_string(jeff.getMlvl(1)), hp2 = to_string(jeff.getMhealth(1)), atk2 = to_string(jeff.getMattack(1)), def2 = to_string(jeff.getMdefense(1)), spd2 = to_string(jeff.getMspeed(1)),
        name3 = jeff.getMname(2), level3 = to_string(jeff.getMlvl(2)), hp3 = to_string(jeff.getMhealth(2)), atk3 = to_string(jeff.getMattack(2)), def3 = to_string(jeff.getMdefense(2)), spd3 = to_string(jeff.getMspeed(2)),
        name4 = jeff.getMname(3), level4 = to_string(jeff.getMlvl(3)), hp4 = to_string(jeff.getMhealth(3)), atk4 = to_string(jeff.getMattack(3)), def4 = to_string(jeff.getMdefense(3)), spd4 = to_string(jeff.getMspeed(3)),
        name5 = jeff.getMname(4), level5 = to_string(jeff.getMlvl(4)), hp5 = to_string(jeff.getMhealth(4)), atk5 = to_string(jeff.getMattack(4)), def5 = to_string(jeff.getMdefense(4)), spd5 = to_string(jeff.getMspeed(4)),
        name6 = jeff.getMname(5), level6 = to_string(jeff.getMlvl(5)), hp6 = to_string(jeff.getMhealth(5)), atk6 = to_string(jeff.getMattack(5)), def6 = to_string(jeff.getMdefense(5)), spd6 = to_string(jeff.getMspeed(5));
    c.X = 1; c.Y = 1;
    g_Console.writeToBuffer(c, "This is the pause menu", 0xC0);
    c.Y += 2;
    g_Console.writeToBuffer(c, "Ele-beast 1:      Lv:   HP:   Atk:   Def:  Spd: ", 0xC0); c.X += 12;
    g_Console.writeToBuffer(c, name1, 0xC0); c.X += 9; g_Console.writeToBuffer(c, level1, 0xC0); c.X += 6; g_Console.writeToBuffer(c, hp1, 0xC0); c.X += 7; g_Console.writeToBuffer(c, atk1, 0xC0); c.X += 7;
    g_Console.writeToBuffer(c, def1, 0xC0); c.X += 6; g_Console.writeToBuffer(c, spd1, 0xC0); c.X = 1;
    c.Y += 2;
    g_Console.writeToBuffer(c, "Ele-beast 2:      Lv:   HP:   Atk:   Def:  Spd: : ", 0xC0); c.X += 12;
    g_Console.writeToBuffer(c, name2, 0xC0); c.X += 9; g_Console.writeToBuffer(c, level2, 0xC0); c.X += 6; g_Console.writeToBuffer(c, hp2, 0xC0); c.X += 7; g_Console.writeToBuffer(c, atk2, 0xC0); c.X += 7;
    g_Console.writeToBuffer(c, def2, 0xC0); c.X += 6; g_Console.writeToBuffer(c, spd2, 0xC0); c.X = 1;
    c.Y += 2;
    g_Console.writeToBuffer(c, "Ele-beast 3:      Lv:   HP:   Atk:   Def:  Spd: : ", 0xC0); c.X += 12;
    g_Console.writeToBuffer(c, name3, 0xC0); c.X += 9; g_Console.writeToBuffer(c, level3, 0xC0); c.X += 6; g_Console.writeToBuffer(c, hp3, 0xC0); c.X += 7; g_Console.writeToBuffer(c, atk3, 0xC0); c.X += 7;
    g_Console.writeToBuffer(c, def3, 0xC0); c.X += 6; g_Console.writeToBuffer(c, spd3, 0xC0); c.X = 1;
    c.Y += 2;
    g_Console.writeToBuffer(c, "Ele-beast 4:      Lv:   HP:   Atk:   Def:  Spd: : ", 0xC0); c.X += 12;
    g_Console.writeToBuffer(c, name4, 0xC0); c.X += 9; g_Console.writeToBuffer(c, level4, 0xC0); c.X += 6; g_Console.writeToBuffer(c, hp4, 0xC0); c.X += 7; g_Console.writeToBuffer(c, atk4, 0xC0); c.X += 7;
    g_Console.writeToBuffer(c, def4, 0xC0); c.X += 6; g_Console.writeToBuffer(c, spd4, 0xC0); c.X = 1;
    c.Y += 2;
    g_Console.writeToBuffer(c, "Ele-beast 5:      Lv:   HP:   Atk:   Def:  Spd: : ", 0xC0); c.X += 12;
    g_Console.writeToBuffer(c, name5, 0xC0); c.X += 9; g_Console.writeToBuffer(c, level5, 0xC0); c.X += 6; g_Console.writeToBuffer(c, hp5, 0xC0); c.X += 7; g_Console.writeToBuffer(c, atk5, 0xC0); c.X += 7;
    g_Console.writeToBuffer(c, def1, 0xC0); c.X += 6; g_Console.writeToBuffer(c, spd1, 0xC0); c.X = 1;
    c.Y += 2;
    g_Console.writeToBuffer(c, "Ele-beast 6:      Lv:   HP:   Atk:   Def:  Spd: : ", 0xC0); c.X += 12;
    g_Console.writeToBuffer(c, name6, 0xC0); c.X += 9; g_Console.writeToBuffer(c, level6, 0xC0); c.X += 6; g_Console.writeToBuffer(c, hp6, 0xC0); c.X += 7; g_Console.writeToBuffer(c, atk6, 0xC0); c.X += 7;
    g_Console.writeToBuffer(c, def6, 0xC0); c.X += 6; g_Console.writeToBuffer(c, spd6, 0xC0); c.X = 1;
    c.Y += 3; c.X += 28;
    g_Console.writeToBuffer(c, "Press F to EXIT PAUSE MENU.", 0xC0);
    c.Y++;
    g_Console.writeToBuffer(c, "Press 'ESC' to EXIT THE GAME.", 0xC0);
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
    c.X = 0; c.Y = 13; 
    g_Console.writeToBuffer(c, "Welcome to the world of ele-beasts! Adventure and challenges await during your ", 0xB0); c.Y++;
    g_Console.writeToBuffer(c, "journey. When you start, you will be prompted to select a starting ele-beast to", 0xB0); c.Y++;
    g_Console.writeToBuffer(c, "accompany you in your travels. Fight and catch other ele-beasts to make yours ", 0xB0); c.Y++;
    g_Console.writeToBuffer(c, "stronger, and defeat the two mysterious ele-beast in your home town area to", 0xB0); c.Y++;
    g_Console.writeToBuffer(c, "free yourself and explore the rest of the world.", 0xB0); c.Y++;
    c.X = 19; c.Y = 21; g_Console.writeToBuffer(c, "Press [ENTER] to start your adventure!", 0xB0);
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
    for (int i = 0; i < K_COUNT; ++i)
    {
        ss.str("");
        switch (i)
        {
        case K_UP: key = "W";
            break;
        case K_DOWN: key = "S";
            break;
        case K_LEFT: key = "A";
            break;
        case K_RIGHT: key = "D";
            break;
        case K_Q: key = "Q";
            break;
        case K_F: key = "F";
            break;
        case K_ENTER: key = "Enter";
            break;
        default: continue;
        }
        if (g_skKeyEvent[i].keyDown)
            ss << key << " pressed";
        else if (g_skKeyEvent[i].keyReleased)
            ss << key << " released";
        else
            ss << key << " not pressed";

        COORD c = { startPos.X, startPos.Y + i };
        g_Console.writeToBuffer(c, ss.str(), 0x17);
    }

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



