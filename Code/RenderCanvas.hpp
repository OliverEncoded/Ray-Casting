#ifndef RenderCanvas_hpp
#define RenderCanvas_hpp

#include "SfAssets.hpp"

struct Ray
{
    sf::Vector2f origin;
    sf::Vector2f direction;
    sf::Vector2f position;
    Ray(sf::Vector2f origin, sf::Vector2f direction);
    bool move(float inc);
};

struct square
{
    square();
    square(sf::Vector2f position, sf::Vector2f size, sf::Color color);
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Color color;
};

void createRays(std::vector<Ray>& rays, float raySeperation, sf::Vector2i pos);
void runRayPath(Ray ray, sfas::Canvas &c, std::vector<square> &squares, int rayLength, bool showRayPath, bool doReflections);

#endif
