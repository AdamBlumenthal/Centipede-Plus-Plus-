#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "BugBlaster.h"

//Constructor
BugBlaster::BugBlaster(float x,float y)
{
    this->bug.setPosition(x,y);//Set position of BugBlaster
    this->createVarible();
    this->createBug();
}

//Destructor
BugBlaster::~BugBlaster()
{

}
//Get class object
sf::RectangleShape BugBlaster::getBug()
{
    return bug;
}
//Initialise Variables
void BugBlaster::createVarible()
{
    this->MoveSpeed=5.f;
}
//Gives bug characteristics
void BugBlaster::createBug()
{
    this->bug.setFillColor(sf::Color::Green);
    this->bug.setSize(sf::Vector2f(25.f,25.f));
}

//functions
//Checks for user input that will move the bug
void BugBlaster::KeyInput()
{
    //Key movements

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        this->bug.move(0.f,-this->MoveSpeed);//Up
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        this->bug.move(0.f,this->MoveSpeed);//Down
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        this->bug.move(-this->MoveSpeed,0.f);//Left
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        this->bug.move(this->MoveSpeed,0.f);//Right
    }


}
//Checks if the bug collision with its defined bounds. Edge of screen and maximum height give by the developers
void BugBlaster::WindowCollision(sf::RenderTarget* target)
{
//Creates lower box for BugBlaster
    if(bug.getGlobalBounds().left<=0.f)
    {
        this->bug.setPosition(0.f,bug.getGlobalBounds().top);
    }
    else if(bug.getGlobalBounds().left+bug.getGlobalBounds().width>=target->getSize().x)
    {
        this->bug.setPosition(target->getSize().x-bug.getGlobalBounds().width,bug.getGlobalBounds().top);
    }

    if(bug.getGlobalBounds().top<=450.f)
    {
        this->bug.setPosition(bug.getGlobalBounds().left,450.f);
    }
    else if(bug.getGlobalBounds().top+bug.getGlobalBounds().height>=target->getSize().y)
    {
        this->bug.setPosition(bug.getGlobalBounds().left,target->getSize().y-bug.getGlobalBounds().height);
    }


}
//Get's the position of the bug
sf::FloatRect BugBlaster::GetBugPosition()
{
    sf::FloatRect BugBounds=bug.getGlobalBounds();
    return BugBounds;
}

//Updates bug based on user input
void BugBlaster::update(sf::RenderTarget* target)
{

    //Key movements
    this->KeyInput();

    //collision
    this->WindowCollision(target);
}
void BugBlaster::render(sf::RenderTarget* target)
{
    //Renders to window
    target->draw(this->bug);
}

