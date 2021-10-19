#ifndef CENTIPEDE_H_INCLUDED
#define CENTIPEDE_H_INCLUDED
#include <vector>
#include "CentipedeSegment.h"
#include <SFML/Graphics.hpp>


class Centipede{
public:
        Centipede();
        Centipede(std::vector<Segment> segments);
        Centipede(int, float, float);
        void checkCentipedeBounds();
        void Move();
        void moveHead();
        void setHitMushroom();
        int getSize();
        bool isEmpty();

        std::vector<Segment> getCentipede();
        std::vector<Segment> getNewCentipede(int pos);
        void update(sf::RenderTarget* target);
        void render(sf::RenderTarget* target);
        void fixedHead(int pos);
        sf::FloatRect GetCentipedeHeadPosition();

private:
    std::vector<Segment> segments;
    int length;
    float direction;
    static float segmentSize;

    bool hitMushroom;
   // float position;
};


#endif // CENTIPEDE_H_INCLUDED