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
#include "Bomb.h"


CollisionControl::CollisionControl(std::shared_ptr<BugBlaster>& BugB,std::vector <std::shared_ptr<Laser>>& laser,std::vector<std::shared_ptr<Mushroom>>& Mush,std::vector<std::shared_ptr<Flea>>& flea,
                                   std::vector<std::shared_ptr<Centipede>>& centipedes,std::vector<std::shared_ptr<Bomb>>& bomb)
{
    LostLife=false;

    LaserCollision(laser);


    //programme crashes this order
    CentipedeCollisionMushroom(centipedes,Mush);
    CollisionCentipedeBomb(centipedes,bomb);
    //CentipedeSelfCollision(centipedes);
    LaserCollisionCentipedes(laser, centipedes,Mush);
   // CentipedeCollisionMushroom(centipedes,Mush);

    LaserCollisionMushrooms(laser,Mush);

    CollisionMushPlayer(BugB,Mush);
    CollisionBugCentipede(BugB,centipedes);

   // CentipedeSelfCollision(centipedes);

    CollisionBugFlea(BugB,flea);
    CollisionLaserFlea(laser,flea);
    CollisionFleaEdge(flea);

    //Bomb
     CollisionLaserBomb(laser,Mush,flea,centipedes,bomb);
}

CollisionControl::CollisionControl()
{
    LostLife=false;
}

