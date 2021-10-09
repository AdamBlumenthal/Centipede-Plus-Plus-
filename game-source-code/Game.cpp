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




int Game::numberOfCentipedes=12;
//int Game::
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

    this->MaxLengthCentipede=12;
    lvlBegin=false;
    currentSegments=MaxLengthCentipede;

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
    this->LaserCollisionCentipede();
    this->LaserCollisionHeads();
    this->LaserCollisionMushrooms();

    if(currentSegments==0)
    {
        MaxLengthCentipede--;
        currentSegments=MaxLengthCentipede;
        lvlBegin=true;
    }

    if(lvlBegin)
    {
        this->MakeCentipede();
        //(MaxLengthCentipede<numberOfCentipedes)
        this->MakeHeads();
        lvlBegin=false;
    }
//=======
    //this->LaserCollisionCentipede();

//>>>>>>> Zunaid

    if (CurrentLasers>=1)
    {
        for(int i=0; i<CurrentLasers; i++)
        {
            this->laser.at(i).update(this->window);
        }

    }
    for(int i=segments.size()-1; i>=0; i--)
    {
        this->segments.at(i).update(this->window);

    }
    for(int i=0; i<heads.size(); i++)
    {
        this->heads.at(i).update(this->window);
        //    std::cout<<"Update "+i<<std::endl;
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
            lvlBegin=true;
        }
    }
    else
    {


        //Render Objects in space
        this->BugB.render(this->window);
       // for(int i=segments.size()-1; i>=0; i--)
      //  {
         //   this->segments.at(i).render(this->window);
       // }
       for(auto i:segments){
        i.render(this->window);
       }
        for(int i=0; i<heads.size(); i++){
                this->heads.at(i).render(this->window);
        }

        for(int i=0;i<=MushCount;i++)
        {
            Mush.at(i)->render(this->window);
        }

        for(auto i:this->laser)
        {
            i.render(this->window);
        }


    this->window->display();
}
}
//Creates the laser beams
void Game::ShootLaser()
{

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&laser.size()<=this->MaxLaserCount&&LaserDelay>=MaxLaserDelay)
    {
        sf::FloatRect BugPos=this->BugB.GetBugPosition();
        this->laser.push_back(Laser(BugPos));
        CurrentLasers++;
        //Game::MaxLengthCentipede
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

void Game:: LaserCollisionCentipede()
{
    bool leave=false;
    for(int i=0; i<CurrentLasers; i++)
    {
        for(int j=0; j<segments.size(); j++)
        {
            if(this->laser.at(i).GetLaserPosition().intersects(this->segments.at(j).GetSegmentPosition()))
            {
                //std::cout<<"Number of segments:"+segments.size()<<std::endl;
                this->laser.erase(this->laser.begin()+i);
                //std::cout<<j+"Hit"<<std::endl;
                leave=true;
                this->segments.erase(this->segments.begin()+j);
                CurrentLasers--;
                currentSegments--;
                if(j>0&&segments.begin()+j<=segments.end())
                    segments.at(j-1).makeHead();
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



void Game::LaserCollisionMushrooms(){

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
                        }
        }
            if(leave){
            //std::cout<<"hwoosooodsdofosdsdgsd"<<std::endl;
            break;
        }
    }


}



void Game:: LaserCollisionHeads()
{
    bool leave=false;
    for(int i=0; i<CurrentLasers; i++)
    {
        for(int j=0; j<heads.size(); j++)
        {
            if(this->laser.at(i).GetLaserPosition().intersects(this->heads.at(j).GetSegmentPosition()))
            {
                 this->laser.erase(this->laser.begin()+i);
                //std::cout<<j+"Hit"<<std::endl;
                leave=true;
                this->heads.erase(this->heads.begin()+j);
                CurrentLasers--;
                currentSegments--;
                 break;
            }
        }
            if(leave){
            std::cout<<"hwoosooodsdofosdsdgsd"<<std::endl;
            break;
        }
    }


}


                //std::cout<<"Number of segments:"+segments.size()<<std::endl

//Makes a centipede. Segments that follow each other
void Game::MakeCentipede()
{
    //int length=10;
    float delay=25.f;
    float pos;
    for(int i=0; i<MaxLengthCentipede; i++)
    {
        pos=i*delay;

        this->segments.push_back(Segment(pos));

    }
    segments.at(MaxLengthCentipede-1).makeHead();

}
void Game::MakeHeads()
{
    //int length=10;
    float delay=10.f;
    float pos;
    for(int i=0; i<(numberOfCentipedes-MaxLengthCentipede); i++)
    {
        pos=i*delay+200.f;

        this->heads.push_back(Segment(pos,delay));
        heads.at(i).makeHead();
        std::cout<<"twice"<<std::endl;
    }
    // std::cout<<"Test"<<std::endl;
}
