#ifndef FLEA_H
#define FLEA_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Mushroom.h"



class Flea
{
    public:
        Flea();
        virtual ~Flea();

        //functions
        void update(sf::RenderTarget* target);
        void render(sf::RenderTarget* target);
        void FleaMove();
        bool CollisionBottomWindow(sf::RenderTarget* target);

        std::vector <Mushroom*> SpawnMushroomWithFlea(std::vector <Mushroom*> Mush);

        sf::FloatRect GetFleaPosition();



    private:

        sf::Sprite flea;
        sf::Texture fleatext;

        float MoveSpeed;

        void LoadSprite();
        void LoadTexture();


};

#endif // FLEA_H
