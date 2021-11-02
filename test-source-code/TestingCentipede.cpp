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
TEST_CASE("Segment y position starts at 1(Allows for outline to be visable)")
{
    float argument=0.f;
    Segment segment(argument);
    auto seg=segment.getSegment();
    CHECK(seg.getPosition().y==1.f);
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
TEST_CASE("Width of bug is 20 times greater than width of laser")
{
    BugBlaster bugBlast;
    auto bug=bugBlast.getBug();
    Laser laser(bug.getGlobalBounds());
    auto laserBeam=laser.getLaser();
    CHECK(bug.getGlobalBounds().width==20*laserBeam.getGlobalBounds().width);
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
TEST_CASE("Bug spawns within the x axis window bounds")
{
    BugBlaster bugBlast;
    auto bug=bugBlast.getBug();
    CHECK((bug.getPosition().x>=0&&bug.getPosition().x<=800));
}
TEST_CASE("Bug spawns outside its y axis window bounds")
{

    BugBlaster bugBlast;
    auto bug=bugBlast.getBug();
    CHECK_FALSE((bug.getPosition().y<450.f&&bug.getPosition().x>600));
}

//Movement Checks
//Bugblaster movement
TEST_CASE("Bug Moves to the right by set movespeed")
{
    BugBlaster bugBlast(0,0);
    bugBlast.KeyInputResults(Movement::Right);
    CHECK(bugBlast.GetBugPosition().left==5.f);
}

TEST_CASE("Bug Moves to the left by set movespeed")
{
    BugBlaster bugBlast(0,0);
    bugBlast.KeyInputResults(Movement::Left);
    CHECK(bugBlast.GetBugPosition().left==-5.f);
}

TEST_CASE("Bug Moves Up by set movespeed")
{
    BugBlaster bugBlast(0,0);
    bugBlast.KeyInputResults(Movement::Up);
    CHECK(bugBlast.GetBugPosition().top==-5.f);
}

TEST_CASE("Bug Moves Down by set movespeed")
{
    BugBlaster bugBlast(0,0);
    bugBlast.KeyInputResults(Movement::Down);
    CHECK(bugBlast.GetBugPosition().top==5.f);
}
TEST_CASE("Bug reamins in the same position without direction given")
{
    auto move_=Movement::NoMove;
    BugBlaster bugBlast(0,0);
    bugBlast.KeyInputResults(move_);
    CHECK(bugBlast.GetBugPosition().top==0);
    CHECK(bugBlast.GetBugPosition().left==0);
}
//Flea Movement
TEST_CASE("Flea moves Down by set movespeed")
{
    Flea flea;
    flea.FleaMove();
    CHECK(flea.GetFleaPosition().top==5.f);
}
TEST_CASE("Flea does not move horizontally")
{
    Flea flea;

    auto x=flea.GetFleaPosition().left;
    flea.FleaMove();
    CHECK(flea.GetFleaPosition().left==x);
}
//Laser movement
TEST_CASE("Laser moves vertically upwards by set movespeed"){
    BugBlaster Bug(50,50);
    Laser laser(Bug.GetBugPosition());
    laser.LaserMove();
    CHECK(laser.GetLaserPosition().top==40);
}
TEST_CASE("Laser does not move horizontally"){
    BugBlaster Bug(50,50);
    Laser laser(Bug.GetBugPosition());
    auto x=laser.GetLaserPosition().left;
    laser.LaserMove();
    CHECK(laser.GetLaserPosition().left==x);
}

//Centipede Movement
//TEST_CASE("Centipede moves across by set movespeed to the right originally for 1 segment of a centipede")
//{
//    Centipede centipede(1,2.f,0.f);
//    centipede.Move();
//    //While movement speed is 2 there is a -1.f offset because of the outline
//    CHECK(centipede.GetCentipedeHeadPosition().left==1.f);
//}
//TEST_CASE("Centipede moves across by set movespeed to the right originally for multiple segments test case 10")
//{
//    Centipede centipede(10,2.f,200.f);
//    centipede.Move();
//    //While movement speed is 2 there is a -1.f offset because of the outline
//    for(int i=0;i<10;i++){
//
//    CHECK(centipede.getCentipede().at(i).GetSegmentPosition().left==201.f-18.f*i);
//}
//}
//
//TEST_CASE("Centipede moves in opposite directiona after hitting wall/mushroom i.e. left"){
//     Centipede centipede(1,2.f,100.f);
//    centipede.setHitMushroom();
//    centipede.Move();
//    //While movement speed is 2 there is a -1.f offset because of the outline
//    CHECK(centipede.GetCentipedeHeadPosition().top==19.f);
//    CHECK(centipede.GetCentipedeHeadPosition().left==97.f);
//    centipede.Move();
//    CHECK(centipede.GetCentipedeHeadPosition().left==95.f);
//
//}
//
//TEST_CASE("Centipede segments follow head after wall/mushroom collisions length=2"){
//     Centipede centipede(2,2.f,100.f);
//
//    centipede.setHitMushroom();
//    centipede.Move();
//    auto headPos=centipede.GetCentipedeHeadPosition();
//    for(int i=0;i<9;i++)
//    centipede.Move();
//
//    //While movement speed is 2 there is a -1.f offset because of the outline
//    CHECK(centipede.getCentipede().at(1).GetSegmentPosition().top==headPos.top);
//    CHECK(centipede.getCentipede().at(1).GetSegmentPosition().left==headPos.left);
//    //CHECK(centipede.GetCentipedeHeadPosition().left==97.f);
//    //centipede.Move();
//    //CHECK(centipede.GetCentipedeHeadPosition().left==95.f);
//
//}
//TEST_CASE("Centipede switches directions after hitting mushrooms i.e. 2 changes"){
//     Centipede centipede(1,2.f,100.f);
//    centipede.setHitMushroom();
//    centipede.Move();
//    //While movement speed is 2 there is a -1.f offset because of the outline
//    CHECK(centipede.GetCentipedeHeadPosition().top==19.f);
//    CHECK(centipede.GetCentipedeHeadPosition().left==97.f);
//    centipede.Move();
//    CHECK(centipede.GetCentipedeHeadPosition().left==95.f);
//    centipede.setHitMushroom();
//    centipede.Move();
//    //While movement speed is 2 there is a -1.f offset because of the outline
//    CHECK(centipede.GetCentipedeHeadPosition().top==39.f);
//    CHECK(centipede.GetCentipedeHeadPosition().left==97.f);
//    centipede.Move();
//    CHECK(centipede.GetCentipedeHeadPosition().left==99.f);
//
//}
//TEST_CASE("Centipede moves down when hit mushroom/wall")
//{
//    Centipede centipede(1,2.f,0.f);
//    centipede.moveHead();
//    //While movement speed is 2 there is a -1.f offset because of the outline
//    CHECK(centipede.GetCentipedeHeadPosition().top==19.f);
//    centipede.Move();
//    CHECK(centipede.GetCentipedeHeadPosition().left==-3.f);
//
//}
//TEST_CASE("Centipede moves then hits wall and moves down - this one involves the collision")
//{
//    Centipede centipede(1,2.f,782.f);
//    centipede.Move();
//    //While movement speed is 2 there is a -1.f offset because of the outline
//    CHECK(centipede.GetCentipedeHeadPosition().top==19.f);
//    // centipede.Move();
//    //CHECK(centipede.GetCentipedeHeadPosition().left==-3.f);
//
//}
//TEST_CASE("Centipede switches direction after reaching bottom of play area")
//{
//    Centipede centipede(1,2.f,200.f);
//    for(int i=0; i<30; i++)
//    {
//        centipede.moveHead();
//       centipede.Move();
//
//    }
//        CHECK(centipede.getCentipede().at(0).verticalSpeed()<0);
//
//
//}
//TEST_CASE("Centipede train follows direction after reaching bottom of play area")
//{
//    Centipede centipede(2,2.f,400.f);
//    for(int i=0; i<35; i++)
//    {
//        centipede.moveHead();
//        //centipede.checkCentipedeBounds();
//        centipede.Move();
//
//    }
//        CHECK(centipede.getCentipede().at(1).getVerticalSpeed()<0);
//
//
//}
//TEST_CASE("Centipede remains in play area after the bottom of the bottom of the playable area")
//{
//    Centipede centipede(1,2.f,400.f);
//    for(int i=0; i<80; i++)
//    {
//        centipede.moveHead();
//        centipede.checkCentipedeBounds();
//        if(i>30){
//        CHECK(centipede.GetCentipedeHeadPosition().top<600.f);
//        CHECK(centipede.GetCentipedeHeadPosition().top>450.f);
//        }
//    }
//
//}
//Mushroom no movement
TEST_CASE("Tests that input arguments create the mushroom at that point")
{
   Mushroom mush(50,50);
   CHECK(mush.GetMushroomPosition().left==50.f);
    CHECK(mush.GetMushroomPosition().top==50.f);
}
//Bomb no movement
TEST_CASE("Tests that input arguments create the Bomb at that point")
{
   Bomb bomb(50,50);
   CHECK(bomb.GetBombPosition().left==50.f);
    CHECK(bomb.GetBombPosition().top==50.f);
}
//Collision Class Tests


TEST_CASE("Player and Centipede collision")
{
    std::shared_ptr<BugBlaster> BugB=std::make_shared<BugBlaster>(0.f,0.f);
    std::vector<std::shared_ptr<Centipede>> centipedes;
    centipedes.push_back(std::make_shared<Centipede>(1,2.f, 0));

    CollisionControl collision;
    collision.CollisionBugCentipede(BugB,centipedes);
    CHECK(collision.DidPlayerLoseLife()==true);


}

TEST_CASE("Player and Centipede did not collide")
{
    std::shared_ptr<BugBlaster> BugB=std::make_shared<BugBlaster>(50.f,50.f);

    std::vector<std::shared_ptr<Centipede>> centipedes;
    centipedes.push_back(std::make_shared<Centipede>(1,2.f, 80));

    CollisionControl collision;
    collision.CollisionBugCentipede(BugB,centipedes);
    CHECK_FALSE(collision.DidPlayerLoseLife()==true);


}

TEST_CASE("Player and Flea collide")
{
    std::shared_ptr<BugBlaster> BugB=std::make_shared<BugBlaster>(400.f,400.f);
    // std::vector<std::shared_ptr<Mushroom>> Mush;
    std::vector<std::shared_ptr<Flea>> flea;
    flea.push_back(std::make_shared<Flea>());
    flea.at(0)->setFleaPosition(400.f, 400.f);


    CollisionControl collision;
    collision.CollisionBugFlea(BugB,flea);
    CHECK(collision.DidPlayerLoseLife()==true);

}
TEST_CASE("Centipede and Mushroom collide")
{
    std::shared_ptr<sf::RenderWindow> window;
    std::vector<std::shared_ptr<Mushroom>> Mush;
    auto x=50.f;
    auto y=0.f;
    Mush.push_back(std::make_shared<Mushroom>(x,y));

    std::vector<std::shared_ptr<Centipede>> centipedes;
    centipedes.push_back(std::make_shared<Centipede>(1,2.f, 31.f));
    centipedes.at(0)->update(window);
    CollisionControl collision;
    collision.CentipedeCollisionMushroom(centipedes,Mush);
    centipedes.at(0)->update(window);
    CHECK(centipedes.at(0)->getMoves().at(0)==Movement::Left);

}

TEST_CASE("Laser collision with top of playable area")
{
    std::shared_ptr<BugBlaster> BugB=std::make_shared<BugBlaster>(0.f,0.f);
    std::vector <std::shared_ptr<Laser>> laser;

    laser.push_back(std::make_shared<Laser>(BugB->GetBugPosition()));
    CollisionControl collision;
    collision.LaserCollision(laser);
    CHECK(laser.empty());


}
TEST_CASE("Laser collision centipede spawns a mushroom")
{
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
TEST_CASE("Laser collision centipede creates new centipede if hit non end segment")
{
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
TEST_CASE("Laser collision mushroom until destroyed")
{
    std::shared_ptr<BugBlaster> BugB=std::make_shared<BugBlaster>(50.f,1.f);
    std::vector <std::shared_ptr<Laser>> laser;
    std::vector<std::shared_ptr<Mushroom>> Mush;
    Mush.push_back(std::make_shared<Mushroom>(50.f,0.f));
    //std::vector<std::shared_ptr<Flea>> flea;
    CollisionControl collision;
    // std::vector<std::shared_ptr<Centipede>> centipedes;
    //centipedes.push_back(std::make_shared<Centipede>(3,2.f,60.f));
    for(int i=0; i<4; i++)
    {
        laser.push_back(std::make_shared<Laser>(BugB->GetBugPosition()));

        collision.LaserCollisionMushrooms(laser,Mush);
    }

    CHECK(Mush.empty());


}

TEST_CASE("Laser collision flea")
{
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

TEST_CASE("Flea collision with bottom of playable area")
{
    std::vector <std::shared_ptr<Flea>> flea;

    flea.push_back(std::make_shared<Flea>());
    flea.at(0)->setFleaPosition(50.f, 900.f);
    CollisionControl collision;
    collision.CollisionFleaEdge(flea);
    CHECK(flea.empty());


}
TEST_CASE("Laser collision Bomb destroys Bomb")
{
    std::shared_ptr<BugBlaster> BugB=std::make_shared<BugBlaster>(50.f,1.f);
    std::vector <std::shared_ptr<Laser>> laser;

    std::vector <std::shared_ptr<Flea>> flea;
    flea.push_back(std::make_shared<Flea>());

    std::vector<std::shared_ptr<Centipede>> centipedes;
    centipedes.push_back(std::make_shared<Centipede>(1,2.f,60.f));

    std::vector<std::shared_ptr<Mushroom>> Mush;
    Mush.push_back(std::make_shared<Mushroom>(40.f,0.f));

    std::vector<std::shared_ptr<Bomb>> bomb;
    bomb.push_back(std::make_shared<Bomb>(50.f, 0.f));

    laser.push_back(std::make_shared<Laser>(BugB->GetBugPosition()));
    CollisionControl collision;
    collision.CollisionLaserBomb(laser,Mush,flea,centipedes,bomb);
    CHECK(bomb.empty());

}
TEST_CASE("Laser collision Bomb destroys Laser")
{
    std::shared_ptr<BugBlaster> BugB=std::make_shared<BugBlaster>(50.f,1.f);
    std::vector <std::shared_ptr<Laser>> laser;

    std::vector <std::shared_ptr<Flea>> flea;
    flea.push_back(std::make_shared<Flea>());

    std::vector<std::shared_ptr<Centipede>> centipedes;
    centipedes.push_back(std::make_shared<Centipede>(1,2.f,60.f));

    std::vector<std::shared_ptr<Mushroom>> Mush;
    Mush.push_back(std::make_shared<Mushroom>(40.f,0.f));

    std::vector<std::shared_ptr<Bomb>> bomb;
    bomb.push_back(std::make_shared<Bomb>(50.f, 0.f));

    laser.push_back(std::make_shared<Laser>(BugB->GetBugPosition()));
    CollisionControl collision;
    collision.CollisionLaserBomb(laser,Mush,flea,centipedes,bomb);
    CHECK(laser.empty());

}
TEST_CASE("Bomb destroys Centipedes around it")
{

    std::vector<std::shared_ptr<Centipede>> centipedes;
    centipedes.push_back(std::make_shared<Centipede>(1,2.f,108.f));

    std::vector<std::shared_ptr<Bomb>> bomb;
    bomb.push_back(std::make_shared<Bomb>(50.f, 0.f));

    CollisionControl collision;
    collision.BombCentipede(bomb,centipedes,0);
     CHECK(centipedes.at(0)->isEmpty());

}
TEST_CASE("Bomb destroys Mushrooms around it")
{

    std::vector<std::shared_ptr<Bomb>> bomb;
    bomb.push_back(std::make_shared<Bomb>(100.f, 100.f));

    std::vector<std::shared_ptr<Mushroom>> Mush;
    Mush.push_back(std::make_shared<Mushroom>(50.f,100.f));
    Mush.push_back(std::make_shared<Mushroom>(150.f,100.f));
    Mush.push_back(std::make_shared<Mushroom>(100.f,50.f));
    Mush.push_back(std::make_shared<Mushroom>(100.f,150.f));

    CollisionControl collision;
    collision.BombMushroom(bomb,Mush,0);
     CHECK(Mush.empty());
                //BombFlea(bomb,flea,k);

}
TEST_CASE("Bomb destroys Fleas around it")
{
    std::vector<std::shared_ptr<Bomb>> bomb;
    bomb.push_back(std::make_shared<Bomb>(100.f, 100.f));

    std::vector <std::shared_ptr<Flea>> flea;
    flea.push_back(std::make_shared<Flea>());
    flea.push_back(std::make_shared<Flea>());
    flea.at(0)->setFleaPosition(50.f,100.f);
    flea.at(1)->setFleaPosition(100.f,150.f);

    CollisionControl collision;
    collision.BombFlea(bomb,flea,0);
     CHECK(flea.empty());

}

TEST_CASE("Laser collision Bomb destroys all objects around bomb")
{
    std::shared_ptr<BugBlaster> BugB=std::make_shared<BugBlaster>(50.f,1.f);
    std::vector <std::shared_ptr<Laser>> laser;

    std::vector <std::shared_ptr<Flea>> flea;
    flea.push_back(std::make_shared<Flea>());
    flea.at(0)->setFleaPosition(40.f,0.f);

    std::vector<std::shared_ptr<Centipede>> centipedes;
    centipedes.push_back(std::make_shared<Centipede>(1,2.f,70.f));

    std::vector<std::shared_ptr<Mushroom>> Mush;
    Mush.push_back(std::make_shared<Mushroom>(40.f,0.f));

    std::vector<std::shared_ptr<Bomb>> bomb;
    bomb.push_back(std::make_shared<Bomb>(50.f, 0.f));

    laser.push_back(std::make_shared<Laser>(BugB->GetBugPosition()));
    CollisionControl collision;
    collision.CollisionLaserBomb(laser,Mush,flea,centipedes,bomb);
    CHECK(flea.empty());
    CHECK(Mush.empty());
    CHECK(centipedes.at(0)->isEmpty());

}


