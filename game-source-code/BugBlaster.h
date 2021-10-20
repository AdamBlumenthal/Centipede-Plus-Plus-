#ifndef BUGBLASTER_H
#define BUGBLASTER_H
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>



enum class Movement{NoMove,Up,Down, Right, Left};


class BugBlaster
{
public:
    BugBlaster(float x=350.f,float y=450.f);
    virtual ~BugBlaster();

    //functions
    Movement BugBlasterGetInputs();
    void KeyInputResults(Movement movement);
    void update(sf::RenderTarget* target);
    void render(sf::RenderTarget* target);


    void WindowCollision(sf::RenderTarget* target);
    void SetPosition(float x,float y);


    sf::FloatRect GetBugPosition();
    sf::RectangleShape getBug();


private:
    sf::RectangleShape bug;
    void createVarible();
    void createBug();

    //Varibles
    float MoveSpeed;



};

#endif // BUGBLASTER_H
