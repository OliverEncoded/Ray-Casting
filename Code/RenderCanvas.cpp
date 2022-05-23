#include "RenderCanvas.hpp"

using namespace sfas;

bool flag = true;
    Ray::Ray(sf::Vector2f origin, sf::Vector2f direction)
    {
        this->origin = origin;
        this->direction = direction;
        this->position = origin;
    }
    
    bool Ray::move(float inc)
    {
        return false;
    }


    square::square(){}
    square::square(sf::Vector2f position, sf::Vector2f size, sf::Color color)
    {
        this->position = position;
        this->size = size;
        this->color = color;
    }


void createRays(std::vector<Ray>& rays, float raySeperation, sf::Vector2i pos)
{
    raySeperation = 0.4;
    //  x*1/(x+y)
    rays.clear();
    for(float x = -1; x <= 1; x += raySeperation)
    {
        for(float y = -1; y <= 1; y+= raySeperation)
        {
            rays.push_back(Ray(sf::Vector2f(pos.x,pos.y) , sf::Vector2f(x, y)));
        }
    }
}

void runRayPath(Ray ray, Canvas &c, std::vector<square> &squares, int rayLength, bool showRayPath, bool doReflections)
{
    std::cout << rayLength << "\n";
    double traveled = 0;
   // for(int i = 0; i <= rayLength; i++)
    while(traveled < rayLength)
    {
        std::cout << traveled << "\n";
        traveled += fabs(ray.direction.x) + fabs(ray.direction.y);
      //  if(traveled > rayLength)
        //    std::cout << traveled << "\n";
        
    ray.position += sf::Vector2f(ray.direction.x, ray.direction.y);
        
        sf::Vector2f rPos = ray.position;
        
        c.brushColor = sf::Color(80, 80, 80);
        
        if(showRayPath)
        c.drawPixel(ray.position.x, ray.position.y);
        
        if(doReflections)
        {
        if(rPos.x >= 400)
            ray.direction.x *= -1;
        if(rPos.x <= 0)
            ray.direction.x *= -1;
        if(rPos.y >= 300)
            ray.direction.y *= -1;
        if(rPos.y <= 0)
            ray.direction.y *= -1;
        }
        
        bool collided = false;
        for(int sq = 0; sq < squares.size(); sq++)
        {
            square &s = squares[sq];
            sf::Vector2f sPos = s.position;
        
            
        if(rPos.x > sPos.x && rPos.x < sPos.x + s.size.x && rPos.y > sPos.y && rPos.y < sPos.y + s.size.y)
        {
            c.brushColor = s.color;
            c.drawPixel(ray.position.x, ray.position.y);
            collided = true;
            break;
        }
        }
        if (collided)
           break;
    }
}

