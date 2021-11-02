#ifndef CENTIPEDE_H_INCLUDED
#define CENTIPEDE_H_INCLUDED
#include <vector>
#include "CentipedeSegment.h"
#include <SFML/Graphics.hpp>
#include <string>


/** \file Centipede.h
    \brief Constructs a centipede, and has all functionality required to move the centipede and change it if required
 */

 /** \class Centipede
    \brief A centipede is created which is a vector of segments. This controls the functionality of the centipede
 */
class Centipede{
public:
       /** \brief The Default constructor  for the Centipede class
        */
        Centipede();
        /** \brief The Parameterised constructor  for the Centipede class which is used to create a new centipede from an old centipede
            \param A vector of segments is received as it is reusing the objects
            \param A vector of MoveCentipede is received as it is reusing old movement
        */
        Centipede(std::vector<Segment> segments, std::vector<MoveCentipede> m);
        /** \brief The Parameterised constructor  for the Centipede class which is used to create a new centipede
            \param An integer specifying the length of the centipede
            \param A float giving the direction of the centipede
            \param A float giving the initial position of the centipede
        */
        Centipede(int, float, float);
        /** \brief Checks whether the centipede hits the sides of the window, bottom of the window or top of player area and moves it up or down and reverses it's horizontal movement direction
        */
        void checkCentipedeBounds();
        /** \brief Moves each segment of the centipede and preloads the next movement
        */
        void Move();
         /** \brief Moves only the first segment
        */
        void moveHead();
        /** \brief Reverses the horizontal direction of the centipede and moves it up or down
        */
        void setHitMushroom();
         /** \brief The size of the centipede
                \return Returns the size of the centipede (number of segments)
        */
        int getSize();
         /** \brief Returns if the vector size of segments is empty
                \return Returns the boolean if the vector is empty or not
        */
        bool isEmpty();
         /** \brief The vector of movement is returned
            \return Returns the vector of the movements for the centipede
        */
        std::vector<MoveCentipede> getMoves(){return moves;};
          /** \brief Gives the movement for the new centipede from preceding centipede
            \param Receives the position where new movements are from
            \return Returns the vector of the movements for the new centipede
        */
        std::vector<MoveCentipede> getMovesNew(int pos);
        /** \brief Returns a vector of segments for the centipede
            \return Returns a vector of segments for the centipede
        */
        std::vector<Segment> getCentipede();
           /** \brief Gives the vector of segments for the new centipede from preceding centipede
            \param Receives the position of where to get new centipede from
            \return Returns the vector of the segments for the new centipede
        */
        std::vector<Segment> getNewCentipede(int pos);

         /** \brief Updates the centipede's segments positions
        \param target The render window which is passed to it for calculations
        */
        void update(sf::RenderTarget* target);
            /** \brief Renders the Centipede's segments in the window
            \param  The window in which the centipede will rendered
                */
        void render(sf::RenderTarget* target);
        /** \brief Erases the segments from the centipede that are destroyed and/or moved to new centipede
            \param Receives the position of where to erase segments from
        */
        void fixedHead(int pos);
        /** \brief Erases the movements from the centipede  moves that are destroyed and/or moved to new centipede
            \param Receives the position of where to erase moves from
        */
        void fixedMoves(int pos);
        /** \brief The position of the first segment, the head of centipede
            \return Global bounds for the first segment
        */
        sf::FloatRect GetCentipedeHeadPosition();

private:
    std::vector<Segment> segments;
    std::vector<MoveCentipede> moves;
    int length;
    float direction;

    bool hitMushroom;
    bool leftOrRight;
    bool upOrDown;
};


#endif // CENTIPEDE_H_INCLUDED
