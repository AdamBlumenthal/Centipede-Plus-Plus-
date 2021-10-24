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
#include "Flea.h"
#include "Centipede.h"
#include "CollisionControl.h"
#include "Bomb.h"
#include <memory>



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
    this->videomode.height=700;
    this->videomode.width=800;
    this->window=new sf::RenderWindow(videomode, "SFML Centipede", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
};
//Gives values to private variables.
void Game::createVarible()
{
    BugB=std::make_shared<BugBlaster>();

    //Laser controls

    MaxLaserCount=10;
    MaxLaserDelay=26.f;
    LaserDelay=MaxLaserDelay;
    //this->CurrentLasers=0;
    //centipedes.push_back(Centipede(0,0.f,0.f));
    MaxLengthCentipede=12;
    //Game controls
    Lives=3;
    lvlBegin=false;
    start=true;
    gameOver=false;
    centMush=false;
    pause=false;
    currentSegments=MaxLengthCentipede;


    //Mushroom controls
    this->MushCount=30;

    //Load font
    if (!this->font.loadFromFile("resources/arial.ttf"))
    {
        std::cout << "ERROR::GAME::Failed to load font" << "\n";
    }

    this->StartSplashText.setFont(this->font);
    this->StartSplashText.setCharacterSize(25);
    this->StartSplashText.setFillColor(sf::Color::White);
    this->StartSplashText.setPosition(0,250);

    //Lives text
    LivesText.setFont(this->font);
    LivesText.setCharacterSize(25);
    LivesText.setFillColor(sf::Color::White);
    LivesText.setPosition(200,650);

    BotLine.setFillColor(sf::Color::Cyan);
    BotLine.setSize(sf::Vector2f(800.f,1.f));
    BotLine.setPosition(0,600);

    //Mushroom* Tempmush=nullptr;

    for(int i=0; i<MushCount; i++)
    {
        float randomy = 21+(rand() % 560);
        float randomx = (rand() % 780);
        //Tempmush=new Mushroom(randomx,randomy);
        Mush.push_back(std::make_shared<Mushroom>(randomx,randomy));

        for(int j=0; j<i-1; j++)//Makes sure random mushrooms dont intersect, if they intersect creates new mushroom
        {
            if(Mush.at(j)->GetMushroomPosition().intersects(Mush.at(i)->GetMushroomPosition()))
            {
                Mush.pop_back();
                i--;
            }


        }

    }

    //Flea controls
    MinFleaTimeDelay=100;
    FleaTimeDelay=0;

    //Bomb controls
    MinBombTimeDelay=300;
    BombTimeDelay=0;

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

     if(currentSegments==0)
    {
        MaxLengthCentipede--;
        currentSegments=MaxLengthCentipede;
        lvlBegin=true;
    }
    if(MaxLengthCentipede==0)gameOver=true;

    if(lvlBegin)
    {


        centipedes.push_back(std::make_shared<Centipede>(12,2.f, 0.f));

        lvlBegin=false;
    }





    BugB->update(window);
    ShootLaser();
    SpawnFlea();
    SpawnBomb();
    if(centipedes.size()>0){



    centipedes.erase(remove_if(centipedes.begin(),centipedes.end(),[](std::shared_ptr<Centipede> cent)->bool{return cent->isEmpty();}),centipedes.end());
       // SelfCollision();
        for(int i=0;i<centipedes.size();i++){
            centipedes.at(i)->update(this->window);

        }

    }
    else{
        gameOver=true;
        this->StartSplashText.setString("Game Over - You Win\n Well Played \n Press Enter to restart \n Press Escape to Quit\n Arrow Keys to move\n Space to Shoot\n Tab to Pause");
    }




    if (laser.size()>=1)
    {
        for(int i=0; i<laser.size(); i++)
        {
           laser.at(i)->update(this->window);
        }


    }
    if (flea.size()>=1)
    {
        for(int i=0; i<flea.size(); i++)
        {
            this->flea.at(i)->update(this->window);
            flea.at(i)->SpawnMushroomWithFlea(Mush);
        }

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

        this->window->draw(this->StartSplashText);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            start=false;
            lvlBegin=true;
        }
    }
    else if(gameOver){

        this->window->draw(this->StartSplashText);
        Mush.clear();
        centipedes.clear();
        flea.clear();

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
//Creates the laser beams
void Game::ShootLaser()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&laser.size()<=this->MaxLaserCount&&LaserDelay>=MaxLaserDelay)
    {
        sf::FloatRect BugPos=BugB->GetBugPosition();
        laser.push_back(std::make_shared<Laser>(BugPos));
        LaserDelay=0.f;
    }
    LaserDelay++;
}


void Game::SpawnFlea()
{
    int PlayerAreaMush=0;

    for(int k=0; k<Mush.size(); k++)
    {
        if(Mush.at(k)->inPlayerArea())
            PlayerAreaMush++;
    }

    if(PlayerAreaMush<7&&MinFleaTimeDelay<FleaTimeDelay)
    {
    flea.push_back(std::make_shared<Flea>());
    FleaTimeDelay=0;
    }
    FleaTimeDelay++;

}

void Game::SpawnBomb()
{
    int randomnum=rand()%100;
    float randomy = 21+(rand() % 460);
    float randomx = (rand() % 780);

    if(randomnum<2&&MinBombTimeDelay<BombTimeDelay&&bomb.size()<4)
    {
    bomb.push_back(std::make_shared<Bomb>(randomx,randomy));
    BombTimeDelay=0;

    for(int j=0; j<Mush.size()-1; j++)//Makes sure random mushrooms dont intersect with bombs
        {
            if(Mush.at(j)->GetMushroomPosition().intersects(bomb.at(bomb.size()-1)->GetBombPosition()))
            {
                bomb.pop_back();
            }


        }
    }

    BombTimeDelay++;
}


