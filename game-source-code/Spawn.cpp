#include "Spawn.h"
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

Spawn::Spawn()
{
    //Laser controls
    MaxLaserCount=10;
    MinLaserDelay=15.f;
    LaserDelay=MinLaserDelay;

    //Mushroom controls
    MushCount=40;

    //Flea controls
    MinFleaTimeDelay=100;
    FleaTimeDelay=0;

    //Bomb controls
    MinBombTimeDelay=300;
    BombTimeDelay=0;
}

//Creates the laser beams
void Spawn::ShootLaser(std::vector <std::shared_ptr<Laser>>& laser,std::shared_ptr<BugBlaster>& BugB)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&laser.size()<MaxLaserCount&&LaserDelay>MinLaserDelay)
    {
        sf::FloatRect BugPos=BugB->GetBugPosition();
        laser.push_back(std::make_shared<Laser>(BugPos));
        LaserDelay=0.f;
    }
    LaserDelay++;
}


void Spawn::SpawnFlea(std::vector <std::shared_ptr<Flea>>& flea,std::vector <std::shared_ptr<Mushroom>>& Mush)
{
    int PlayerAreaMush=0;
    int randomchance=rand()%100;

    for(int k=0; k<Mush.size(); k++)
    {
        if(Mush.at(k)->inPlayerArea())
            PlayerAreaMush++;
    }

    if(PlayerAreaMush<7&&MinFleaTimeDelay<FleaTimeDelay&&randomchance<2)//If all requirements are met than a 2% chance to spawn
    {
    flea.push_back(std::make_shared<Flea>());
    FleaTimeDelay=0;
    }
    FleaTimeDelay++;

}

void Spawn::SpawnBomb(std::vector <std::shared_ptr<Bomb>>& bomb,std::vector <std::shared_ptr<Mushroom>>& Mush)
{

    int randomnum=rand()%100;
    float randomy = 20+(rand() % 21)*20;
    float randomx = 20+(rand() % 38)*20;


    if(randomnum<2&&MinBombTimeDelay<BombTimeDelay&&bomb.size()<4)
    {
    bomb.push_back(std::make_shared<Bomb>(randomx,randomy));
    BombTimeDelay=0;


    for(int i=0;i<bomb.size()-1;i++)//Makes sure random previous bombs dont intersect with new bomb
    {
    for(int j=0; j<Mush.size(); j++)//Makes sure random mushrooms dont intersect with bomb

        {
            if(Mush.at(j)->GetMushroomPosition().intersects(bomb.at(bomb.size()-1)->GetBombPosition())||bomb.at(i)->GetBombPosition().intersects(bomb.at(bomb.size()-1)->GetBombPosition()))
            {
                bomb.pop_back();

                BombTimeDelay=MinBombTimeDelay;
                break;
            }
        }
    }
    }

    BombTimeDelay++;
}

 void Spawn::SpawnMushroomField(std::vector <std::shared_ptr<Mushroom>>& Mush,std::shared_ptr<BugBlaster>& BugB)
 {
     for(int i=0; i<MushCount; i++)
    {
        Mush.push_back(std::make_shared<Mushroom>());

        for(int j=0; j<i-1; j++)//Makes sure random mushrooms dont intersect, if they intersect creates new mushroom
        {
            if(Mush.at(j)->GetMushroomPosition().intersects(Mush.at(i)->GetMushroomPosition())||Mush.at(i)->MushroomInPlayerStart(BugB))
            {
                Mush.pop_back();
                i--;
            }

        }

    }

 }
