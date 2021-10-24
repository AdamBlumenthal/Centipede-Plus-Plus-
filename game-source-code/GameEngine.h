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
#include "Centipede.h"
#include "CollisionControl.h"
#include "Bomb.h"
#include <memory>


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
    //void KillFlea();

    void SpawnBomb();

    //collisions
    //void LaserCollision();
    //void LaserCollisionCentipede();

    //new centipede
    //void LaserCollisionCentipedes(std::shared_ptr<Centipede> centipede);
    //void LaserCollisionHeads();
    //void LaserCollisionMushrooms();
    //void CollisionCentipedeMushroom();
    void CollisionBugCentipede();

    //void CollisionBugPlayer();
    //void CollisionBugFlea();
    //void CollisonLaserFlea();

    //void checkRestCollision(int,int);
    //void CentipedeSelfCollision();
    //void CentipedeCollisionMushroom(std::shared_ptr<Centipede> centipede);
    void SelfCollision();

    //void MakeMushroom(Segment segment);
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
   // int CurrentLasers;

    int MushCount;

    //Flea varibles
    int MinFleaTimeDelay;
    int FleaTimeDelay;

    //Bomb varibles
    int MinBombTimeDelay;
    int BombTimeDelay;

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
    //BugBlaster BugB;//BugBlaster object
    //std::vector <Laser> laser;//Laser object
    //std::vector <Segment> segments;//Centipede
    //std::vector <Segment> heads;//Independent centipedes
    //std::vector <Mushroom*> Mush;
    //std::vector <Flea*> flea;//Flea object
    //std::vector<int>headCount;
    //std::vector<Centipede> centipedes;
    std::shared_ptr<BugBlaster> BugB;//=std::make_shared<BugBlaster>();
    std::vector<std::shared_ptr<Laser>> laser;
    std::vector<std::shared_ptr<Centipede>> centipedes;
    std::vector<std::shared_ptr<Mushroom>> Mush;
    std::vector<std::shared_ptr<Flea>> flea;
    std::vector<std::shared_ptr<Bomb>> bomb;

};
#endif // GAMEENGINE_H_INCLUDED
