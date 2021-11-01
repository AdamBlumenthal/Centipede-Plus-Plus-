#ifndef BOMB_H
#define BOMB_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>


class Bomb
{
    public:
        Bomb(float x,float y);

        void render(sf::RenderTarget* target);

        sf::FloatRect GetBombPosition();

    private:

        sf::Sprite bomb;
        sf::Texture bombtext;

        void LoadSprite();
        void LoadTexture();



};

#endif // BOMB_H
