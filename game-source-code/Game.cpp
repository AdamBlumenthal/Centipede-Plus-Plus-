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
#include "Flea.h"
#include "Centipede.h"
#include "CollisionControl.h"
#include "Bomb.h"
#include "Spawn.h"
#include <memory>



int Game::numberOfCentipedes=12;
//int Game::
//Constructor
Game::Game()
{
    createVarible();
    createWindow();

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
    videomode.height=700;
    videomode.width=800;
    window=std::make_shared<sf::RenderWindow>(videomode, "SFML Centipede", sf::Style::Titlebar | sf::Style::Close);
    window->setFramerateLimit(60);
};
//Gives values to private variables.
void Game::createVarible()
{
    BugB=std::make_shared<BugBlaster>();


    //Spawn Control
    spawnobj=Spawn();

    //Game controls
    Lives=3;
    lvlBegin=false;
    start=true;
    gameOver=true;
    pause=false;


    //Load font
    if (!font.loadFromFile("resources/arial.ttf"))
    {
        std::cout << "ERROR::GAME::Failed to load font" << "\n";
    }

    StartSplashText.setFont(font);
    StartSplashText.setCharacterSize(25);
    StartSplashText.setFillColor(sf::Color::White);
    StartSplashText.setPosition(0,250);

    //Lives text
    LivesText.setFont(font);
    LivesText.setCharacterSize(25);
    LivesText.setFillColor(sf::Color::White);
    LivesText.setPosition(200,650);

    BotLine.setFillColor(sf::Color::Cyan);
    BotLine.setSize(sf::Vector2f(800.f,1.f));
    BotLine.setPosition(0,600);


    //Create random mushrooms
    spawnobj.SpawnMushroomField(Mush,BugB);


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
    UpdateEvent();
    if(!gameOver){
    if(!pause){


    if(lvlBegin)
    {

        centipedes.clear();
        centipedes.push_back(std::make_shared<Centipede>(12,2.f, 0.f));

        lvlBegin=false;

    }


    BugB->update(window);
    spawnobj.ShootLaser(laser,BugB);
    spawnobj.SpawnFlea(flea,Mush);
    spawnobj.SpawnBomb(bomb,Mush);
    if(centipedes.size()>0){



    centipedes.erase(remove_if(centipedes.begin(),centipedes.end(),[](std::shared_ptr<Centipede> cent)->bool{return cent->isEmpty();}),centipedes.end());
       // SelfCollision();
    for(int i=0;i<centipedes.size();i++){
            centipedes.at(i)->update(window);

        }

    }
    else{
        gameOver=true;
        StartSplashText.setString("Game Over - You Win\n Well Played \n Press Enter to restart \n Press Escape to Quit\n Arrow Keys to move\n Space to Shoot\n Tab to Pause");
    }



        for(int i=0; i<laser.size(); i++)
        {
           laser.at(i)->update();
        }


        for(int i=0; i<flea.size(); i++)
        {
            flea.at(i)->update();
            flea.at(i)->SpawnMushroomWithFlea(Mush);
        }


    Collision=CollisionControl(BugB,laser,Mush,flea,centipedes,bomb);

    }

    if(Collision.DidPlayerLoseLife()){
        Lives--;
        centipedes.clear();
        if(Lives==0){
                gameOver=true;
                this->StartSplashText.setString("Game Over - You Lose\n Better Luck Next Time \n Press Enter to restart \n Press Escape to Quit\n Arrow Keys to move\n Space to Shoot\n Tab to Pause");
        }
        else {
                lvlBegin=true;
        }
        }

}
}
//Renders Objects and window
void Game::render()
{
    this->window->clear(sf::Color::Black);
    //Splash Screen displayed
    if(start)
    {
         this->StartSplashText.setString("SFML Centipede: Press Enter to start,Press Escape to Quit\n Arrow Keys to move\n Space to Shoot\n Tab to Pause");

        this->window->draw(StartSplashText);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            start=false;
            lvlBegin=true;
            gameOver=false;
        }
    }
    else if(gameOver){

        this->window->draw(this->StartSplashText);
        Mush.clear();
        centipedes.clear();
        flea.clear();
        laser.clear();
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {

        bomb.clear();
          Mush.clear();
          createVarible();
          start=false;
            gameOver=false;
            lvlBegin=true;
        }
    }
    else
    {

        //update();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
            if(pause)
                pause=false;
            else
                pause=true;
        }
        //Display lives remaining

        LivesText.setString("Lives Remaining:"+std::to_string(Lives));
        this->window->draw(LivesText);
        this->window->draw(BotLine);


        //Render Objects in space

        BugB->render(this->window);

       for(auto i:centipedes)
        i->render(this->window);
        for(int i=0; i<Mush.size(); i++)
        {
            Mush.at(i)->render(this->window);
        }

        for(auto i:laser)
        {
            i->render(this->window);
        }


        for(int i=0; i<flea.size(); i++)
        {
            flea.at(i)->render(this->window);
        }
        for(int i=0; i<bomb.size(); i++)
        {
            bomb.at(i)->render(this->window);
        }

    }
    this->window->display();


}



