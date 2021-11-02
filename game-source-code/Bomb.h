#ifndef BOMB_H
#define BOMB_H

#include <SFML/Graphics.hpp>
#include <iostream>

/** \file Bomb.h
    \brief Contains code for constructing the Bomb class
 */

 /** \class Bomb
    \brief A sprite is created that does not move but is able to have collisions with objects around it
 */

class Bomb
{
    public:
        //Constructor
         /** \brief The Constructor for the Bomb class
        \param x The set x-axis position
        \param y The set y-axis position
    */
        Bomb(float x,float y);

         /** \brief Renders the Bomb in the window
        \param window The window in which the bomb will rendered

    */
        void render(sf::RenderTarget* window);

        /** \brief Fetches the Bomb object position from the class
        \return Gets the bomb position stored as an sf::FloatRect
    */
        sf::FloatRect GetBombPosition();

    private:

        sf::Sprite bomb;
        sf::Texture bombtext;

        void LoadSprite();
        void LoadTexture();



};

#endif // BOMB_H
