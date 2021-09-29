

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

//Function
void Game::createWindow()
{
    this->videomode.height=600;
    this->videomode.width=800;
    this->window=new sf::RenderWindow(videomode, "SFML Centipede", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);



};

void Game::createVarible()
{
    this->MaxLaserCount=10;
    this->MaxLaserDelay=10.f;
    this->LaserDelay=this->MaxLaserDelay;
    this->CurrentLasers=0;
    //Load font
	if (!this->font.loadFromFile("arial.ttf"))
		std::cout << "ERROR::GAME::Failed to load font" << "\n";

    this->StartSplashText.setFont(this->font);
	this->StartSplashText.setCharacterSize(25);
	this->StartSplashText.setFillColor(sf::Color::White);
	this->StartSplashText.setString("SFML Centipede: Press Enter to start,Press Escape to Quit\n Arrow Keys to move\n Space to Shoot");
	this->StartSplashText.setPosition(0,250);
}


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



void Game::update()
{


    this->UpdateEvent();
    //this->ShootLaser();

    this->BugB.update(this->window);

    this->UpdateEvent();
    this->ShootLaser();
    this->LaserCollision();

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
        //for(int j=0;j<20000;j++)
        //std::cout<<i<<std::endl;
    }
    // std::cout<<400000000<<std::endl;
    //this->laser.update(this->window);

}

void Game::render()
{
    this->window->clear(sf::Color::Black);
    if(start){
            this->window->draw(this->StartSplashText);
           // this->window->display();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        start=false;
    }
    }
else{


    //Render Objects in space
    this->BugB.render(this->window);
    //  this->BugB.render(this->window);
    for(int i=9; i>=0; i--)
    {
        this->segments.at(i).render(this->window);
    }
    for(auto i:this->laser)
    {
        i.render(this->window);
    }

    // this->BugB.render(this->window);
//    for(auto i:this->laser)
    //{
    //     i.render(this->window);
    // }
}

    this->window->display();
}

void Game::ShootLaser()
{
    //Time delay


    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&laser.size()<=this->MaxLaserCount&&LaserDelay>=MaxLaserDelay)
    {

        sf::FloatRect BugPos=this->BugB.GetBugPosition();
        this->laser.push_back(Laser(BugPos));
        CurrentLasers++;
        LaserDelay=0.f;

    }
    LaserDelay++;

}


void Game::LaserCollision()
{

    for(int j=0; j<segments.size(); j++)
    {
        for(int i=0; i<CurrentLasers; i++)
        {
            sf::FloatRect LaserPos=this->laser.at(i).GetLaserPosition();

            if(LaserPos.top<=0.f)
            {
                this->laser.erase(this->laser.begin()+i);
                CurrentLasers--;
            }
            else if(this->laser.at(i).GetLaserPosition().intersects(this->segments.at(j).GetSegmentPosition()))
            {
                this->laser.erase(this->laser.begin()+i);
                CurrentLasers--;
                // this->segments.erase(this->segments.begin()+j);
            }
        }
    }
}
void Game::MakeCentipede()
{
    int length=10;
    float delay=25.f;
    float pos;
    //  LaserDelay=0.f;
    for(int i=0; i<length; i++)
    {
        pos=i*delay;

        this->segments.push_back(Segment(pos));

    }

}

