#ifndef CENTIPEDESEGMENT_H_INCLUDED
#define CENTIPEDESEGMENT_H_INCLUDED
#include <SFML/Graphics.hpp>

class Segment
{

public:
    Segment(float& position);
    void moveDirections();
    sf::RectangleShape getSegment();
    void update(sf::RenderTarget* target);
    void render(sf::RenderTarget* target);
    sf::FloatRect GetSegmentPosition();
private:
    sf::RectangleShape segment1;
    float movespeed=5.f;
    void makeSegment(float& position);
    float position;

};

#endif // CENTIPEDESEGMENT_H_INCLUDED
