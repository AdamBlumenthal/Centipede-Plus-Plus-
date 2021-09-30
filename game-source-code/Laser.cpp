#include "Laser.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

#include "BugBlaster.h"

Laser::Laser(sf::FloatRect BugBounds)
{
    this->laser.setPosition(BugBounds.left+BugBounds.width/2-2.5,BugBounds.top);

    this->createVarible();
    this->createLaser();

}

Laser::~Laser()
{
    //Destructor

}

void Laser::createVarible()
{
    this->MoveSpeed=10.f;
}

void Laser::createLaser()
{
    this->laser.setFillColor(sf::Color::Yellow);
    this->laser.setSize(sf::Vector2f(5.f,20.f));
}

//functions
void Laser::LaserMove()
{
    this->laser.move(0.f,-this->MoveSpeed);//Upwards
}

void Laser::SetPositionLaser(sf::FloatRect BugBounds)
{
    laser.setPosition(BugBounds.left+BugBounds.width/2-2.5,BugBounds.top);

}

sf::FloatRect Laser::GetLaserPosition()
 {
     sf::FloatRect LaserBounds=laser.getGlobalBounds();
     return LaserBounds;
 }



void Laser::update(sf::RenderTarget* target)
{

    this->LaserMove();

}

void Laser::render(sf::RenderTarget* target)
{
    target->draw(this->laser);
}


