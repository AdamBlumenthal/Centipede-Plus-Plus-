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
Centipede::Centipede(std::vector<Segment> seg){
    segments.clear();
    segments=seg;

    hitMushroom=true;
    segments.at(0).makeHead();
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
std::vector<MoveCentipede> temp(length*9,MoveCentipede::NoMove);
moves=temp;
moves.insert(moves.begin(),MoveCentipede::Right);
}
//Moves Centipede and checks screen bounds with relation to head
void Centipede::checkCentipedeBounds(){
    int gameWidth=800;//constants throughout the game
    int gameHeight=600;//constants
     if(hitMushroom==true){

        moves.at(0)=MoveCentipede::Down;

        leftOrRight=!leftOrRight;
    hitMushroom=false;

    }
    else if(segments.at(0).GetSegmentPosition().left-1==0&&moves.at(0)!=MoveCentipede::Right)
    {
        //segments.at(0).moveMushroom();
       moves.at(0)=MoveCentipede::Down;
       // segments.at(0).moveDirections(moves.at(0));
    leftOrRight=!leftOrRight;//if(leftOrRight)

    }

    else if(segments.at(0).GetSegmentPosition().left +segments.at(0).GetSegmentPosition().width-1 == gameWidth)
    {

     // segments.at(0).moveMushroom
   moves.at(0)=MoveCentipede::Down;
      //  segments.at(0).moveDirections(moves.at(0));
    leftOrRight=!leftOrRight;
     //  if(leftOrRight)
    //moves.insert(moves.begin(),MoveCentipede::Right);
    //else
   // moves.insert(moves.begin(),MoveCentipede::Left);
    }
    else if(segments.at(0).GetSegmentPosition().top+segments.at(0).GetSegmentPosition().height>gameHeight||(segments.at(0).GetSegmentPosition().top<450.f&&segments.at(0).getVerticalSpeed()<0)){
            //segments.at(0).setVerticalSpeed();
           // segments.at(0).moveMushroom();
           moves.at(0)=MoveCentipede::Down;
            leftOrRight=!leftOrRight;
            }

}

void Centipede::Move(){
if(moves.at(1)!=MoveCentipede::Down)
checkCentipedeBounds();
for(int i=0;i<segments.size();i++){
    segments.at(i).moveDirections(moves.at(i*9));
}
if(leftOrRight)
    moves.insert(moves.begin(),MoveCentipede::Right);
else if(!leftOrRight)
    moves.insert(moves.begin(),MoveCentipede::Left);

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
sf::FloatRect Centipede::GetCentipedeHeadPosition()
{
    sf::FloatRect CentipedeHeadBounds=segments.at(0).GetSegmentPosition();
    return CentipedeHeadBounds;
}
void Centipede::setHitMushroom(){
  hitMushroom=true;

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
bool Centipede::isEmpty(){
    return segments.empty();
}
void Centipede::moveHead(){
    segments.at(0).moveMushroom();
}
