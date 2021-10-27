#ifndef MUSHROOM_H
#define MUSHROOM_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>


class Mushroom
{
    public:
        Mushroom(float x, float y);
        Mushroom();
        virtual ~Mushroom();

    //functions
    void render(sf::RenderTarget* target);
    bool inPlayerArea();

    sf::FloatRect GetMushroomPosition();
    sf::Sprite getMushroom();


    void HealthLoss();
    bool IsHealthZero();


    private:
        sf::Sprite mush;
        sf::Texture mushtext;

        void LoadSprite();
        void LoadTexture();

        //Varibles
        int MushHealth;


};

#endif // MUSHROOM_H
