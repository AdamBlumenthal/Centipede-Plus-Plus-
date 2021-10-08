#ifndef GAMEENGINE_H_INCLUDED
#define GAMEENGINE_H_INCLUDED
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "BugBlaster.h"
#include "Laser.h"
#include <vector>
#include "CentipedeSegment.h"
#include "Mushroom.h"


class Game
{
public:


    //Constructor
    Game();
    virtual ~Game();

    //Checks
    const bool IsRunning() const;

    //Functions
    void createVarible();
    void createWindow();
    void update();
    void render();
    void UpdateEvent();
    void ShootLaser();
    void MakeCentipede();

    //Collisions
    void LaserCollisionCentipede();
    void LaserCollision();
    void LaserCollisionMushrooms();

private:

    sf::RenderWindow* window;
    sf::Event event;
    sf::VideoMode videomode;

    int MaxLaserCount;
    float MaxLaserDelay;
    float LaserDelay;
    int CurrentLasers;

    int MushCount;

    bool start=true;

    sf::Font font;
    sf::Text StartSplashText;

    BugBlaster BugB;//BugBlaster object
    std::vector <Laser> laser;//Laser object
    std::vector <Segment> segments;//Centipede
    std::vector <Mushroom*> Mush;

};
#endif // GAMEENGINE_H_INCLUDED
