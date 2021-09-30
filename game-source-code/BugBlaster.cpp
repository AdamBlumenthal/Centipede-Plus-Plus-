
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "BugBlaster.h"
//#include "Laser.h"


//Constructor
BugBlaster::BugBlaster(float x,float y)
{
    this->bug.setPosition(x,y);//Set position if BugBlaster

    this->createVarible();
    this->createBug();
}

//Destructor
BugBlaster::~BugBlaster()
{

}
sf::RectangleShape BugBlaster::getBug(){
    return bug;
    }
void BugBlaster::createVarible()
{
    this->MoveSpeed=5.f;
}

void BugBlaster::createBug()
{
    this->bug.setFillColor(sf::Color::Green);
    this->bug.setSize(sf::Vector2f(25.f,25.f));
}

//functions

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

 void BugBlaster::WindowCollision(sf::RenderTarget* target)
 {

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

 sf::FloatRect BugBlaster::GetBugPosition()
 {
     sf::FloatRect BugBounds=bug.getGlobalBounds();
     return BugBounds;
 }




void BugBlaster::update(sf::RenderTarget* target)
{

    //Key movements
    this->KeyInput();

    //collision
    this->WindowCollision(target);
}

void BugBlaster::render(sf::RenderTarget* target)
{
    target->draw(this->bug);
}

