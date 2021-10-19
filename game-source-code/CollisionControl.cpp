#include "CollisionControl.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "GameEngine.h"
#include "BugBlaster.h"
#include "Laser.h"
#include <vector>
#include "CentipedeSegment.h"
#include "Mushroom.h"
#include "Flea.h"
#include "Centipede.h"


CollisionControl::CollisionControl(BugBlaster BugB,std::vector <Laser> laser,std::vector <Mushroom*> Mush,std::vector <Flea*> flea,std::vector<Centipede> centipedes)
{
    //ctor
    CollisonLaserFlea(flea,laser);
}

CollisionControl::~CollisionControl()
{
    //dtor
}

//Laser collisions

//Bug collisions

//Centipede collisons

//Flea collisons
void CollisionControl::CollisonLaserFlea(std::vector <Flea*> flea,std::vector <Laser> laser)
{
    bool leave=false;

    for(int i=0; i<laser.size(); i++)
    {
        for(int j=0; j<flea.size(); j++)
        {
            if(laser.at(i).GetLaserPosition().intersects(flea.at(j)->GetFleaPosition()))
            {
                flea.erase(flea.begin()+j);
            }

        }
    }
}


