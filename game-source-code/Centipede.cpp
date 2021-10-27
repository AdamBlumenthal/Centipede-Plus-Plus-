#include <vector>
#include <cmath>
#include "Centipede.h"
#include "CentipedeSegment.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
//Size of segment
float Centipede::segmentSize=20.f;
Centipede::Centipede(){
segments.clear();
}
Centipede::Centipede(std::vector<Segment> seg, std::vector<MoveCentipede> m){
    segments.clear();
    segments=seg;
    moves=m;
    hitMushroom=true;
    upOrDown=true;
    leftOrRight=true;
    for(int i=0;i<moves.size();i++){
        if(moves.at(i)==MoveCentipede::Down){
            upOrDown=true;
             break;
        }
         if(moves.at(i)==MoveCentipede::Up){
            upOrDown=false;
            break;
        }
    }for(int i=0;i<moves.size();i++){
        if(moves.at(i)==MoveCentipede::Right){
            leftOrRight=true;
             break;
        }
         if(moves.at(i)==MoveCentipede::Left){
            leftOrRight=false;
            break;
        }
    }
    segments.at(0).makeHead();
   // moves.insert(moves.begin(),MoveCentipede::Down);
    }
Centipede::Centipede(int l, float d, float p ):length(l),direction(d) {
    segments.clear();
    float pos;
    hitMushroom=false;
    for(auto i=0; i<length;i++){
            //pos=p+(-18)*i;
    segments.push_back(Segment(pos, direction));
    }
    segments.at(0).makeHead();
    leftOrRight=true;
    upOrDown=true;
std::vector<MoveCentipede> temp(length*9,MoveCentipede::NoMove);
moves=temp;
moves.insert(moves.begin(),MoveCentipede::Right);
}
//Moves Centipede and checks screen bounds with relation to head
void Centipede::checkCentipedeBounds(){
    int gameWidth=800;//constants throughout the game
    int gameHeight=600;//constants
     //if(hitMushroom==true){


       // hitMushroom=false;

   // }

     if((segments.at(0).GetSegmentPosition().left-1==0&&moves.at(0)!=MoveCentipede::Right)
            ||segments.at(0).GetSegmentPosition().left +segments.at(0).GetSegmentPosition().width-1 == gameWidth)
    {
    leftOrRight=!leftOrRight;
    upOrDown ? moves.at(0)=MoveCentipede::Down : moves.at(0)=MoveCentipede::Up;



    }
    else if(segments.at(0).GetSegmentPosition().top+segments.at(0).GetSegmentPosition().height>gameHeight||
            (segments.at(0).GetSegmentPosition().top<450.f&&!upOrDown)){
            //segments.at(0).setVerticalSpeed();
           // segments.at(0).moveMushroom();
           upOrDown=!upOrDown;


           upOrDown ? moves.at(0)=MoveCentipede::Down : moves.at(0)=MoveCentipede::Up;
            leftOrRight=!leftOrRight;
            }


}

void Centipede::Move(){
if(!(moves.at(1)==MoveCentipede::Down||moves.at(1)==MoveCentipede::Up)){
checkCentipedeBounds();

}
for(int i=0;i<segments.size();i++){
    segments.at(i).moveDirections(moves.at(i*9));
}
leftOrRight ? moves.insert(moves.begin(),MoveCentipede::Right) : moves.insert(moves.begin(),MoveCentipede::Left);
std::cout<<GetCentipedeHeadPosition().top<<std::endl;
moves.pop_back();

}







void Centipede::update(sf::RenderTarget* target)
{

   this->Move();
   //setHitMushroom();
}
//Rednders segment
void Centipede::render(sf::RenderTarget* target)
{
    for(int i=0;i<segments.size();i++)
    segments.at(i).render(target);
}

std::vector<Segment> Centipede::getNewCentipede(int pos){

    auto centi=segments;
    centi.clear();
    //segments.clear();
    for(int i=pos+1;i<segments.size();i++)
        centi.push_back(segments.at(i));

    return centi;
}
std::vector<MoveCentipede> Centipede::getMovesNew(int pos){

    std::vector<MoveCentipede> m(moves.begin()+(pos+1)*9,moves.end());
    //m.clear();
    //segments.clear();
    //for(int i=pos+1;i<moves.size();i++)
     //  m.push_back(moves.at(i));

    return m;
}
sf::FloatRect Centipede::GetCentipedeHeadPosition()
{
    sf::FloatRect CentipedeHeadBounds=segments.at(0).GetSegmentPosition();
    return CentipedeHeadBounds;
}
void Centipede::setHitMushroom(){
   upOrDown ? moves.at(0)=MoveCentipede::Down : moves.at(0)=MoveCentipede::Up;
    leftOrRight=!leftOrRight;

}
int Centipede::getSize(){

    return segments.size();
}

std::vector<Segment> Centipede::getCentipede(){
    return segments;
}
void Centipede::fixedHead(int pos){
    auto temp=segments;
    temp.clear();
    //segments.clear();
    for(int i=0;i<pos;i++)
        temp.push_back(segments.at(i));

    segments=temp;


}
void Centipede::fixedMoves(int pos){
    std::vector<MoveCentipede>temp(moves.begin(),moves.begin()+pos*9);
    moves=temp;

}
bool Centipede::isEmpty(){
    return segments.empty();
}
void Centipede::moveHead(){
    segments.at(0).moveMushroom();
}
