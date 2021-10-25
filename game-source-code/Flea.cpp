#include "Flea.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Mushroom.h"

Flea::Flea()
{
    //ctor
    this->LoadTexture();
    this->LoadSprite();

    float randomx = (rand() % 780);

    this->flea.setPosition(randomx,0);

}

Flea::~Flea()
{
    //dtor
}

void Flea::update(sf::RenderTarget* target)
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

 void Flea::SpawnMushroomWithFlea(std::vector<std::shared_ptr<Mushroom>>& Mush)
 {

     float randomvalue = (rand() % 100);
     int Length=Mush.size();

     if(randomvalue<2&&flea.getGlobalBounds().top<680)
     {

         //Mushroom* Tempmush=nullptr;

        //Tempmush=new Mushroom(flea.getGlobalBounds().left, flea.getGlobalBounds().top);
        Mush.push_back(std::make_shared<Mushroom>(flea.getGlobalBounds().left, flea.getGlobalBounds().top));


     for(int j=0; j<Length-1; j++)//Makes sure dropped mushrooms dont intersect
        {
            if(Mush.at(Length)->GetMushroomPosition().intersects(Mush.at(j)->GetMushroomPosition()))
            {
                Mush.pop_back();
                break;
            }

        }
     }

 }

void Flea::setFleaPosition(float x, float y){

    flea.setPosition(x,y);
}
