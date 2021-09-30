#ifndef LASER_H
#define LASER_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

#include "BugBlaster.h"


class Laser
{
    public:
        Laser(sf::FloatRect BugBounds);
        virtual ~Laser();

        //Varibles
        float MoveSpeed;

//functions
        void LaserMove();
        void update(sf::RenderTarget* target);
        void render(sf::RenderTarget* target);
        void SetPositionLaser(sf::FloatRect BugBounds);

        void CheckCollisionWindow(sf::RenderTarget* target);

        sf::FloatRect GetLaserPosition();
        sf::RectangleShape getLaser();



    private:
        sf::RectangleShape laser;

        void createVarible();
        void createLaser();



};

#endif // LASER_H
