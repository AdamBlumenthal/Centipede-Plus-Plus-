#ifndef FLEA_H
#define FLEA_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Mushroom.h"
#include <memory>



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

        void SpawnMushroomWithFlea(std::vector<std::shared_ptr<Mushroom>>& Mush);

        sf::FloatRect GetFleaPosition();

        void setFleaPosition(float, float);

    private:

        sf::Sprite flea;
        sf::Texture fleatext;

        float MoveSpeed;

        void LoadSprite();
        void LoadTexture();


};

#endif // FLEA_H
