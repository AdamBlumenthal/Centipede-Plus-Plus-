#include <SFML/Graphics.hpp>
#include "CentipedeSegment.h"
#include <iostream>

//Constructor
Segment::Segment(float& pos):position(pos)
{
    movespeed=2.f;
    verticalSpeed=20.f;
    this->makeSegment(pos);
    head=false;
}
Segment::Segment(float& pos, float& mSpeed):position(pos),movespeed(mSpeed)
{
    verticalSpeed=20.f;
    this->makeSegment(pos);
    head=false;
}
//Movement with in bounds for the segments
void Segment::moveDirections()
{
    this->segment1.move(movespeed,0);
}
void Segment::moveMushroom(){
        movespeed=(-1)*movespeed;

        this->segment1.move(0,verticalSpeed);
       // this->segment1.move(movespeed,0);
}
// Create a segment of the centipede
void Segment::makeSegment(float& position)
{
    this->segment1.setSize(sf::Vector2f(18.f, 18.f));
    this->segment1.setFillColor(sf::Color::Blue);
    this->segment1.setOutlineColor(sf::Color::Yellow);
    this->segment1.setPosition(position,0);
    this->segment1.setOutlineThickness(1.f);
}
void Segment::makeHead()
{
    this->segment1.setFillColor(sf::Color::Red);
    head=true;
}
//Get Shape of segment
sf::RectangleShape Segment::getSegment()
{
    return segment1;
}
//Updates Segment
void Segment::update(sf::RenderTarget* target)
{


}
//Rednders segment
void Segment::render(sf::RenderTarget* target)
{
    target->draw(this->segment1);
}
//Gets position
sf::FloatRect Segment::GetSegmentPosition()
{
    sf::FloatRect SegmentBounds=segment1.getGlobalBounds();
    return SegmentBounds;
}

void Segment::setVerticalSpeed(){

    verticalSpeed=(-1)*verticalSpeed;
}
