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
    this->videomode.height=600;
    this->videomode.width=800;
    this->window=new sf::RenderWindow(videomode, "SFML Centipede", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);



};
//Gives values to private variables.
void Game::createVarible()
{

    //Laser controls

    this->MaxLaserCount=10;
    this->MaxLaserDelay=26.f;
    this->LaserDelay=this->MaxLaserDelay;
    //this->CurrentLasers=0;
    //centipedes.push_back(Centipede(0,0.f,0.f));
    this->MaxLengthCentipede=12;
    //Game controls
    lvlBegin=false;
    start=true;
    gameOver=false;
    centMush=false;
    pause=false;
    currentSegments=MaxLengthCentipede;


    //Mushroom controls
    this->MushCount=20;

    //Load font
    if (!this->font.loadFromFile("resources/arial.ttf"))
    {
        std::cout << "ERROR::GAME::Failed to load font" << "\n";
    }

    this->StartSplashText.setFont(this->font);
    this->StartSplashText.setCharacterSize(25);
    this->StartSplashText.setFillColor(sf::Color::White);
   // this->StartSplashText.setString("SFML Centipede: Press Enter to start,Press Escape to Quit\n Arrow Keys to move\n Space to Shoot");
    this->StartSplashText.setPosition(0,250);

    Mushroom* Tempmush=nullptr;

    for(int i=0; i<=MushCount; i++)
    {
        float randomy = 21+(rand() % 580);
        float randomx = (rand() % 800);
        Tempmush=new Mushroom(randomx,randomy);
        Mush.push_back(Tempmush);

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

    CollisionControl(BugB,laser,Mush,flea,centipedes);
    //std::cerr<<"Here"<<std::endl;
    //if(laser.size()>0)
    //std::cout<<laser.at(0).use_count()<<std::endl;

    SpawnFlea();
    KillFlea();

    if(!pause){
    this->UpdateEvent();

    this->BugB.update(this->window);



    //this->UpdateEvent();
    this->ShootLaser();
   // this->LaserCollision();
    this->LaserCollisionMushrooms();
    this->CollisionBugCentipede();
    //this->MakeCentipede();

    this->CollisionBugPlayer();
    this->CollisionBugFlea();
    //this->CollisonLaserFlea();


    if(centipedes.size()>0){

        for(int i=0;i<centipedes.size();i++){

            CentipedeCollisionMushroom(centipedes.at(i));
            LaserCollisionCentipedes(centipedes.at(i));
            //SelfCollision(centipedes.at(i),  i);


    }

    centipedes.erase(remove_if(centipedes.begin(),centipedes.end(),[](std::shared_ptr<Centipede> cent)->bool{return cent->isEmpty();}),centipedes.end());
       // SelfCollision();
        for(int i=0;i<centipedes.size();i++)
            centipedes.at(i)->update(this->window);
    }


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


    if (laser.size()>=1)
    {
        for(int i=0; i<laser.size(); i++)
        {
           laser.at(i)->update(this->window);
        }

    }


    }

    if (flea.size()>=1)
    {
        for(int i=0; i<flea.size(); i++)
        {
            this->flea.at(i)->update(this->window);
            Mush=this->flea.at(i)->SpawnMushroomWithFlea(Mush);
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
         this->StartSplashText.setString("SFML Centipede: Press Enter to start,Press Escape to Quit\n Arrow Keys to move\n Space to Shoot");

        this->window->draw(this->StartSplashText);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            start=false;
            lvlBegin=true;
        }
    }
    else if(gameOver){
          this->StartSplashText.setString("Game Over\n Press Enter to restart \n Press Escape to Quit\n Arrow Keys to move\n Space to Shoot");
        this->window->draw(this->StartSplashText);
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {


          //  this->window->clear(sf::Color::Black);
          segments.clear();
          heads.clear();
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
       // update();
        //Render Objects in space

        this->BugB.render(this->window);

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
            this->flea.at(i)->render(this->window);
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
        laser.push_back(std::make_shared<Laser>(BugPos));
        //CurrentLasers++;
        //Game::MaxLengthCentipede
        LaserDelay=0.f;
    }
    LaserDelay++;
}

//Checks if Laser collides with objects such as edge of screen or centipede segments
//void Game::LaserCollision()
//{
//
//    for(int i=0; i<laser.size(); i++)
//    {
//        //sf::FloatRect LaserPos=this->laser.at(i).GetLaserPosition();
//
//        if(laser.at(i)->GetLaserPosition().top<=0.f)
//        {
//            this->laser.erase(this->laser.begin()+i);
//            break;
//        }
//
//    }
//}
void Game::CentipedeCollisionMushroom(std::shared_ptr<Centipede> centipede){
    if(centipede->getSize()>0)
    for(int i=0;i<Mush.size();i++)
        if(Mush.at(i)->GetMushroomPosition().intersects(centipede->GetCentipedeHeadPosition())){
            centipede->setHitMushroom();
        }
}
void Game::LaserCollisionCentipedes(std::shared_ptr<Centipede> centipede){
    bool leave=false;
    for(int i=0;i<laser.size();i++){
        for(int j=0;j<centipede->getSize();j++){
            if(laser.at(i)->GetLaserPosition().intersects(centipede->getCentipede().at(j).GetSegmentPosition())){
                this->laser.erase(laser.begin()+i);
                leave=true;
                MakeMushroom(centipede->getCentipede().at(j));

                auto temp=centipede->getNewCentipede(j);
                auto length=centipede->getSize()-1;

                centipede->fixedHead(j);

                //if(centipede.getSize()==0)
                   // std::cerr<<"There"<<std::endl;
                if(j!=length){
                    std::cerr<<"There"<<std::endl;
                    centipedes.push_back(std::make_shared<Centipede>(temp));

                }
                //std::cerr<<j<<std::endl;
                break;
            }
        }
        if(leave)break;
}

}
void Game::SelfCollision(){
}
//    bool collision=false;
//
//    for(int i=0;i<centipedes.size()-1;i++){
//        for(int j=i+1;j<centipedes.size();j++){
//                for(int k=0;k<centipedes.at(j).getSize();k++){
//
//                    if(centipedes.at(i).GetCentipedeHeadPosition().intersects(centipedes.at(j).getCentipede().at(k).GetSegmentPosition())){
//                        if(k==0)
//                            centipedes.at(j).moveHead();
//                        std::cout<<"Hit pos og at y";
//                        std::cout<<centipedes.at(i).getCentipede().at(0).GetSegmentPosition().top;
//                          std::cout<<" Hit pos og at x";
//                        std::cout<<centipedes.at(i).getCentipede().at(0).GetSegmentPosition().left;
//                        std::cout<<std::endl;
//                        centipedes.at(i).moveHead();
//
//                        std::cout<<"Hit pos new at y";
//                        std::cout<<centipedes.at(i).getCentipede().at(0).GetSegmentPosition().top;
//                          std::cout<<" Hit pos new at x";
//                        std::cout<<centipedes.at(i).getCentipede().at(0).GetSegmentPosition().left;
//                        std::cout<<std::endl;
//                        std::cout<<"Here ";
//                        std::cout<<i;
//                        std::cout<<" Hit ";
//                        std::cout<<j;
//                        std::cout<<" segm";
//                        std::cout<<k;
//                        std::cout<<std::endl;
//                        collision=true;
//                        break;
//            }
//        }
//        if(collision){
//                collision=false;
//            break;
//        }
//    }
//
//}
//}


void Game::LaserCollisionMushrooms()
{

    bool leave=false;
    for(int i=0; i<laser.size(); i++)
    {
        for(int k=0; k<Mush.size(); k++)
        {
            if(this->laser.at(i)->GetLaserPosition().intersects(Mush.at(k)->GetMushroomPosition()))
            {

                this->laser.erase(this->laser.begin()+i);
              //  CurrentLasers--;
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
        if(leave)
        {
            //std::cout<<"hwoosooodsdofosdsdgsd"<<std::endl;
            break;
        }
    }


}
void Game::CentipedeSelfCollision(){

    for(auto i=0;i< segments.size();i++){
    for(auto j=i+1;j<segments.size();j++){
        if(segments.at(i).GetSegmentPosition().intersects(segments.at(j).GetSegmentPosition())){
            segments.at(i).moveMushroom();
            segments.at(j).moveMushroom();
        }

    }
    }

}

//Can make a general function where pass segments vector in

void Game::CollisionCentipedeMushroom()
{
    bool leave=false;
    int coun=0;
    //int mush, int segment;
    for(int i=0; i<Mush.size(); i++)
    {
        for(int j=0; j<segments.size(); j++)
        {
            if(Mush.at(i)->GetMushroomPosition().intersects(this->segments.at(j).GetSegmentPosition()))
            {

                leave=true;
                segments.at(j).moveMushroom();
                break;
                 //                       std::cout<<"44"<<std::endl;
                //break;

                }


            }
            //  if(leave)break;
        }

    }


void Game::CollisionBugCentipede(){
}
// for(int j=0; j<segments.size(); j++)
//        {
//            if(this->BugB.GetBugPosition().intersects(this->segments.at(j).GetSegmentPosition()))
//            {
//                gameOver=true;
//                break;
//            }
//        }
//}
//std::cout<<"Number of segments:"+segments.size()<<std::endl

//Makes a centipede. Segments that follow each other
//Bug they don't all follow each other at correct intervals


void Game::MakeMushroom(Segment segment)
{
    auto temp=segment.GetSegmentPosition();
//    std::cout<<temp<<std::endl;
    Mushroom* mush=new Mushroom(temp.left, temp.top);
    Mush.push_back(mush);
    //delete mush;
}

void Game::CollisionBugPlayer()
{

    for(int k=0; k<Mush.size(); k++)//Checks all mushrooms
    {

        if(BugB.GetBugPosition().intersects(Mush.at(k)->GetMushroomPosition()))
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)||sf::Keyboard::isKeyPressed(sf::Keyboard::Right))//Left and right
            {
                if(BugB.GetBugPosition().left>=Mush.at(k)->GetMushroomPosition().left-BugB.GetBugPosition().width
                        && BugB.GetBugPosition().left+BugB.GetBugPosition().width>Mush.at(k)->GetMushroomPosition().left+Mush.at(k)->GetMushroomPosition().width)//Checks if on the right and not on the left
                {
                    BugB.SetPosition(Mush.at(k)->GetMushroomPosition().left+Mush.at(k)->GetMushroomPosition().width,BugB.GetBugPosition().top);
                }
                else if(BugB.GetBugPosition().left+BugB.GetBugPosition().width>=Mush.at(k)->GetMushroomPosition().left)//Checks if on the left
                {
                    BugB.SetPosition(Mush.at(k)->GetMushroomPosition().left-BugB.GetBugPosition().width,BugB.GetBugPosition().top);
                }
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)||sf::Keyboard::isKeyPressed(sf::Keyboard::Down))//Up and down
            {
                if (BugB.GetBugPosition().top<Mush.at(k)->GetMushroomPosition().top+BugB.GetBugPosition().height
                        &&BugB.GetBugPosition().top>Mush.at(k)->GetMushroomPosition().top)//Checks if below and not above
                {
                    BugB.SetPosition(BugB.GetBugPosition().left,Mush.at(k)->GetMushroomPosition().top+Mush.at(k)->GetMushroomPosition().height);
                }
                else if(BugB.GetBugPosition().top+BugB.GetBugPosition().height>Mush.at(k)->GetMushroomPosition().top)//Checks if above
                {
                    BugB.SetPosition(BugB.GetBugPosition().left,Mush.at(k)->GetMushroomPosition().top-BugB.GetBugPosition().height);
                }
            }

        }

    }

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

     Flea* Tempflea=nullptr;
     Tempflea=new Flea();
    flea.push_back(Tempflea);
    FleaTimeDelay=0;

    }
    FleaTimeDelay++;

}

