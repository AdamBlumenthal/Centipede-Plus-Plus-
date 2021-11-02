#ifndef MUSHROOM_H
#define MUSHROOM_H

#include <SFML/Graphics.hpp>
#include "BugBlaster.h"
#include <memory>

/** \file Mushroom.h
    \brief Contains code for constructing the Mushroom class
 */

/** \class Mushroom
    \brief A sprite is created that is randomly spawned in the gamespace.
    The Mushroom does not move.
 */

class Mushroom
{
    public:
        //Constructor
         /** \brief The Constructor for the Mushroom class
        \param x The set x-axis position
        \param y The set y-axis position
    */
        Mushroom(float x, float y);
        /** \brief Another Constructor for the Mushroom class.
        This sets the Mushroom position randomly within the player space
    */
        Mushroom();

    //functions
    /** \brief Renders the Mushroom in the window
        \param window The window in which the mushroom will rendered

    */
    void render(sf::RenderTarget* target);
    /** \brief Checks if the mushroom position is within the Player area
        \return bool true if Mushroom is within the player area,false is outside Player area

    */
    bool inPlayerArea();
    /** \brief Checks if the mushroom position is intersectiong with the player position
        \param Bug The BugBlaster object controled by the player
        \return bool true if the Mushroom intersects with the player,false if there is no intersection
    */
    bool MushroomInPlayerStart(std::shared_ptr<BugBlaster>& Bug);
/** \brief Fetches the Mushroom object position from the class
        \return Gets the Mushroom position stored as an sf::FloatRect
    */
    sf::FloatRect GetMushroomPosition();
    /** \brief Fetches the Mushroom object from the class
        \return Gets the Mushroom object from the class as an sf::RectangleShape
    */
    sf::Sprite getMushroom();

/** \brief Reduces the Mushroom Health points by 1

    */
    void HealthLoss();
    /** \brief Checks if the Mushroom health is zero or less
        \return bool which is true if the Mushroom health is 0 is less than 0

    */
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
