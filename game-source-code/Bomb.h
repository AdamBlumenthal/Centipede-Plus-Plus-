#ifndef BOMB_H
#define BOMB_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>


class Bomb
{
    public:
        Bomb(float x,float y);
        virtual ~Bomb();

        void update(sf::RenderTarget* target);
        void render(sf::RenderTarget* target);

        void RescaleBomb();

        sf::FloatRect GetBombPosition();

    private:

        sf::Sprite bomb;
        sf::Texture bombtext;

        void LoadSprite();
        void LoadTexture();



};

#endif // BOMB_H