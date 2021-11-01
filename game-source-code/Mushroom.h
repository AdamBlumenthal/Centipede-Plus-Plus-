#ifndef MUSHROOM_H
#define MUSHROOM_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "BugBlaster.h"
#include <memory>


class Mushroom
{
    public:
        Mushroom(float x, float y);
        Mushroom();

    //functions
    void render(sf::RenderTarget* target);
    bool inPlayerArea();
    bool MushroomInPlayerStart(std::shared_ptr<BugBlaster> Bug);

    sf::FloatRect GetMushroomPosition();
    sf::Sprite getMushroom();


    void HealthLoss();
    bool IsHealthZero();


    private:
        sf::Sprite mush;
        sf::Texture mushtext;

        void LoadSprite();
        void LoadTexture();

        //Control Variables
        int MushHealth;


};

#endif // MUSHROOM_H
