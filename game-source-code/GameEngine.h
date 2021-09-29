#ifndef GAMEENGINE_H_INCLUDED
#define GAMEENGINE_H_INCLUDED
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "BugBlaster.h"
#include "Laser.h"
#include <vector>
#include "CentipedeSegment.h"


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
    void splashScreen();
    void update();
    void render();
    void UpdateEvent();
    void ShootLaser();
    void LaserCollision();
    void MakeCentipede();
    bool startup();
    void displaystart();
private:

    sf::RenderWindow* window;
    sf::Event event;
    sf::VideoMode videomode;
    int MaxLaserCount;
    float MaxLaserDelay;
    float LaserDelay;
    int CurrentLasers;
    bool noNewCentipede=false;
    bool start=true;
    sf::Font font;
	sf::Text StartSplashText;
   // Segment segment;
    BugBlaster BugB;//BugBlaster object
    std::vector <Laser> laser;//Laser object
    std::vector <Segment> segments;

};
#endif // GAMEENGINE_H_INCLUDED
