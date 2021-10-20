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

}



