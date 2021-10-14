#ifndef FLEA_H
#define FLEA_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>



class Flea
{
    public:
        Flea();
        virtual ~Flea();

        //functions
        void update();
        void render(sf::RenderTarget* target);
        void FleaMove();
        bool CollisionBottomWindow(sf::RenderTarget* target);

        sf::FloatRect GetFleaPosition();



    private:

        sf::Sprite flea;
        sf::Texture fleatext;

        float MoveSpeed;

        void LoadSprite();
        void LoadTexture();


};

#endif // FLEA_H
