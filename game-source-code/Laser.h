#ifndef LASER_H
#define LASER_H
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "BugBlaster.h"

/** \file Laser.h
    \brief Contains code for constructing the Laser class
 */

/** \class Laser
    \brief A thin rectangle is created that is shot by th player.
    The Laser starts in the middle of the player and moves upwards.
 */


class Laser
{
public:
    /** \brief The Constructor for the Laser class.
       \param BugBounds The position of the BugBlaster.
       So the Laser can spawn at the Player
    */
    Laser(sf::FloatRect BugBounds);

    //functions
    /** \brief Moves the Laser up by the set movement speed
    */
    void LaserMove();
    /** \brief Updates the Laser position from the movement that have occured
    */
    void update();
    /** \brief Renders the Laser in the window
        \param target The window in which the Laser will be drawn

    */
    void render(sf::RenderTarget* target);
    /** \brief Sets a new position for the laser based on the player position
       \param BugBounds The current position of the BugBlaster.
       So the Laser can spawn at the Player
    */
    void SetPositionLaser(sf::FloatRect BugBounds);

/** \brief Fetches the Laser object position from the class
        \return Gets the Laser position stored as an sf::FloatRect
    */
    sf::FloatRect GetLaserPosition();
    /** \brief Fetches the Laser object from the class
        \return Gets the Laser object from the class as an sf::RectangleShape
    */
    sf::RectangleShape getLaser();



private:

    sf::RectangleShape laser;

    void createVarible();
    void createLaser();

    //Varibles
    float MoveSpeed;




};

#endif // LASER_H
