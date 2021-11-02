#include "Mushroom.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
//Will set a known startpoint
Mushroom::Mushroom(float x, float y)
{
    LoadTexture();
    LoadSprite();

    mush.setPosition(x,y);

}
//Will set a random startpoint
Mushroom::Mushroom()
{
    LoadTexture();
    LoadSprite();

    float randomy = 20+(rand() % 28)*20;
    float randomx =20 + (rand() % 38)*20;

    mush.setPosition(randomx,randomy);

}


void Mushroom::render(std::shared_ptr<sf::RenderWindow> target)
{
    target->draw(mush);
}

void Mushroom::LoadTexture()
{
    if(!mushtext.loadFromFile("resources/Mushroomsprite1.png"))
    {
        std::cout << "Mushroom.cpp Failed to load Sprite" <<std::endl;
    }

}

void Mushroom::LoadSprite()
{
    mush.setTexture(mushtext);

    //Scaling image
    mush.scale(0.009f,0.009f);

    //Set Health start
    MushHealth=4;
}
//Called when hit by Laser
void Mushroom::HealthLoss()
{
    MushHealth--;
}

sf::FloatRect Mushroom::GetMushroomPosition()
{
    sf::FloatRect MushroomBounds=mush.getGlobalBounds();
    return MushroomBounds;
}

sf::Sprite Mushroom::getMushroom()
{
    return mush;
}

//Checks if Health is Zero
 bool Mushroom::IsHealthZero()
 {
     if(MushHealth<=0)
     {
         return true;
     }
     else
     {
         return false;
     }
 }
//Used to count mushrooms in Player area
 bool Mushroom::inPlayerArea()
{
    if(mush.getPosition().y>450)
        return true;
        else
            return false;
}
//Does mushroom intersect with the PLayer
bool Mushroom::MushroomInPlayerStart(std::shared_ptr<BugBlaster> Bug)
{
    if(mush.getGlobalBounds().intersects(Bug->GetBugPosition()))
        return true;

    else
        return false;
}

