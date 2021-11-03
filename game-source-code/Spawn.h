#ifndef SPAWN_H
#define SPAWN_H
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "BugBlaster.h"
#include "Laser.h"
#include <vector>
#include "CentipedeSegment.h"
#include "Mushroom.h"
#include "Flea.h"
#include "Centipede.h"
#include "Bomb.h"
#include <memory>
/** \file Spawn.h
    \brief Creates new objects in the game
 */

/** \class Spawn
    \brief A class that receives all game objects and checks them for collisions and updates them accordingly
 */


class Spawn
{
    public:
        /** \brief The default Constructor for the Spawn class which creats a spawn
    */
        Spawn();
        /** \brief Creates a laser when spacebar is pressed
        \param laser - Reference to vector of shared pointers to all lasers created
        \param BugB - Referenced to the shared pointer for BugBlaster object
    */
        void ShootLaser(std::vector <std::shared_ptr<Laser>>& laser,std::shared_ptr<BugBlaster>& BugB);
        /** \brief Creates a Flea object at the top of the screen
            \param flea -Reference to vector of shared pointers to all flea objects
            \param Mush -Reference to vector of shared pointers to all mushrooms objects
        */
        void SpawnFlea(std::vector<std::shared_ptr<Flea>>& flea,std::vector <std::shared_ptr<Mushroom>>& Mush);
        /** \brief Creates a vector full of randomly placed Mushroom Objects
            \param Mush -Reference to vector of shared pointers to all mushrooms objects
            \param BugB - Referenced to the shared pointer for BugBlaster object
        */
        void SpawnMushroomField(std::vector<std::shared_ptr<Mushroom>>& Mush,std::shared_ptr<BugBlaster>& BugB);
        /** \brief Creates a Bomb Ojects based on a random chance
            \param bombs - Reference to the vector of shared pointers to all bomb objects
            \param Mush -Reference to vector of shared pointers to all mushrooms objects
        */
        void SpawnBomb(std::vector<std::shared_ptr<Bomb>>& bomb,std::vector <std::shared_ptr<Mushroom>>& Mush);



    private:

    //Laser Varibles
    int MaxLaserCount;
    float MinLaserDelay;
    float LaserDelay;

    //Mushroom starting value
    int MushCount;

    //Flea varibles
    int MinFleaTimeDelay;
    int FleaTimeDelay;

    //Bomb varibles
    int MinBombTimeDelay;
    int BombTimeDelay;
};

#endif // SPAWN_H
