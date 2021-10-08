#ifndef CENTIPEDESEGMENT_H_INCLUDED
#define CENTIPEDESEGMENT_H_INCLUDED
#include <SFML/Graphics.hpp>

class Segment
{

public:
    Segment(float& position);
    Segment(float& position, float& movespeed);
    void moveDirections();
    void moveMushroom();
    sf::RectangleShape getSegment();
    void update(sf::RenderTarget* target);
    void render(sf::RenderTarget* target);
    void makeHead();
    sf::FloatRect GetSegmentPosition();
private:
    sf::RectangleShape segment1;
    float movespeed;//=5.f;
    float verticalSpeed;
    void makeSegment(float& position);
    float position;

};

#endif // CENTIPEDESEGMENT_H_INCLUDED
