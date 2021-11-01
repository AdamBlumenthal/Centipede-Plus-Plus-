#include "Bomb.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>


Bomb::Bomb(float x, float y)
{
    LoadTexture();
    LoadSprite();

    bomb.setPosition(x,y);

}

void Bomb::render(sf::RenderTarget* target)
{
    target->draw(bomb);
}

void Bomb::LoadTexture()
{
    if(!bombtext.loadFromFile("resources/DDTBomb.png"))
    {
        std::cout << "Bomb.cpp Failed to load Sprite" <<std::endl;
    }

}

void Bomb::LoadSprite()
{
    bomb.setTexture(bombtext);

    //Scaling image
    bomb.scale(0.03f,0.03f);
}

sf::FloatRect Bomb::GetBombPosition()
{
    sf::FloatRect BombBounds=bomb.getGlobalBounds();
    return BombBounds;
}
