#include <SFML/Graphics.hpp>
#include "CentipedeSegment.h"
#include <iostream>

//Constructor
Segment::Segment(float pos):position(pos)
{
    movespeed=2.f;
    makeSegment(pos);
}
Segment::Segment(float pos, float mSpeed):position(pos),movespeed(mSpeed)
{
    makeSegment(pos);

}
//Movement with in bounds for the segments
void Segment::moveDirections(Movement dir)
{
    switch(dir){
    case Movement::Up:  segment.move(0,(-1)*verticalSpeed); break;
    case Movement::Down: segment.move(0,verticalSpeed); break;
    case Movement::Left: segment.move((-1)*movespeed,0); break;
    case Movement::Right: segment.move(movespeed,0); break;
    default:         segment.move(0,0);
    }



}

// Create a segment of the centipede
void Segment::makeSegment(float& position)
{
    segment.setSize(sf::Vector2f(18.f, 18.f));
    segment.setFillColor(sf::Color::Blue);
    segment.setOutlineColor(sf::Color::Yellow);
    segment.setPosition(position,1);
    segment.setOutlineThickness(1.f);
}
void Segment::makeHead()
{
    segment.setFillColor(sf::Color::Red);

}
//Get Shape of segment
sf::RectangleShape Segment::getSegment()
{
    return segment;
}

//Renders segment
void Segment::render(std::shared_ptr<sf::RenderWindow> target)
{
    target->draw(segment);
}
//Gets position
sf::FloatRect Segment::GetSegmentPosition()
{

    return segment.getGlobalBounds();
}
//Used for Testing Centipede
void Segment::setSegmentPosition(float x, float y){

    segment.setPosition(x,y);
}
