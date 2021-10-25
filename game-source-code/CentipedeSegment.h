#ifndef CENTIPEDESEGMENT_H_INCLUDED
#define CENTIPEDESEGMENT_H_INCLUDED
#include <SFML/Graphics.hpp>

enum class MoveCentipede{NoMove,Up,Down, Right, Left};

class Segment
{

public:
    Segment(float& position);
    Segment(float& position, float& movespeed);
    void moveDirections(MoveCentipede dir);
    void moveMushroom();
    void moveBlock();
    void setVerticalSpeed();
    bool isHead(){return head;};
    float getVerticalSpeed(){return verticalSpeed;};
    sf::RectangleShape getSegment();
    void update(sf::RenderTarget* target);
    void render(sf::RenderTarget* target);
    void makeHead();
    sf::FloatRect GetSegmentPosition();
    float getMoveSpeed(){return movespeed;}
private:
    sf::RectangleShape segment1;
    float movespeed;//=5.f;
    float verticalSpeed;
    void makeSegment(float& position);
    float position;
    bool head;

};

#endif // CENTIPEDESEGMENT_H_INCLUDED
