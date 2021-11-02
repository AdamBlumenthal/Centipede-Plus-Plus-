#ifndef COLLISIONCONTROL_H
#define COLLISIONCONTROL_H
#include <SFML/Audio.hpp>
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
/** \file CollisionControl.h
    \brief Checks all collisions between objects in the game
 */

/** \class CollisionControl
    \brief A class that receives all game objects and checks them for collisions and updates them accordingly
 */
class CollisionControl
{
    public:
         /** \brief The Parameritised Constructor for the Collision Control class which then checks all collisions
        \param BugB - Referenced to the shared pointer for BugBlaster object
        \param laser - Reference to vector of shared pointers to all lasers created
        \param Mush -Reference to vector of shared pointers to all mushrooms objects
        \param centipedes - Reference to the vector of shared pointers to all centipedes objects
        \param flea -Reference to vector of shared pointers to all flea objects
        \param bombs - Reference to the vector of shared pointers to all bomb objects

    */
        CollisionControl(std::shared_ptr<BugBlaster>& BugB,std::vector <std::shared_ptr<Laser>>& laser,std::vector<std::shared_ptr<Mushroom>>& Mush,std::vector<std::shared_ptr<Flea>>& flea,std::vector<std::shared_ptr<Centipede>>& centipedes,std::vector<std::shared_ptr<Bomb>>& bomb);
           /** \brief The Default  Constructor for the Collision Control class
            */
        CollisionControl();

       //void CollisionControl2(std::vector <std::shared_ptr<Laser>>& laser,std::vector<std::shared_ptr<Mushroom>>& Mush,std::vector<std::shared_ptr<Flea>>& flea,std::vector<std::shared_ptr<Centipede>>& centipedes);
        /** \brief Checks whether the laser reaches the top of the window and then destroys it
        \param laser - Reference to vector of shared pointers to all lasers create
    */
        void LaserCollision(std::vector <std::shared_ptr<Laser>>& laser);
         /** \brief Checks whether the laser collides with a segment of a centipede and then creates a new centipede, a mushroom and destroys deleted segment and laser
        \param laser - Reference to vector of shared pointers to all lasers create
        \param centipedes - Reference to the vector of shared pointers to all centipedes objects
        \param Mush -Reference to vector of shared pointers to all mushrooms objects
        */
        void LaserCollisionCentipedes(std::vector <std::shared_ptr<Laser>>& laser, std::vector<std::shared_ptr<Centipede>>& centipede,std::vector<std::shared_ptr<Mushroom>>& Mush);
           /** \brief Checks whether the Bugblaster collides with a mushroom and then stops the Bubblaster interesection a mushroom
        \param BugB - Referenced to the shared pointer for BugBlaster object
        \param Mush -Reference to vector of shared pointers to all mushrooms objects
        */
        void CollisionMushPlayer(std::shared_ptr<BugBlaster>& BugB, std::vector<std::shared_ptr<Mushroom>>& Mush);
         /** \brief Checks whether the Bugblaster collides with a segment of a centipede and then sets lostLife true if a collision occurs
            \param BugB - Referenced to the shared pointer for BugBlaster object
            \param centipedes - Reference to the vector of shared pointers to all centipedes objects
        */
        void CollisionBugCentipede(std::shared_ptr<BugBlaster>& BugB,std::vector<std::shared_ptr<Centipede>>& centipedes);
           /** \brief Checks whether the laser collides with a mushroom destroys laser involved with collisions and then decreases health for a mushroom and destroys the mushroom if it runs out of health
        \param laser - Reference to vector of shared pointers to all lasers create
        \param Mush -Reference to vector of shared pointers to all mushrooms objects
        */
        void LaserCollisionMushrooms(std::vector <std::shared_ptr<Laser>>& laser,std::vector<std::shared_ptr<Mushroom>>& Mush);
         /** \brief Checks whether the centipede collides collides with a mushroom whereby it will call the function setHitMushroom for the centipede
         \param centipedes - Reference to the vector of shared pointers to all centipedes objects
        \param Mush -Reference to vector of shared pointers to all mushrooms objects
        */
        void CentipedeCollisionMushroom(std::vector<std::shared_ptr<Centipede>>& centipedes,std::vector<std::shared_ptr<Mushroom>>& Mush);
         /** \brief Checks whether the Bugblaster collides with a flea and then sets lostLife true if a collision occurs
            \param BugB - Referenced to the shared pointer for BugBlaster object
            \param flea -Reference to vector of shared pointers to all flea objects
        */
        void CollisionBugFlea(std::shared_ptr<BugBlaster>& BugB,std::vector<std::shared_ptr<Flea>>& flea);
        /** \brief Checks whether the laser collides with a flea destroys laser involved with collisions and flea
        \param laser - Reference to vector of shared pointers to all lasers create
        \param flea -Reference to vector of shared pointers to all flea objects
        */
        void CollisionLaserFlea(std::vector<std::shared_ptr<Laser>>& laser,std::vector<std::shared_ptr<Flea>>& flea);
          /** \brief Checks whether the flea reaches the bottom of the playing area and then destroys it
        \param flea -Reference to vector of shared pointers to all flea objects
        */
        void CollisionFleaEdge(std::vector<std::shared_ptr<Flea>>& flea);


