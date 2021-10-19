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


CollisionControl::CollisionControl(BugBlaster BugB,std::vector <std::shared_ptr<Laser>>& laser,std::vector <Mushroom*> Mush,std::vector <Flea*> flea,
                                   std::vector<std::shared_ptr<Centipede>>& centipedes)
{
    LaserCollision(laser);
    LaserCollisionCentipedes(laser, centipedes);
}

CollisionControl::~CollisionControl()
{
    //dtor
}

void CollisionControl::LaserCollision(std::vector <std::shared_ptr<Laser>>& laser)
{

    for(int i=0; i<laser.size(); i++)
    {
        //sf::FloatRect LaserPos=this->laser.at(i).GetLaserPosition();

        if(laser.at(i)->GetLaserPosition().top<=0.f)
        {
            laser.erase(laser.begin()+i);
           std::cout<<laser.size()<<std::endl;
            break;
        }

    }
}

void CollisionControl::LaserCollisionCentipedes(std::vector <std::shared_ptr<Laser>>& laser, std::vector<std::shared_ptr<Centipede>>& centipedes){
for(int k=0;k<centipedes.size();k++){
    bool leave=false;
    for(int i=0;i<laser.size();i++){
        for(int j=0;j<centipedes.at(k)->getSize();j++){
            if(laser.at(i)->GetLaserPosition().intersects(centipedes.at(k)->getCentipede().at(j).GetSegmentPosition())){
                laser.erase(laser.begin()+i);
                leave=true;
                //MakeMushroom(centipedes.at(k)->getCentipede().at(j));

                auto temp=centipedes.at(k)->getNewCentipede(j);
                auto length=centipedes.at(k)->getSize()-1;

                centipedes.at(k)->fixedHead(j);

                //if(centipede.getSize()==0)
                   // std::cerr<<"There"<<std::endl;
                if(j!=length){
                   // std::cerr<<"There"<<std::endl;
                    centipedes.push_back(std::make_shared<Centipede>(temp));

                }
                //std::cerr<<j<<std::endl;
                break;
            }
        }
        if(leave)break;
}
}
}
//Laser collisions

//Bug collisions

//Centipede collisons

//Flea collisons
//void CollisionControl::CollisonLaserFlea()
//{
//    bool leave=false;
//
//    for(int i=0; i<laser.size(); i++)
//    {
//        for(int j=0; j<flea.size(); j++)
//        {
//            if(laser.at(i).GetLaserPosition().intersects(flea.at(j)->GetFleaPosition()))
//            {
//                flea.erase(flea.begin()+j);
//            }
//
//        }
//    }
//}


