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


class CollisionControl
{
    public:
        CollisionControl(BugBlaster BugB,std::vector <Laser> laser,std::vector <Mushroom*> Mush,std::vector <Flea*> flea,std::vector<Centipede> centipedes);
        virtual ~CollisionControl();

       void CollisonLaserFlea(std::vector <Flea*> flea,std::vector <Laser> laser);


    private:

};

#endif // COLLISIONCONTROL_H
