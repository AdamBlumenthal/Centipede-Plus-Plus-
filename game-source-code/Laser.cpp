#include "Laser.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "BugBlaster.h"

//Constructor
Laser::Laser(sf::FloatRect BugBounds)
{
    laser.setPosition(BugBounds.left+BugBounds.width/2,BugBounds.top);
    createVarible();
    createLaser();

}

//Get class object for shape
sf::RectangleShape Laser::getLaser()
{
    return laser;
}
//Sets movement speed
void Laser::createVarible()
{
    MoveSpeed=10.f;
}
void Laser::createLaser()
{
    //Sets laser parameters
    laser.setFillColor(sf::Color::Yellow);
    laser.setSize(sf::Vector2f(1.f,20.f));
}

//functions
//Moves the laser in a direction
void Laser::LaserMove()
{
    laser.move(0.f,-this->MoveSpeed);//Upwards
}
void Laser::SetPositionLaser(sf::FloatRect BugBounds)
{
    //Start position set at the top of BugBlaster
    laser.setPosition(BugBounds.left+BugBounds.width/2-2.5,BugBounds.top);

}

//Gets the position of the laser
sf::FloatRect Laser::GetLaserPosition()
{
    sf::FloatRect LaserBounds=laser.getGlobalBounds();
    return LaserBounds;
}


//Updates laser
void Laser::update()
{
    //Changes in movement
    LaserMove();

}
//renders laser
void Laser::render(std::shared_ptr<sf::RenderWindow> target)
{
    target->draw(laser);
}


