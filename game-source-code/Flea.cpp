#include "Flea.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

Flea::Flea()
{
    //ctor
    this->LoadTexture();
    this->LoadSprite();

    float randomx = (rand() % 800);

    this->flea.setPosition(randomx,0);

}

Flea::~Flea()
{
    //dtor
}

void Flea::update()
{
    this->FleaMove();

}

void Flea::render(sf::RenderTarget* target)
{
    target->draw(this->flea);
}

void Flea::LoadTexture()
{
    if(!this->fleatext.loadFromFile("resources/Flea.png"))
    {
        std::cout << "Flea.cpp Failed to load Sprite" <<std::endl;
    }

}

void Flea::LoadSprite()
{
    this->flea.setTexture(this->fleatext);

    //Scaling image
    this->flea.scale(0.1f,0.1f);

    MoveSpeed=5.f;
}

sf::FloatRect Flea::GetFleaPosition()
{
    sf::FloatRect FleaBounds=flea.getGlobalBounds();
    return FleaBounds;
}

void Flea::FleaMove()
{
    this->flea.move(0.f,this->MoveSpeed);//Downwards
}

bool Flea::CollisionBottomWindow(sf::RenderTarget* target)
{
     if(flea.getGlobalBounds().top>=target->getSize().y)
    {
       return true;
    }

return false;
}
