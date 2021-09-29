


#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "GameEngine.h"

// Define some constants
//const int gameWidth = 800;
//const int gameHeight = 600;

int main()
{

    // Create the window of the application
    Game game;

    while (game.IsRunning())
    {
    //window.draw(pauseMessage);
    //Update

    game.update();

    //Render
     game.render();


    }

     return 0;
    }





