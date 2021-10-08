#include "Mushroom.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

Mushroom::Mushroom()
{
    this->LoadTexture();
    this->LoadSprite();

    float randomy = (rand() % 600);
    float randomx = (rand() % 800);

    this->mush.setPosition(randomx,randomy);

}

Mushroom::~Mushroom()
{
    //dtor
}

void Mushroom::update(sf::RenderTarget* target)
{

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
    this->mush.scale(0.01f,0.01f);

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