void Game::KillFlea()
{
     for(int h=0; h<flea.size(); h++)
        {

            if(flea.at(h)->CollisionBottomWindow(this->window))
            {
                flea.erase(flea.begin()+h);
                //std::cout<<flea.size()<<std::endl;
            }

        }
}

 //int* generalCollision( std::vector <A> a,std::vector <B> b)
 //{
    // int aa[a.size()];
    // int bb[b.size()];

    // for(int i=0;i<a.size();i++)
    // {
       //  for(int j=0;j<b.size();j++)
        // {
         //    if(a.getObjectPosition.intersects(b.getObjectPosiition))
           //     {
            //        aa[i]=1;
            //        bb[j]=1;
           //     }
        // }
   //  }

   //  return [aa,bb];
// }


bool Game::IsEmpty(Centipede seg){
    return seg.isEmpty();
}

void Game::CollisionBugFlea()
{
    for(int h=0; h<flea.size(); h++)
        {
            if(this->BugB.GetBugPosition().intersects(flea.at(h)->GetFleaPosition()))
            {
                gameOver=true;
                break;
            }
        }

}

void Game::CollisonLaserFlea2()
{
    bool leave=false;

    for(int i=0; i<laser.size(); i++)
    {
        for(int j=0; j<flea.size(); j++)
        {
            if(laser.at(i)->GetLaserPosition().intersects(flea.at(j)->GetFleaPosition()))
            {

                //leave=true;
                flea.erase(flea.begin()+j);

            }


            }
            //  if(leave)break;
        }
}