        //Bomb
         /** \brief Checks for all collisions that can occur due to a laser colliding with a bomb - calls other funcions for other objects hit by a bomb. It will destroy the bomb and the laser
        \param laser - Reference to vector of shared pointers to all lasers created
        \param Mush -Reference to vector of shared pointers to all mushrooms objects
        \param centipedes - Reference to the vector of shared pointers to all centipedes objects
        \param flea -Reference to vector of shared pointers to all flea objects
        \param bombs - Reference to the vector of shared pointers to all bomb objects

    */
        void CollisionLaserBomb(std::vector <std::shared_ptr<Laser>>& laser,std::vector<std::shared_ptr<Mushroom>>& Mush,std::vector<std::shared_ptr<Flea>>& flea,std::vector<std::shared_ptr<Centipede>>& centipedes,std::vector<std::shared_ptr<Bomb>>& bomb);
           /** \brief Checks for collision between mushrooms in the bomb blast radius. It will destroy the mushrooms in the radius
        \param Mush -Reference to vector of shared pointers to all mushrooms objects
        \param bombs - Reference to the vector of shared pointers to all bomb objects

    */
        void BombMushroom(std::vector<std::shared_ptr<Bomb>>& bomb,std::vector<std::shared_ptr<Mushroom>>& Mush,int k);
           /** \brief Checks for collision between fleas in the bomb blast radius. It will destroy the fleas in the radius

        \param flea -Reference to vector of shared pointers to all flea objects
        \param bombs - Reference to the vector of shared pointers to all bomb objects

    */
        void BombFlea(std::vector<std::shared_ptr<Bomb>>& bomb,std::vector<std::shared_ptr<Flea>>& flea,int k);
           /** \brief Checks for collision between centipedes in the bomb blast radius. It will destroy the centipede segments in the radius and create new centipedes if necessary. Does not spawn a mushroom as bomb destroys it

        \param centipedes - Reference to the vector of shared pointers to all centipedes objects
        \param bombs - Reference to the vector of shared pointers to all bomb objects

    */
        void BombCentipede(std::vector<std::shared_ptr<Bomb>>& bomb,std::vector<std::shared_ptr<Centipede>>& centipedes,int i);
             /** \brief Checks whether the centipede  collides with a bomb whereby it will call the function setHitMushroom for the centipede
         \param centipedes - Reference to the vector of shared pointers to all centipedes objects
          \param bombs - Reference to the vector of shared pointers to all bomb objects
        */
        void CollisionCentipedeBomb(std::vector<std::shared_ptr<Centipede>>& centipedes,std::vector<std::shared_ptr<Bomb>>& bomb);
            /** \brief Checks whether the centipede  collides with another centipede whereby it will call the function setHitMushroom for the centipede
         \param centipedes - Reference to the vector of shared pointers to all centipedes objects
        */
        void CentipedeSelfCollision(std::vector<std::shared_ptr<Centipede>>& centipedes);


        /** \brief Returns the boolean lost life
         \return The boolean lost life is returned
        */
        bool DidPlayerLoseLife();

    private:
        bool LostLife;
        //std::shared_ptr<BugBlaster> tem;

};

#endif // COLLISIONCONTROL_H

