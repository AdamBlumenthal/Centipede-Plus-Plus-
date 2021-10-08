#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "GameEngine.h"
#include "BugBlaster.h"
#include "Laser.h"
#include <vector>
#include "CentipedeSegment.h"
#include "Mushroom.h"




//Constructor
Game::Game()
{
    this->createVarible();
    this->createWindow();

}

//Destructor
Game::~Game()
{
    this->window=nullptr;
}

//Checks
const bool Game::IsRunning() const
{

    return this->window->isOpen();
}

//Functions

//Creates Window
void Game::createWindow()
{
    this->videomode.height=600;
    this->videomode.width=800;
    this->window=new sf::RenderWindow(videomode, "SFML Centipede", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);



};
//Gives values to private variables.
void Game::createVarible()
{
    this->MaxLaserCount=10;
    this->MaxLaserDelay=10.f;
    this->LaserDelay=this->MaxLaserDelay;
    this->CurrentLasers=0;
    this->MushCount=20;
    //Load font
    if (!this->font.loadFromFile("resources/arial.ttf"))
        std::cout << "ERROR::GAME::Failed to load font" << "\n";

    this->StartSplashText.setFont(this->font);
    this->StartSplashText.setCharacterSize(25);
    this->StartSplashText.setFillColor(sf::Color::White);
    this->StartSplashText.setString("SFML Centipede: Press Enter to start,Press Escape to Quit\n Arrow Keys to move\n Space to Shoot");
    this->StartSplashText.setPosition(0,250);

    Mushroom* Mush=NULL;

   for(int i=0;i<=MushCount;i++)
        {
            Mush=new Mushroom();
            this->Mush.push_back(Mush);

        }

}

//Checks if window closed by clicking escape
void Game::UpdateEvent()
{
    while(this->window->pollEvent(this->event))
    {
        switch(this->event.type)
        {

        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if(this->event.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        }
    }
}


//Updates everything in game
void Game::update()
{


    this->UpdateEvent();
    this->BugB.update(this->window);
    this->UpdateEvent();
    this->ShootLaser();
    this->LaserCollision();
    //this->LaserCollisionCentipede();
    this->LaserCollisionMushrooms();
    this->MakeCentipede();

    if (CurrentLasers>=1)
    {
        for(int i=0; i<CurrentLasers; i++)
        {
            this->laser.at(i).update(this->window);
        }

    }
    for(int i=9; i>=0; i--)
    {
        this->segments.at(i).update(this->window);

    }


}
//Renders Objects and window
void Game::render()
{
    this->window->clear(sf::Color::Black);
    //Splash Screen displayed
    if(start)
    {
        this->window->draw(this->StartSplashText);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            start=false;
        }
    }
    else
    {


        //Render Objects in space
        this->BugB.render(this->window);

        for(int i=0;i<=MushCount;i++)
        {
            Mush.at(i)->render(this->window);
        }


        for(int i=9; i>=0; i--)
        {
            this->segments.at(i).render(this->window);
        }
        for(auto i:this->laser)
        {
            i.render(this->window);
        }
    }

    this->window->display();
}
//Creates the laser beams
void Game::ShootLaser()
{

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&laser.size()<=this->MaxLaserCount&&LaserDelay>=MaxLaserDelay)
    {
        sf::FloatRect BugPos=this->BugB.GetBugPosition();
        this->laser.push_back(Laser(BugPos));
        CurrentLasers++;
        LaserDelay=0.f;
    }
    LaserDelay++;
}

//Checks if Laser collides with objects such as edge of screen or centipede segments
void Game::LaserCollision()
{

    for(int i=0; i<CurrentLasers; i++)
    {
        sf::FloatRect LaserPos=this->laser.at(i).GetLaserPosition();

        if(LaserPos.top<=0.f)
        {
            this->laser.erase(this->laser.begin()+i);
            CurrentLasers--;
            break;
        }

    }
}


void Game::LaserCollisionMushrooms()
{
    bool leave=false;
    for(int i=0; i<CurrentLasers; i++)
    {
        for(int k=0; k<=MushCount; k++)
        {
            if(this->laser.at(i).GetLaserPosition().intersects(Mush.at(k)->GetMushroomPosition()))
            {

                this->laser.erase(this->laser.begin()+i);
                CurrentLasers--;
                leave=true;
                Mush.at(k)->HealthLoss();
                if(Mush.at(k)->IsHealthZero()==true)
                {
                    Mush.erase(Mush.begin()+k);
                    MushCount--;

                }
                break;

                //seg.getFillColor()==sf::Color::Green
                //  std::cout<<j<<std::endl;
            }
        }
        if(leave){
            std::cout<<"hwoosooodsdofosdsdgsd"<<std::endl;
            break;
        }
    }


}


//Makes a centipede. Segments that follow each other
void Game::MakeCentipede()
{
    int length=10;
    float delay=25.f;
    float pos;
    for(int i=0; i<length; i++)
    {
        pos=i*delay;

        this->segments.push_back(Segment(pos));

    }

}

