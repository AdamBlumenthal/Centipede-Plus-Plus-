#include "../game-source-code/Laser.h"
#include "../game-source-code/CentipedeSegment.h"
#include "../game-source-code/BugBlaster.h"
#include "../game-source-code/GameEngine.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("Outline Thickness of Segment ")
{
    float argument=0.f;
    Segment segment(argument);
    auto seg=segment.getSegment();
    CHECK(seg.getOutlineThickness()==2.f);
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
//    laser.setPosition(BugBounds.left+BugBounds.width/2-2.5,BugBounds.top);
    BugBlaster bugBlast;
    auto bug=bugBlast.getBug();
    CHECK_FALSE(bug.getPosition().y==0.f);
}
TEST_CASE("Bug bounds are bigger than segment bounds  in width")
{
//    laser.setPosition(BugBounds.left+BugBounds.width/2-2.5,BugBounds.top);
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
TEST_CASE("Width of bug is 5 times greater than width of laser")
{
//    laser.setPosition(BugBounds.left+BugBounds.width/2-2.5,BugBounds.top);
    //float argument=0.f;
    //Segment segment(argument);
    //auto seg=segment.getSegment();
    BugBlaster bugBlast;
    auto bug=bugBlast.getBug();
    Laser laser(bug.getGlobalBounds());
    auto laserBeam=laser.getLaser();
    CHECK(bug.getGlobalBounds().width==5*laserBeam.getGlobalBounds().width);
}

    TEST_CASE("The colour of the outline of segments is the same colour as laser beams")
{
//    laser.setPosition(BugBounds.left+BugBounds.width/2-2.5,BugBounds.top);
    //float argument=0.f;
    //Segment segment(argument);
    //auto seg=segment.getSegment
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
    float height=450.f;
    float width=350.f;
    BugBlaster bugBlast;
    auto bug=bugBlast.getBug();
    CHECK((bug.getPosition().x>=0&&bug.getPosition().x<=800));
}
TEST_CASE("Bug spawns outside its y axis window bounds"){
    float height=450.f;
    float width=350.f;
    BugBlaster bugBlast;
    auto bug=bugBlast.getBug();
    CHECK_FALSE((bug.getPosition().y<450.f&&bug.getPosition().x>600));
}

;
