#ifndef CENTIPEDESEGMENT_H_INCLUDED
#define CENTIPEDESEGMENT_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "BugBlaster.h"
/** \file CentipedeSegment.h
    \brief Contains code for constructing a segment of a centipede. This gives it's basic characteristics
 */
//enum class MoveCentipede{NoMove,Up,Down, Right, Left};
/** \class Segment
    \brief A rectangular shape is created that will act as a segment of a centipede. It sets up the ability for a segment to move
 */
class Segment
{

public:
    /** \brief One of the constructors for the Segment  class
        \param Receives the intial x position for the segment to be created.
    */
    Segment(float position);
      /** \brief One of the constructors for the Segment class
        \param Receives the intial x position for the segment to be created.
        \param Receives the movespeeed for a segment
    */
    Segment(float position, float movespeed);

    /** \brief Moves the segment in one of the directions allowed
        \param dir is the enum of the direction for a segment to move
    */
    void moveDirections(Movement dir);


    /** \brief Returns the a rectangle shape
        \return A segment the rectangle shape object
    */
    sf::RectangleShape getSegment();

/** \brief Renders the BugBlaster in the window
        \param target The window in which the bug will rendered

    */
    void render(std::shared_ptr<sf::RenderWindow> target);

        /** \brief Changes the colour of a segment to red which is the colour of a head segment
    */
    void makeHead();
      /** \brief Gives the segment global bound coordinates
            \returns A segment's global bounds
    */
    sf::FloatRect GetSegmentPosition();
          /** \brief Sets the segments position
            \param x coordinate
            \param y coordinate
    */
    void setSegmentPosition(float x, float y);

private:
    sf::RectangleShape segment;
    float movespeed;
    float verticalSpeed=20.f;
    void makeSegment(float& position);
    float position;

};

#endif // CENTIPEDESEGMENT_H_INCLUDED
