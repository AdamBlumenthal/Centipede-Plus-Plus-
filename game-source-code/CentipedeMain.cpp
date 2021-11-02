/** \file CentipedeMain.cpp
    \brief Contains the main function
 */
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "GameEngine.h"
#include <time.h>

/** \fn int main()
 *  \brief This function contains the game loop of updates and drawing to the window
 *
 *  \return The application exit code: 0 for successful completion; a negative number to indicate an error
 *
 */

int main()
{
    srand (time(NULL));

    //Game object
    Game game;
    //While loop to continuosly run and update the game until user closes it
    while (game.IsRunning())
    {
        //Update
        game.update();
        //Render
        game.render();
    }

    return 0;
}





