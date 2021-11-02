#include <SFML/Graphics.hpp>
#include "BugBlaster.h"

//Constructor
BugBlaster::BugBlaster(float x,float y)
{
    bug.setPosition(x,y);//Set position of BugBlaster
    createVarible();
    createBug();
}
//Get class object
sf::RectangleShape BugBlaster::getBug()
{
    return bug;
}
//Initialise Variables
void BugBlaster::createVarible()
{
    MoveSpeed=5.f;
}
//Gives bug characteristics
void BugBlaster::createBug()
{
    bug.setFillColor(sf::Color::Green);
    bug.setSize(sf::Vector2f(20.f,20.f));
}

//functions
//Checks for user input that will move the bug
void BugBlaster::KeyInputResults(Movement movement)
{
    //Key movements

    if(movement==Movement::Up)
    {
        bug.move(0.f,-MoveSpeed);//Up
    }
    else if(movement==Movement::Down)
    {
        bug.move(0.f,MoveSpeed);//Down
    }
    if(movement==Movement::Left)
    {
        bug.move(-MoveSpeed,0.f);//Left
    }
    else if(movement==Movement::Right)
    {
        bug.move(MoveSpeed,0.f);//Right
    }


}
//Checks if the bug collision with its defined bounds. Edge of screen and maximum height give by the developers
void BugBlaster::WindowCollision(sf::RenderTarget* target)
{
//Creates lower box for BugBlaster
    if(bug.getGlobalBounds().left<=0.f)
    {
        bug.setPosition(0.f,bug.getGlobalBounds().top);
    }
    else if(bug.getGlobalBounds().left+bug.getGlobalBounds().width>=target->getSize().x)
    {
        bug.setPosition(target->getSize().x-bug.getGlobalBounds().width,bug.getGlobalBounds().top);
    }

    if(bug.getGlobalBounds().top<=450.f)
    {
        bug.setPosition(bug.getGlobalBounds().left,450.f);
    }
    else if(bug.getGlobalBounds().top+bug.getGlobalBounds().height>=target->getSize().y-100.f)
    {
        bug.setPosition(bug.getGlobalBounds().left,target->getSize().y-bug.getGlobalBounds().height-100.f);
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
    auto movement=BugBlasterGetInputs();

    KeyInputResults(movement);

    //collision
    WindowCollision(target);
}
void BugBlaster::render(sf::RenderTarget* target)
{
    //Renders to window
    target->draw(bug);
}

void BugBlaster::SetPosition(float x,float y)
{
    bug.setPosition(x,y);
}

 Movement BugBlaster::BugBlasterGetInputs()
{


    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        return Movement::Up;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
       return Movement::Down;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
      return Movement::Left;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
      return Movement::Right;
    }


}
