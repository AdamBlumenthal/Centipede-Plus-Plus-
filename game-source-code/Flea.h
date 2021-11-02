#ifndef FLEA_H
#define FLEA_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "Mushroom.h"
#include <memory>

/** \file Flea.h
    \brief Contains code for constructing the Flea class
 */

/** \class Flea
    \brief A sprite is created that can spawn a Mushroom as it moves.
    The Flea starts at the top of the screen and moves down.
 */

class Flea
{
    public:
    /** \brief The Constructor for the Flea class.
        The flea stats at a random x position and y position=0
    */
        Flea();

        //functions
    /** \brief Updates the Flea position from the movement and collisions that have occured
    */
        void update();
    /** \brief Renders the Flea in the window
        \param target The window in which the Flea will render

    */
        void render(sf::RenderTarget* target);
    /** \brief Moves the Flea down by the set movement speed
    */
        void FleaMove();
    /** \brief Checks if the Flea has moved below the window player area bottom
        \param target The window in which the game occurs
        \return A bool that is true if the Flea is below the player area,false if the Flea is outside the area
    */
        bool CollisionBottomWindow(sf::RenderTarget* target);
        /** \brief Randomly spawns mushrooms at the Flea position
        \param Mush the vector of mushrooms that has to be added too
    */
        void SpawnMushroomWithFlea(std::vector<std::shared_ptr<Mushroom>>& Mush);
    /** \brief Fetches the Flea object position from the class
        \return Gets the Flea position stored as an sf::FloatRect
    */
        sf::FloatRect GetFleaPosition();
    /** \brief Sets a new position for the Flea object
        \param x The new x-axis position
        \param y The new y-axis position
    */
        void setFleaPosition(float, float);

    private:

        sf::Sprite flea;
        sf::Texture fleatext;

        float MoveSpeed;

        void LoadSprite();
        void LoadTexture();


};

#endif // FLEA_H
