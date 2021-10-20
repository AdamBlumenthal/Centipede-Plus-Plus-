#include "../game-source-code/Laser.h"
#include "../game-source-code/CentipedeSegment.h"
#include "../game-source-code/BugBlaster.h"
#include "../game-source-code/GameEngine.h"
#include "../game-source-code/Flea.h"
#include "../game-source-code/CentipedeSegment.h"
#include "../game-source-code/Centipede.h"
#include "../game-source-code/Mushroom.h"
#include "../game-source-code/CollisionControl.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("Outline Thickness of Segment ")
{
    float argument=0.f;
    Segment segment(argument);
    auto seg=segment.getSegment();
    CHECK(seg.getOutlineThickness()==1.f);
}
TEST_CASE("Segment y position starts at zero")
{
    float argument=0.f;
    Segment segment(argument);
    auto seg=segment.getSegment();
    CHECK(seg.getPosition().y==0.f);
}
TEST_CASE("Fill Colour of sement is not green")
{
    float argument=0.f;
    Segment segment(argument);
    auto seg=segment.getSegment();
    CHECK_FALSE(seg.getFillColor()==sf::Color::Green);

}


TEST_CASE("Check bug does not start at y=0")
{

    BugBlaster bugBlast;
    auto bug=bugBlast.getBug();
    CHECK_FALSE(bug.getPosition().y==0.f);
}
TEST_CASE("Bug bounds are bigger than segment bounds  in width")
{

    float argument=0.f;
    Segment segment(argument);
    auto seg=segment.getSegment();
    BugBlaster bugBlast;
    auto bug=bugBlast.getBug();
    CHECK_FALSE(bug.getGlobalBounds().width<seg.getGlobalBounds().width);
}
TEST_CASE("Test laser starts on bug blaster")
{

    BugBlaster bugBlast;
    auto bug=bugBlast.getBug();
    Laser laser(bug.getGlobalBounds());
    auto laserBeam=laser.getLaser();
    CHECK(bug.getPosition().y==laserBeam.getPosition().y);
}
TEST_CASE("Width of bug is 24 times greater than width of laser")
{
    BugBlaster bugBlast;
    auto bug=bugBlast.getBug();
    Laser laser(bug.getGlobalBounds());
    auto laserBeam=laser.getLaser();
    CHECK(bug.getGlobalBounds().width==24*laserBeam.getGlobalBounds().width);
}

    TEST_CASE("The colour of the outline of segments is the same colour as laser beams")
{

    float argument=0.f;
    Segment segment(argument);
    auto seg=segment.getSegment();
    BugBlaster bugBlast;
    auto bug=bugBlast.getBug();
    Laser laser(bug.getGlobalBounds());
    auto laserBeam=laser.getLaser();
    CHECK(seg.getOutlineColor()==laserBeam.getFillColor());
}
TEST_CASE("Bug spawns within the x axis window bounds"){
    BugBlaster bugBlast;
    auto bug=bugBlast.getBug();
    CHECK((bug.getPosition().x>=0&&bug.getPosition().x<=800));
}
TEST_CASE("Bug spawns outside its y axis window bounds"){

    BugBlaster bugBlast;
    auto bug=bugBlast.getBug();
    CHECK_FALSE((bug.getPosition().y<450.f&&bug.getPosition().x>600));
}

//Movement Checks

TEST_CASE("Bug Moves to the right by set movespeed"){
    BugBlaster bugBlast(0,0);
    bugBlast.KeyInputResults(Movement::Right);
    CHECK(bugBlast.GetBugPosition().left==5.f);
}

TEST_CASE("Bug Moves to the left by set movespeed"){
    BugBlaster bugBlast(0,0);
    bugBlast.KeyInputResults(Movement::Left);
    CHECK(bugBlast.GetBugPosition().left==-5.f);
}

TEST_CASE("Bug Moves Up by set movespeed"){
    BugBlaster bugBlast(0,0);
    bugBlast.KeyInputResults(Movement::Up);
    CHECK(bugBlast.GetBugPosition().top==-5.f);
}

TEST_CASE("Bug Moves Down by set movespeed"){
    BugBlaster bugBlast(0,0);
    bugBlast.KeyInputResults(Movement::Down);
    CHECK(bugBlast.GetBugPosition().top==5.f);
}
TEST_CASE("Flea moves Down by set movespeed"){
    Flea flea;
    flea.FleaMove();
    CHECK(flea.GetFleaPosition().top==5.f);
}

