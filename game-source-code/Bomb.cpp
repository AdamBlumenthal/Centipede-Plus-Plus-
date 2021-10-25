#include "Bomb.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>


Bomb::Bomb(float x, float y)
{
    this->LoadTexture();
    this->LoadSprite();

    this->bomb.setPosition(x,y);

}

Bomb::~Bomb()
{
    //dtor
}

void Bomb::update(sf::RenderTarget* target)
{

}

void Bomb::render(sf::RenderTarget* target)
{
    target->draw(this->bomb);
}

void Bomb::LoadTexture()
{
    if(!this->bombtext.loadFromFile("resources/DDTBomb.png"))
    {
        std::cout << "Bomb.cpp Failed to load Sprite" <<std::endl;
    }

}

void Bomb::LoadSprite()
{
    this->bomb.setTexture(this->bombtext);

    //Scaling image
    this->bomb.scale(0.03f,0.03f);
}

sf::FloatRect Bomb::GetBombPosition()
{
    sf::FloatRect BombBounds=bomb.getGlobalBounds();
    return BombBounds;
}

void Bomb::RescaleBomb()
{
    std::cout<<"Testing";
    this->bomb.scale(1.f,1.f);
}
