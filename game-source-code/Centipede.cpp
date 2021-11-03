#include <vector>
#include <cmath>
#include "Centipede.h"
#include "CentipedeSegment.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>


Centipede::Centipede(){
segments.clear();
}
Centipede::Centipede(std::vector<Segment> seg, std::vector<Movement> m):segments(seg),moves(m)
{

    upOrDown=true;
    leftOrRight=true;
    for(int i=0;i<moves.size();i++){
        if(moves.at(i)==Movement::Down){
            upOrDown=true;
             break;
        }
         if(moves.at(i)==Movement::Up){
            upOrDown=false;
            break;
        }
    }for(int i=0;i<moves.size();i++){
        if(moves.at(i)==Movement::Right){
            leftOrRight=true;
             break;
        }
         if(moves.at(i)==Movement::Left){
            leftOrRight=false;
            break;
        }
    }
    segments.at(0).makeHead();
    }
Centipede::Centipede(int l, float d, float p ):length(l),direction(d) {
    segments.clear();
    float pos=p;
    for(auto i=0; i<length;i++){
            //pos=p+(-18)*i;
    segments.push_back(Segment(pos, direction));
    }
    segments.at(0).makeHead();
    leftOrRight=true;
    upOrDown=true;
std::vector<Movement> temp(length*9-8);
moves=temp;
moves.insert(moves.begin(),Movement::Right);
}
//Moves Centipede and checks screen bounds with relation to head
void Centipede::checkCentipedeBounds(){
    int gameWidth=800;//constants throughout the game
    int gameHeight=600;//constants


     if((segments.at(0).GetSegmentPosition().left-1<=0&&moves.at(0)!=Movement::Right)
            ||segments.at(0).GetSegmentPosition().left +segments.at(0).GetSegmentPosition().width-1 >= gameWidth)
    {
    leftOrRight=!leftOrRight;
    if(segments.at(0).GetSegmentPosition().top>=580.f||segments.at(0).GetSegmentPosition().top<=460.f&&!upOrDown)
        upOrDown=!upOrDown;
    upOrDown ? moves.at(0)=Movement::Down : moves.at(0)=Movement::Up;

    }



}

void Centipede::Move(){
if(!(moves.at(1)==Movement::Down||moves.at(1)==Movement::Up)){
checkCentipedeBounds();

}
for(int i=0;i<segments.size();i++){
    segments.at(i).moveDirections(moves.at(i*9));
}
leftOrRight ? moves.insert(moves.begin(),Movement::Right) : moves.insert(moves.begin(),Movement::Left);

moves.pop_back();

}

void Centipede::update(std::shared_ptr<sf::RenderWindow> target)
{
   Move();
}
//Rednders segment
void Centipede::render(std::shared_ptr<sf::RenderWindow> target)
{
    for(int i=0;i<segments.size();i++)
    segments.at(i).render(target);
}

std::vector<Segment> Centipede::getNewCentipede(int pos){

    std::vector<Segment> centi(segments.begin()+pos+1,segments.end());

    return centi;
}
std::vector<Movement> Centipede::getMovesNew(int pos){

    std::vector<Movement> m(moves.begin()+(pos+1)*9,moves.end());


    return m;
}
sf::FloatRect Centipede::GetCentipedeHeadPosition()
{
    sf::FloatRect CentipedeHeadBounds=segments.at(0).GetSegmentPosition();
    return CentipedeHeadBounds;
}
void Centipede::setHitMushroom(){
    if(segments.at(0).GetSegmentPosition().top>=580.f||segments.at(0).GetSegmentPosition().top<=460.f&&!upOrDown)
        upOrDown=!upOrDown;
   upOrDown ? moves.at(0)=Movement::Down : moves.at(0)=Movement::Up;
    leftOrRight=!leftOrRight;

}
int Centipede::getSize(){

    return segments.size();
}

std::vector<Segment> Centipede::getCentipede(){
    return segments;
}
void Centipede::fixedHead(int pos){

    segments.erase(segments.begin()+pos,segments.end());
}
void Centipede::fixedMoves(int pos){


    moves.erase(moves.begin()+(pos)*9,moves.end());


}
bool Centipede::isEmpty(){
    return segments.empty();
}

