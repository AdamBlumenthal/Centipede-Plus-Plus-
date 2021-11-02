#ifndef BUGBLASTER_H
#define BUGBLASTER_H
#include <SFML/Graphics.hpp>
#include <memory>

/** \file BugBlaster.h
    \brief Contains code for constructing the BugBlaster class and the movement enum
 */


enum class Movement{Up,Down, Right, Left,NoMove};

/** \class BugBlaster
    \brief Creates a Green square what can be controled by the arrow keys on the keyboard.
    The movement is limited to a rectangle at the bottom of the screen.
 */


class BugBlaster
{
public:
     /** \brief The Constructor for the BugBlaster class
        \param x The set starting x-axis position defualt at 350
        \param y The set starting y-axis position defualt at 450
    */
    BugBlaster(float x=350.f,float y=450.f);

    //functions
    /** \brief Finds the movement direction of the player form the keyboard inputs
        \return The movement direction as a type class enum Movement
    */

    Movement BugBlasterGetInputs();
    /** \brief Changes the player position based on the movent speed and given direction
        \param movement player movemnet direction as type class enum Movement
    */
    void KeyInputResults(Movement movement);
    /** \brief Updates the player position from the movement and collisions
        \param target The render window which is passed on for collision calculations
    */
    void update(std::shared_ptr<sf::RenderWindow> target);
    /** \brief Renders the BugBlaster in the window
        \param target The window in which the bug will rendered

    */
    void render(std::shared_ptr<sf::RenderWindow> target);
/** \brief Stops the player from moving outside the player bounds
        \param target The window in which the bug has been bounded

    */

    void WindowCollision(std::shared_ptr<sf::RenderWindow> target);
    /** \brief Sets a new position for the BugBlaster object
        \param x The new x-axis position
        \param y The new y-axis position
    */
    void SetPosition(float x,float y);

    /** \brief Fetches the BugBlaster object position from the class
        \return Gets the bug position stored as an sf::FloatRect
    */
    sf::FloatRect GetBugPosition();
    /** \brief Fetches the BugBlaster object from the class
        \return Gets the bug object from the class as an sf::RectangleShape
    */
    sf::RectangleShape getBug();


private:
    sf::RectangleShape bug;
    void createVarible();
    void createBug();

    //Variables
    float MoveSpeed;



};

#endif // BUGBLASTER_H