TEST_CASE("Centipede moves across by set movespeed"){
    Centipede centipede(1,2.f,0.f);
    centipede.Move();
    //While movement speed is 2 there is a -1.f offset because of the outline
    CHECK(centipede.GetCentipedeHeadPosition().left==1.f);
}
TEST_CASE("Segment moves down when hit by Mushroom/Wall by set vertical movespeed"){
    //While movement speed is 2 there is a -1.f offset because of the outline
    float argument=1.f;
    Segment segment(argument);
    segment.moveMushroom();
    CHECK(segment.GetSegmentPosition().top==19.f);
    segment.moveDirections();
    //remember the -1 offset starting position
    CHECK(segment.GetSegmentPosition().left==-2.f);
}

TEST_CASE("Centipede moves down when hit mushroom/wall"){
    Centipede centipede(1,2.f,0.f);
    centipede.moveHead();
    //While movement speed is 2 there is a -1.f offset because of the outline
    CHECK(centipede.GetCentipedeHeadPosition().top==19.f);
    centipede.Move();
    CHECK(centipede.GetCentipedeHeadPosition().left==-3.f);

}
TEST_CASE("Centipede moves then hits wall and moves down - this one involves the collision"){
    Centipede centipede(1,2.f,782.f);
    centipede.Move();
    //While movement speed is 2 there is a -1.f offset because of the outline
    CHECK(centipede.GetCentipedeHeadPosition().top==19.f);
   // centipede.Move();
    //CHECK(centipede.GetCentipedeHeadPosition().left==-3.f);

}
TEST_CASE("Centipede remains in play area after the bottom of the bottom of the playable area"){
    Centipede centipede(1,2.f,400.f);
    for(int i=0;i<80;i++){
    centipede.moveHead();
    centipede.checkCentipedeBounds();
    }
    //While movement speed is 2 there is a -1.f offset because of the outline
    CHECK(centipede.GetCentipedeHeadPosition().top<600.f);
    CHECK(centipede.GetCentipedeHeadPosition().top>450.f);
   // centipede.Move();
    //CHECK(centipede.GetCentipedeHeadPosition().left==-3.f);

}
TEST_CASE("Player and Centipede collision"){
    std::shared_ptr<BugBlaster> BugB=std::make_shared<BugBlaster>(0.f,0.f);
    //std::vector <std::shared_ptr<Laser>> laser;
   // std::vector<std::shared_ptr<Mushroom>> Mush;
    //std::vector<std::shared_ptr<Flea>> flea;
    std::vector<std::shared_ptr<Centipede>> centipedes;
    centipedes.push_back(std::make_shared<Centipede>(1,2.f, 0));

    CollisionControl collision;
    collision.CollisionBugCentipede(BugB,centipedes);
    CHECK(collision.DidPlayerLoseLife()==true);


}

TEST_CASE("Player and Centipede did not collide"){
    std::shared_ptr<BugBlaster> BugB=std::make_shared<BugBlaster>(0.f,0.f);
    //std::vector <std::shared_ptr<Laser>> laser;
   // std::vector<std::shared_ptr<Mushroom>> Mush;
    //std::vector<std::shared_ptr<Flea>> flea;
    std::vector<std::shared_ptr<Centipede>> centipedes;
    centipedes.push_back(std::make_shared<Centipede>(1,2.f, 80));

    CollisionControl collision;
    collision.CollisionBugCentipede(BugB,centipedes);
    CHECK_FALSE(collision.DidPlayerLoseLife()==true);


}

TEST_CASE("Player and Flea collide"){
    std::shared_ptr<BugBlaster> BugB=std::make_shared<BugBlaster>(400.f,400.f);
   // std::vector<std::shared_ptr<Mushroom>> Mush;
    std::vector<std::shared_ptr<Flea>> flea;
    flea.push_back(std::make_shared<Flea>());
    flea.at(0)->setFleaPosition(400.f, 400.f);


    CollisionControl collision;
    collision.CollisionBugFlea(BugB,flea);
    CHECK(collision.DidPlayerLoseLife()==true);

}
TEST_CASE("Centipede and Mushroom collide"){

  std::vector<std::shared_ptr<Mushroom>> Mush;
   auto x=79.f;
   auto y=0.f;
  Mush.push_back(std::make_shared<Mushroom>(x,y));

   std::vector<std::shared_ptr<Centipede>> centipedes;
   centipedes.push_back(std::make_shared<Centipede>(1,2.f, 78));

   CollisionControl collision;

    collision.CentipedeCollisionMushroom(centipedes,Mush);
    centipedes.at(0)->Move();
   CHECK(centipedes.at(0)->GetCentipedeHeadPosition().top+1==20.f);
//
}

