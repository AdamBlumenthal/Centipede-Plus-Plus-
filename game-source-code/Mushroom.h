#ifndef MUSHROOM_H
#define MUSHROOM_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>


class Mushroom
{
    public:
        Mushroom();
        virtual ~Mushroom();

    //functions
    void update(sf::RenderTarget* target);
    void render(sf::RenderTarget* target);

    sf::FloatRect GetMushroomPosition();


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
