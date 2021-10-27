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
#include "CollisionControl.h"
#include "Bomb.h"
#include <memory>

class CollisionControl
{
    public:
        CollisionControl(std::shared_ptr<BugBlaster>& BugB,std::vector <std::shared_ptr<Laser>>& laser,std::vector<std::shared_ptr<Mushroom>>& Mush,std::vector<std::shared_ptr<Flea>>& flea,std::vector<std::shared_ptr<Centipede>>& centipedes,std::vector<std::shared_ptr<Bomb>>& bomb);
        CollisionControl();
       //void CollisionControl2(std::vector <std::shared_ptr<Laser>>& laser,std::vector<std::shared_ptr<Mushroom>>& Mush,std::vector<std::shared_ptr<Flea>>& flea,std::vector<std::shared_ptr<Centipede>>& centipedes);

        void LaserCollision(std::vector <std::shared_ptr<Laser>>& laser);
        void LaserCollisionCentipedes(std::vector <std::shared_ptr<Laser>>& laser, std::vector<std::shared_ptr<Centipede>>& centipede,std::vector<std::shared_ptr<Mushroom>>& Mush);

        void CollisionMushPlayer(std::shared_ptr<BugBlaster>& BugB, std::vector<std::shared_ptr<Mushroom>>& Mush);
        void CollisionBugCentipede(std::shared_ptr<BugBlaster>& BugB,std::vector<std::shared_ptr<Centipede>>& centipedes);

        void LaserCollisionMushrooms(std::vector <std::shared_ptr<Laser>>& laser,std::vector<std::shared_ptr<Mushroom>>& Mush);

        void CentipedeCollisionMushroom(std::vector<std::shared_ptr<Centipede>>& centipedes,std::vector<std::shared_ptr<Mushroom>>& Mush);

        void CollisionBugFlea(std::shared_ptr<BugBlaster>& BugB,std::vector<std::shared_ptr<Flea>>& flea);
        void CollisionLaserFlea(std::vector<std::shared_ptr<Laser>>& laser,std::vector<std::shared_ptr<Flea>>& flea);
        void CollisionFleaEdge(std::vector<std::shared_ptr<Flea>>& flea);


        //Bomb
        void CollisionLaserBomb(std::vector <std::shared_ptr<Laser>>& laser,std::vector<std::shared_ptr<Mushroom>>& Mush,std::vector<std::shared_ptr<Flea>>& flea,std::vector<std::shared_ptr<Centipede>>& centipedes,std::vector<std::shared_ptr<Bomb>>& bomb);
        void BombMushroom(std::vector<std::shared_ptr<Bomb>>& bomb,std::vector<std::shared_ptr<Mushroom>>& Mush,int k);
        void BombFlea(std::vector<std::shared_ptr<Bomb>>& bomb,std::vector<std::shared_ptr<Flea>>& flea,int k);
        void BombCentipede(std::vector<std::shared_ptr<Bomb>>& bomb,std::vector<std::shared_ptr<Centipede>>& centipedes,int i);
        void CollisionCentipedeBomb(std::vector<std::shared_ptr<Centipede>>& centipedes,std::vector<std::shared_ptr<Bomb>>& bomb);

        void CentipedeSelfCollision(std::vector<std::shared_ptr<Centipede>>& centipedes);

        //void CentipedeSelfCollision(std::vector<std::shared_ptr<Centipede>>& centipedes);

        bool DidPlayerLoseLife();

    private:
        bool LostLife;
        //std::shared_ptr<BugBlaster> tem;

};

#endif // COLLISIONCONTROL_H

