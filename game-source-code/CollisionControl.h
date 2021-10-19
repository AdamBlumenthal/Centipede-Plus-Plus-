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
#include <memory>

class CollisionControl
{
    public:
        CollisionControl(BugBlaster BugB,std::vector <std::shared_ptr<Laser>>& laser,std::vector <Mushroom*> Mush,std::vector <Flea*> flea,std::vector<std::shared_ptr<Centipede>>& centipedes);
        virtual ~CollisionControl();

       void LaserCollision(std::vector <std::shared_ptr<Laser>>& laser);
        void LaserCollisionCentipedes(std::vector <std::shared_ptr<Laser>>& laser, std::vector<std::shared_ptr<Centipede>>& centipede);

    private:

};

#endif // COLLISIONCONTROL_H
