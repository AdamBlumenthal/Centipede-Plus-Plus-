#ifndef GAMEENGINE_H_INCLUDED
#define GAMEENGINE_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "BugBlaster.h"
#include "Laser.h"
#include <vector>
#include "CentipedeSegment.h"
#include "Mushroom.h"
#include "Flea.h"
#include "Centipede.h"
#include "CollisionControl.h"
#include "Bomb.h"
#include "Spawn.h"
#include <memory>

/** \file GameEngine.h
    \brief Contains code for constructing the Game class
 */

/** \class Game
    \brief A class that holds the game objects and controls and renders them
 */



class Game
{
public:


    //Constructor
    /** \brief The Constructor for the Game class.
    This also initializes the Starting objects and constants
    */
    Game();
    /** \brief The Destructor for the Game class.
    */
    virtual ~Game();

    //Checks
    /** \brief Checks if game is still running
        \return bool true if game is running,false if game has terminated
    */
    const bool IsRunning() const;

    //Functions
    /** \brief initializes the Starting objects in the game and constants

    */
    void createVariable();
    /** \brief Sets the conditions and parameters of the render window

    */
    void createWindow();
    /** \brief Updates the all the ojects in the game based on collisions and movments
    */
    void update();
    /** \brief Renders all of the objects in the render window

    */
    void render();
    /** \brief Polls to determine the new key inputs

    */
    void UpdateEvent();
    /** \brief Creates a Laser object to simulate the player shooting

    */
    void ShootLaser();
    /** \brief Creates a Flea object at the top of the screen
    */
    void SpawnFlea();
    /** \brief Creates a vector full of randomly placed Mushroom Objects
    */
    void SpawnMushroomField();
/** \brief Creates a Bomb Ojects based on a random chance
    */
    void SpawnBomb();


private:

    std::shared_ptr<sf::RenderWindow> window;
    sf::Event event;
    sf::VideoMode videomode;
    static int numberOfCentipedes;
    bool lvlBegin;
    int MaxLengthCentipede;
    int currentSegments;

    int Lives;

    bool start;
    bool gameOver;
    bool centMush;
    bool pause;
    Centipede centipede;

    sf::Font font;
    sf::Text StartSplashText;
    sf::Text LivesText;
    sf::RectangleShape BotLine;

    CollisionControl Collision;
    Spawn spawnobj;

    std::shared_ptr<BugBlaster> BugB;
    std::vector<std::shared_ptr<Laser>> laser;
    std::vector<std::shared_ptr<Centipede>> centipedes;
    std::vector<std::shared_ptr<Mushroom>> Mush;
    std::vector<std::shared_ptr<Flea>> flea;
    std::vector<std::shared_ptr<Bomb>> bomb;

};
#endif // GAMEENGINE_H_INCLUDED
