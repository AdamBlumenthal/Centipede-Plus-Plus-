#ifndef GAMEENGINE_H_INCLUDED
#define GAMEENGINE_H_INCLUDED
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "BugBlaster.h"
#include "Laser.h"
#include <vector>
#include "CentipedeSegment.h"
#include "Mushroom.h"
#include "Flea.h"


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
    void SpawnFlea();
    void KillFlea();

    //collisions
    void LaserCollision();
    void LaserCollisionCentipede();
    void LaserCollisionHeads();
    void LaserCollisionMushrooms();
    void CollisionCentipedeMushroom();
    void CollisionBugCentipede();
    void CollisionBugPlayer();

    void MakeCentipede();
    void MakeHeads();
    void MakeMushroom(Segment segment);
    //Collisions
   // void LaserCollisionCentipede();
   // void LaserCollision();
  // int generalCollision( std::vector <Laser> a,std::vector <Mushroom> b);




private:

    sf::RenderWindow* window;
    sf::Event event;
    sf::VideoMode videomode;
    static int numberOfCentipedes;
    bool lvlBegin;
    int MaxLengthCentipede;
    int currentSegments;
    int MaxLaserCount;
    float MaxLaserDelay;
    float LaserDelay;
    int CurrentLasers;

    int MushCount;

    //Flea varibles
    int MinFleaTimeDelay;
    int FleaTimeDelay;

    bool start;
    bool gameOver;

    sf::Font font;
    sf::Text StartSplashText;

    BugBlaster BugB;//BugBlaster object
    std::vector <Laser> laser;//Laser object
    std::vector <Segment> segments;//Centipede
    std::vector <Segment> heads;//Independent centipedes
    std::vector <Mushroom*> Mush;
    std::vector <Flea*> flea;//Flea object


};
#endif // GAMEENGINE_H_INCLUDED