void CollisionControl::LaserCollision(std::vector <std::shared_ptr<Laser>>& laser)
{

    for(int i=0; i<laser.size(); i++)
    {
        //sf::FloatRect LaserPos=this->laser.at(i).GetLaserPosition();

        if(laser.at(i)->GetLaserPosition().top<=0.f)
        {
            laser.erase(laser.begin()+i);

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


                if(j!=length){

                    centipedes.push_back(std::make_shared<Centipede>(temp));

                }

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
                //if(laser.size()>0){
                //    i--;
                //}
                Mush.at(k)->HealthLoss();
                if(Mush.at(k)->IsHealthZero()==true)
                {
                    Mush.erase(Mush.begin()+k);


                }
                 leave=true;
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

void CollisionControl::CollisionLaserBomb(std::vector <std::shared_ptr<Laser>>& laser,std::vector<std::shared_ptr<Mushroom>>& Mush,std::vector<std::shared_ptr<Flea>>& flea,std::vector<std::shared_ptr<Centipede>>& centipedes,std::vector<std::shared_ptr<Bomb>>& bomb)
{
     for(int i=0; i<laser.size(); i++)
    {
        bool leave=false;
        for(int k=0; k<bomb.size(); k++)
        {
            if(laser.at(i)->GetLaserPosition().intersects(bomb.at(k)->GetBombPosition()))
            {
                laser.erase(laser.begin()+i);
                BombCentipede(bomb,centipedes,k);
                BombMushroom(bomb,Mush,k);
                BombFlea(bomb,flea,k);
                bomb.erase(bomb.begin()+k);
                leave=true;
                break;

            }
        }
    if(leave)break;
    }


}

void CollisionControl::BombMushroom(std::vector<std::shared_ptr<Bomb>>& bomb,std::vector<std::shared_ptr<Mushroom>>& Mush,int k)
{
    for(int i=0;i<Mush.size();i++)
    {
        if(Mush.at(i)->GetMushroomPosition().left+Mush.at(i)->GetMushroomPosition().width>bomb.at(k)->GetBombPosition().left-40
           &&Mush.at(i)->GetMushroomPosition().left<bomb.at(k)->GetBombPosition().left+bomb.at(k)->GetBombPosition().width+40
           &&Mush.at(i)->GetMushroomPosition().top+Mush.at(i)->GetMushroomPosition().height>bomb.at(k)->GetBombPosition().top-40
           &&Mush.at(i)->GetMushroomPosition().top<bomb.at(k)->GetBombPosition().top+bomb.at(k)->GetBombPosition().height+40)
        {
            Mush.erase(Mush.begin()+i);
            i--;
        }
    }

}
void CollisionControl::BombFlea(std::vector<std::shared_ptr<Bomb>>& bomb,std::vector<std::shared_ptr<Flea>>& flea,int k)
{
    for(int i=0;i<flea.size();i++)
    {
        if(flea.at(i)->GetFleaPosition().left+flea.at(i)->GetFleaPosition().width>bomb.at(k)->GetBombPosition().left-40
           &&flea.at(i)->GetFleaPosition().left<bomb.at(k)->GetBombPosition().left+bomb.at(k)->GetBombPosition().width+40
           &&flea.at(i)->GetFleaPosition().top+flea.at(i)->GetFleaPosition().height>bomb.at(k)->GetBombPosition().top-40
           &&flea.at(i)->GetFleaPosition().top<bomb.at(k)->GetBombPosition().top+bomb.at(k)->GetBombPosition().height+40)
        {
            flea.erase(flea.begin()+i);
            i--;
        }
    }

}

void CollisionControl::BombCentipede(std::vector<std::shared_ptr<Bomb>>& bomb,std::vector<std::shared_ptr<Centipede>>& centipedes,int i)
{
    for(int k=0; k<centipedes.size(); k++)
    {
        for(int j=0; j<centipedes.at(k)->getSize(); j++)
        {
            if(centipedes.at(k)->getCentipede().at(j).GetSegmentPosition().left+centipedes.at(k)->getCentipede().at(j).GetSegmentPosition().width>bomb.at(i)->GetBombPosition().left-40
           &&centipedes.at(k)->getCentipede().at(j).GetSegmentPosition().left<bomb.at(i)->GetBombPosition().left+bomb.at(i)->GetBombPosition().width+40
           &&centipedes.at(k)->getCentipede().at(j).GetSegmentPosition().top+centipedes.at(k)->getCentipede().at(j).GetSegmentPosition().height>bomb.at(i)->GetBombPosition().top-40
           &&centipedes.at(k)->getCentipede().at(j).GetSegmentPosition().top<bomb.at(i)->GetBombPosition().top+bomb.at(i)->GetBombPosition().height+40)
            {

                auto temp=centipedes.at(k)->getNewCentipede(j);
                auto length=centipedes.at(k)->getSize()-1;
                centipedes.at(k)->fixedHead(j);


                if(j!=length)
                {

                    centipedes.push_back(std::make_shared<Centipede>(temp));

                }


            }
        }

    }

}

void CollisionControl::CollisionCentipedeBomb(std::vector<std::shared_ptr<Centipede>>& centipedes,std::vector<std::shared_ptr<Bomb>>& bomb)
{

    for(int k=0; k<centipedes.size(); k++)
    {

        for(int i=0; i<bomb.size(); i++)
        {
            if(bomb.at(i)->GetBombPosition().intersects(centipedes.at(k)->GetCentipedeHeadPosition()))
            {
                centipedes.at(k)->setHitMushroom();
            }
        }

    }

}

//Centipede collisons
//void CollisionControl::CentipedeSelfCollision(std::vector<std::shared_ptr<Centipede>>& centipedes)
//{
//
//    for(int k=0; k<centipedes.size(); k++)
//    {
//        bool breakMiddleLoop=false;
//        for(int i=k+1; i<centipedes.size(); i++)
//        {
//            for(int j=0; j<centipedes.at(i)->getSize();j++){
//
//                if(centipedes.at(k)->GetCentipedeHeadPosition().intersects(centipedes.at(i)->getCentipede().at(j).GetSegmentPosition())){
//                    centipedes.at(k)->setHitMushroom();
//                    if(j==0&&i<centipedes.size()-1){
//                        centipedes.at(i)->setHitMushroom();
//                        i++;
//                    }
//                  //  breakMiddleLoop=true;
//                    break;
//                }
//
//
//
//            }
//           // if(breakMiddleLoop){
//            //    breakMiddleLoop=false;
//            //    break;
//           // }
//
//        }
//
//    }
//}