TEST_CASE("Laser collision with top of playable area"){
    std::shared_ptr<BugBlaster> BugB=std::make_shared<BugBlaster>(0.f,0.f);
    std::vector <std::shared_ptr<Laser>> laser;

    laser.push_back(std::make_shared<Laser>(BugB->GetBugPosition()));
    CollisionControl collision;
    collision.LaserCollision(laser);
    CHECK(laser.empty());


}
TEST_CASE("Laser collision centipede spawns a mushroom"){
    std::shared_ptr<BugBlaster> BugB=std::make_shared<BugBlaster>(0.f,1.f);
    std::vector <std::shared_ptr<Laser>> laser;
    std::vector<std::shared_ptr<Mushroom>> Mush;

    std::vector<std::shared_ptr<Flea>> flea;

    std::vector<std::shared_ptr<Centipede>> centipedes;
   centipedes.push_back(std::make_shared<Centipede>(1,2.f,0.f));


    laser.push_back(std::make_shared<Laser>(BugB->GetBugPosition()));
    CollisionControl collision;
    collision.LaserCollisionCentipedes(laser,centipedes,Mush);
    CHECK(!Mush.empty());


}
TEST_CASE("Laser collision centipede creates new centipede if hit non end segment"){
    std::shared_ptr<BugBlaster> BugB=std::make_shared<BugBlaster>(50.f,1.f);
    std::vector <std::shared_ptr<Laser>> laser;
    std::vector<std::shared_ptr<Mushroom>> Mush;

    std::vector<std::shared_ptr<Flea>> flea;

    std::vector<std::shared_ptr<Centipede>> centipedes;
   centipedes.push_back(std::make_shared<Centipede>(3,2.f,60.f));


    laser.push_back(std::make_shared<Laser>(BugB->GetBugPosition()));
    CollisionControl collision;
    collision.LaserCollisionCentipedes(laser,centipedes,Mush);
    CHECK(centipedes.size()>1);


}
TEST_CASE("Laser collision mushroom until destroyed"){
    std::shared_ptr<BugBlaster> BugB=std::make_shared<BugBlaster>(50.f,1.f);
    std::vector <std::shared_ptr<Laser>> laser;
    std::vector<std::shared_ptr<Mushroom>> Mush;
    Mush.push_back(std::make_shared<Mushroom>(50.f,0.f));
    //std::vector<std::shared_ptr<Flea>> flea;
 CollisionControl collision;
   // std::vector<std::shared_ptr<Centipede>> centipedes;
   //centipedes.push_back(std::make_shared<Centipede>(3,2.f,60.f));
    for(int i=0;i<4;i++){
    laser.push_back(std::make_shared<Laser>(BugB->GetBugPosition()));

    }

    collision.LaserCollisionMushrooms(laser,Mush);
    CHECK(Mush.empty());


}

TEST_CASE("Laser collision flea"){
    std::shared_ptr<BugBlaster> BugB=std::make_shared<BugBlaster>(50.f,1.f);
    std::vector <std::shared_ptr<Laser>> laser;
    //std::vector<std::shared_ptr<Mushroom>> Mush;

    std::vector<std::shared_ptr<Flea>> flea;
     flea.push_back(std::make_shared<Flea>());
    flea.at(0)->setFleaPosition(50.f, 0.f);
    //std::vector<std::shared_ptr<Centipede>> centipedes;
   //centipedes.push_back(std::make_shared<Centipede>(3,2.f,60.f));


    laser.push_back(std::make_shared<Laser>(BugB->GetBugPosition()));
    CollisionControl collision;
    collision.CollisionLaserFlea(laser,flea);
    CHECK(flea.empty());

}

TEST_CASE("Flea collision with bottom of playable area"){
    std::vector <std::shared_ptr<Flea>> flea;

    flea.push_back(std::make_shared<Flea>());
    flea.at(0)->setFleaPosition(50.f, 900.f);
    CollisionControl collision;
    collision.CollisionFleaEdge(flea);
    CHECK(flea.empty());


}
