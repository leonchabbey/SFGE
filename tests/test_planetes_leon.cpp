#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>
#include <cmath>

#define SUN_MASS 50.0f;
#define PLANET_NMB 5;

class World
{

};

class Planet
{
public:
    Planet()
    {
        
    }
    
    sf::Vector2f linearVelocity;
    sf::Vector2f position;
    float mass;
};

int main()
{
    std::list<Planet> planets;
    std::srand(30);

    sf::CircleShape sun(3.0f);
    sun.setOrigin(sf::Vector2f(3.0f, 3.0f));
    sun.setPosition(sf::Vector2f(400, 400));
    sun.setFillColor(sf::Color::Yellow);
    
    for (int i = 0; i < 5; i++) {
        Planet p;
        sf::Vector2f r = p.position - sun.getPosition();
        p.linearVelocity = sf::Vector2f() * SUN_MASS / std::sqrt(r.x*r.x + r.y*r.y);
    }

    sf::RenderWindow window(sf::VideoMode(800, 800), "My window");

    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);
        window.draw(sun);

        // end the current frame
        window.display();
    }

    return 0;
    
    system("pause");
    return 0;
}
