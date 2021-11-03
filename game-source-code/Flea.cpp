#include "Flea.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Mushroom.h"

//Construnctor
Flea::Flea()
{

    LoadTexture();
    LoadSprite();

    float randomx = 20+(rand() % 38)*20;

    flea.setPosition(randomx,0);

}


void Flea::update()
{
    FleaMove();
}

void Flea::render(std::shared_ptr<sf::RenderWindow> target)
{
    target->draw(flea);
}

void Flea::LoadTexture()
{
    if(!fleatext.loadFromFile("resources/Flea.png"))
    {
        std::cout << "Flea.cpp Failed to load Sprite" <<std::endl;
    }

}

void Flea::LoadSprite()
{
    flea.setTexture(fleatext);

    //Scaling image
    flea.scale(0.1f,0.1f);

    MoveSpeed=5.f;
}

sf::FloatRect Flea::GetFleaPosition()
{
    sf::FloatRect FleaBounds=flea.getGlobalBounds();
    return FleaBounds;
}

void Flea::FleaMove()
{
    flea.move(0.f,MoveSpeed);//Downwards
}

bool Flea::CollisionBottomWindow(std::shared_ptr<sf::RenderWindow> target)
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

     if(randomvalue<2&&flea.getGlobalBounds().top<600)
     {
        Mush.push_back(std::make_shared<Mushroom>(flea.getGlobalBounds().left, flea.getGlobalBounds().top));


     for(int j=0; j<Length; j++)//Makes sure dropped mushrooms dont intersect
        {
            if(Mush.at(Length)->GetMushroomPosition().intersects(Mush.at(j)->GetMushroomPosition()))
            {
                Mush.pop_back();
                break;
            }

        }
     }

 }

 //Used for Testing Flea
void Flea::setFleaPosition(float x, float y){

    flea.setPosition(x,y);
}
