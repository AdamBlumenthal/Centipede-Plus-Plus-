#include <SFML/Graphics.hpp>
#include "CentipedeSegment.h"
#include <iostream>

//Constructor
Segment::Segment(float& pos):position(pos)
{

    this->makeSegment(pos);
}
//Movement with in bounds for the segments
void Segment::moveDirections()
{

    int gameWidth=800;

    if(this->segment1.getPosition().x==0&&movespeed<0)
    {
        this-> segment1.setPosition(this->segment1.getPosition().x,this->segment1.getPosition().y);
        this-> movespeed=5.f;
        this->segment1.move(0,20.f);
    }

    else if(this->segment1.getPosition().x +20.f >= gameWidth)
    {
        this-> segment1.setPosition(this->segment1.getPosition().x,this->segment1.getPosition().y);
        this->movespeed=-5.f;
        this->segment1.move(0,20.f);
    }
    this->segment1.move(movespeed,0);
}

// Create a segment of the centipede
void Segment::makeSegment(float& position)
{
    this->segment1.setSize(sf::Vector2f(20.f, 20.f));
    this->segment1.setFillColor(sf::Color::Blue);
    this->segment1.setOutlineColor(sf::Color::Yellow);
    this->segment1.setPosition(position,0);
    this->segment1.setOutlineThickness(2.f);
}
//Get Shape of segment
sf::RectangleShape Segment::getSegment()
{
    return segment1;
}
//Updates Segment
void Segment::update(sf::RenderTarget* target)
{
    //Changes in position
    this->moveDirections();

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

