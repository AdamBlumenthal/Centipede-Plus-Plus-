#include <SFML/Graphics.hpp>
#include "CentipedeSegment.h"
#include <iostream>
//using namespace std;
Segment::Segment(float& pos):position(pos){
//std::cout<<"Zunaid"<<std::endl;
//makeSegment(position);
//std::cout<<"Dylan"<<std::endl;
//float position=0.f;
    //float position=0.f;
    this->makeSegment(pos);
}
//sf::FloatRect BugBlaster::GetBugPosition()
 //{
  //   sf::FloatRect BugBounds=bug.getGlobalBounds();
    // return BugBounds;
 //}
void Segment::moveDirections(){

    int gameWidth=800;
                //this-> movespeed=5.f;
                if(this->segment1.getPosition().x==0&&movespeed<0){
                       this-> segment1.setPosition(this->segment1.getPosition().x,this->segment1.getPosition().y);
                      this-> movespeed=5.f;
                        this->segment1.move(0,20.f);
                        }

                else if(this->segment1.getPosition().x +20.f >= gameWidth){
                   this-> segment1.setPosition(this->segment1.getPosition().x,this->segment1.getPosition().y);
                    this->movespeed=-5.f;
                    this->segment1.move(0,20.f);
                   // segment.move(movespeed,0);
                    //break;
                }
               this->segment1.move(movespeed,0);
}
//    segmentWin=makeSegment();
//num=x;

 void Segment::makeSegment(float& position)
{
    // Create a segment of the centipede

    //auto segment = sf::RectangleShape{};
    this->segment1.setSize(sf::Vector2f(20.f, 20.f));
    this->segment1.setFillColor(sf::Color::Blue);
    this->segment1.setOutlineColor(sf::Color::Yellow);
    this->segment1.setPosition(position,0);
    this->segment1.setOutlineThickness(2.f);
    //std::cout<<"Bob"<<std::endl;
    //return segment;
}

sf::RectangleShape Segment::getSegment(){
    return segment1;
    }

void Segment::update(sf::RenderTarget* target)
{

    this->moveDirections();


}

void Segment::render(sf::RenderTarget* target)
{
    target->draw(this->segment1);
}

sf::FloatRect Segment::GetSegmentPosition()
 {
     sf::FloatRect SegmentBounds=segment1.getGlobalBounds();
     return SegmentBounds;
 }
//int Segment::getNum(){
//return 7;
//}
//sf::RectangleShape moveRight(){
//segment.move(10.f,0.f);
//}
//sf::RectangleShape Segment::getRect(){
//return segment;
//}
