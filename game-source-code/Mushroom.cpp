#include "Mushroom.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

Mushroom::Mushroom(float x, float y)
{
    this->LoadTexture();
    this->LoadSprite();

    this->mush.setPosition(x,y);

}

Mushroom::Mushroom()
{
    this->LoadTexture();
    this->LoadSprite();

    float randomy = 20+(rand() % 28)*20;
    float randomx =20 + (rand() % 38)*20;

    this->mush.setPosition(randomx,randomy);

}



Mushroom::~Mushroom()
{
    //dtor
}

void Mushroom::render(sf::RenderTarget* target)
{
    target->draw(this->mush);
}

void Mushroom::LoadTexture()
{
    if(!this->mushtext.loadFromFile("resources/Mushroomsprite1.png"))
    {
        std::cout << "Mushroom.cpp Failed to load Sprite" <<std::endl;
    }

}

void Mushroom::LoadSprite()
{
    this->mush.setTexture(this->mushtext);

    //Scaling image
    this->mush.scale(0.009f,0.009f);

    //Set Health start
    MushHealth=4;
}

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

 bool Mushroom::inPlayerArea()
{
    if(mush.getPosition().y>450)
        return true;
        else
            return false;
}

