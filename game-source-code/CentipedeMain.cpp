#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "GameEngine.h"



int main()
{
    //Game object
    Game game;
    //While loop to continuosly run and update the game until user closes it
    while (game.IsRunning())
    {
        //Update
        //game.update();
        //Render
        game.render();
    }

    return 0;
}





