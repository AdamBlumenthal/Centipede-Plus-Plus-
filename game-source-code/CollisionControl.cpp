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


CollisionControl::CollisionControl(std::shared_ptr<BugBlaster>& BugB,std::vector <std::shared_ptr<Laser>>& laser,std::vector<std::shared_ptr<Mushroom>>& Mush,std::vector<std::shared_ptr<Flea>>& flea,
                                   std::vector<std::shared_ptr<Centipede>>& centipedes)
{
    LostLife=false;

    LaserCollision(laser);


    //programme crashes this order
    CentipedeCollisionMushroom(centipedes,Mush);
    LaserCollisionCentipedes(laser, centipedes,Mush);
   // CentipedeCollisionMushroom(centipedes,Mush);

    LaserCollisionMushrooms(laser,Mush);

    CollisionMushPlayer(BugB,Mush);
    CollisionBugCentipede(BugB,centipedes);


    CollisionBugFlea(BugB,flea);
    CollisionLaserFlea(laser,flea);
    CollisionFleaEdge(flea);
}

CollisionControl::CollisionControl()
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

void CollisionControl::LaserCollisionCentipedes(std::vector <std::shared_ptr<Laser>>& laser, std::vector<std::shared_ptr<Centipede>>& centipedes,
                                                std::vector<std::shared_ptr<Mushroom>>& Mush){
for(int k=0;k<centipedes.size();k++){
    bool leave=false;
    for(int i=0;i<laser.size();i++){
        for(int j=0;j<centipedes.at(k)->getSize();j++){
            if(laser.at(i)->GetLaserPosition().intersects(centipedes.at(k)->getCentipede().at(j).GetSegmentPosition())){
                laser.erase(laser.begin()+i);
                leave=true;



                auto temp=centipedes.at(k)->getNewCentipede(j);
                auto length=centipedes.at(k)->getSize()-1;
                 Mush.push_back(std::make_shared<Mushroom>(centipedes.at(k)->getCentipede().at(j).GetSegmentPosition().left,centipedes.at(k)->getCentipede().at(j).GetSegmentPosition().top));
                centipedes.at(k)->fixedHead(j);

                //if(centipede.getSize()==0)
                   // std::cerr<<"There"<<std::endl;
                if(j!=length){
                   // std::cerr<<"There"<<std::endl;
                    centipedes.push_back(std::make_shared<Centipede>(temp));
                  //  k++;

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

void CollisionControl::LaserCollisionMushrooms(std::vector <std::shared_ptr<Laser>>& laser,std::vector<std::shared_ptr<Mushroom>>& Mush)
{

    bool leave=false;
    for(int i=0; i<laser.size(); i++)
    {
        for(int k=0; k<Mush.size(); k++)
        {
            if(laser.at(i)->GetLaserPosition().intersects(Mush.at(k)->GetMushroomPosition()))
            {

                laser.erase(laser.begin()+i);
                leave=true;
                Mush.at(k)->HealthLoss();
                if(Mush.at(k)->IsHealthZero()==true)
                {
                    Mush.erase(Mush.begin()+k);


                }
                break;
            }
        }
        if(leave)
        {
            break;
        }
    }


}

//Bug collisions

void CollisionControl::CollisionMushPlayer(std::shared_ptr<BugBlaster>& BugB, std::vector<std::shared_ptr<Mushroom>>& Mush)
{

   for(int k=0; k<Mush.size(); k++)//Checks all mushrooms
    {

        if(BugB->GetBugPosition().intersects(Mush.at(k)->GetMushroomPosition()))
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)||sf::Keyboard::isKeyPressed(sf::Keyboard::Right))//Left and right
            {
                if(BugB->GetBugPosition().left>=Mush.at(k)->GetMushroomPosition().left-BugB->GetBugPosition().width
                        && BugB->GetBugPosition().left+BugB->GetBugPosition().width>Mush.at(k)->GetMushroomPosition().left+Mush.at(k)->GetMushroomPosition().width)//Checks if on the right and not on the left
                {
                    BugB->SetPosition(Mush.at(k)->GetMushroomPosition().left+Mush.at(k)->GetMushroomPosition().width,BugB->GetBugPosition().top);
                }
                else if(BugB->GetBugPosition().left+BugB->GetBugPosition().width>=Mush.at(k)->GetMushroomPosition().left)//Checks if on the left
                {
                    BugB->SetPosition(Mush.at(k)->GetMushroomPosition().left-BugB->GetBugPosition().width,BugB->GetBugPosition().top);
                }
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)||sf::Keyboard::isKeyPressed(sf::Keyboard::Down))//Up and down
            {
                if (BugB->GetBugPosition().top<Mush.at(k)->GetMushroomPosition().top+BugB->GetBugPosition().height
                        &&BugB->GetBugPosition().top>Mush.at(k)->GetMushroomPosition().top)//Checks if below and not above
                {
                    BugB->SetPosition(BugB->GetBugPosition().left,Mush.at(k)->GetMushroomPosition().top+Mush.at(k)->GetMushroomPosition().height);
                }
                else if(BugB->GetBugPosition().top+BugB->GetBugPosition().height>Mush.at(k)->GetMushroomPosition().top)//Checks if above
                {
                    BugB->SetPosition(BugB->GetBugPosition().left,Mush.at(k)->GetMushroomPosition().top-BugB->GetBugPosition().height);
                }
            }

        }

    }

}


//Centipede collisons
void CollisionControl::CentipedeCollisionMushroom(std::vector<std::shared_ptr<Centipede>>& centipedes,std::vector<std::shared_ptr<Mushroom>>& Mush)
{

    for(int k=0; k<centipedes.size(); k++)
    {

        for(int i=0; i<Mush.size(); i++)
        {
            if(Mush.at(i)->GetMushroomPosition().intersects(centipedes.at(k)->GetCentipedeHeadPosition()))
            {
                centipedes.at(k)->setHitMushroom();
            }
        }

    }
}

//Flea collisons

void CollisionControl::CollisionBugFlea(std::shared_ptr<BugBlaster>& BugB,std::vector<std::shared_ptr<Flea>>& flea)
{
    for(int h=0; h<flea.size(); h++)
        {
            if(BugB->GetBugPosition().intersects(flea.at(h)->GetFleaPosition()))
            {
                LostLife=true;
                flea.erase(flea.begin()+h);
                break;
            }
        }

}

void CollisionControl::CollisionLaserFlea(std::vector<std::shared_ptr<Laser>>& laser,std::vector<std::shared_ptr<Flea>>& flea)
{

    for(int i=0; i<laser.size(); i++)
    {
        for(int j=0; j<flea.size(); j++)
        {
            if(laser.at(i)->GetLaserPosition().intersects(flea.at(j)->GetFleaPosition()))
            {

                flea.erase(flea.begin()+j);

            }


            }

        }
}

void CollisionControl::CollisionFleaEdge(std::vector<std::shared_ptr<Flea>>& flea)
{
     for(int h=0; h<flea.size(); h++)
        {

            if(flea.at(h)->GetFleaPosition().top>=600)
            {
                flea.erase(flea.begin()+h);
            }
        }
}

void CollisionControl::CollisionBugCentipede(std::shared_ptr<BugBlaster>& BugB,std::vector<std::shared_ptr<Centipede>>& centipedes)
{
    for(int k=0; k<centipedes.size(); k++)
    {
        bool leave=false;
        for(int j=0; j<centipedes.at(k)->getSize(); j++)
        {
            if(BugB->GetBugPosition().intersects(centipedes.at(k)->getCentipede().at(j).GetSegmentPosition()))
            {
                //std::cout<<"Dead"<<std::endl;
                LostLife=true;
                leave=true;
                break;
            }
        }
        if(leave)break;

    }
}

bool CollisionControl::DidPlayerLoseLife()
{
    return LostLife;
}
