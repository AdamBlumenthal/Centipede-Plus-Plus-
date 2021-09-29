#ifndef BUGBLASTER_H
#define BUGBLASTER_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
//#include "Laser.h"



class BugBlaster
{
    public:
        BugBlaster(float x=350.f,float y=450.f);
        virtual ~BugBlaster();

        //Varibles
        float MoveSpeed;


        //functions
        void KeyInput();
        void update(sf::RenderTarget* target);
        void render(sf::RenderTarget* target);

        void WindowCollision(sf::RenderTarget* target);

        sf::FloatRect GetBugPosition();



    private:
        sf::RectangleShape bug;

        void createVarible();
        void createBug();



};

#endif // BUGBLASTER_H
