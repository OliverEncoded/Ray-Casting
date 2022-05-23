#include "SfAssets.hpp"
#include "RenderCanvas.hpp"

using namespace sfas;





float pi = 3.141592;
int main()
{
    
    
    sf::RenderWindow window(
                            sf::VideoMode(1500, 1000),
                            "Shader, wow",
                            sf::Style::Titlebar |
                            sf::Style::Close);
    
    WidgetManager widgetMan;
    
    Canvas c(0, 0, 1600, 1000);
    c.create(800, 500);
    //widgetMan.registerWidget(&c);
    
    Switch showRayPathSwitch(1275, 50, 50, 50);
    widgetMan.registerWidget(&showRayPathSwitch);
    
    Switch doReflectionsSwitch(1375, 50, 50, 50);
    widgetMan.registerWidget(&doReflectionsSwitch);
    
    Slider rayLengthSlider(1250, 150, 200, 50, 5, 400);
    rayLengthSlider.setValue(100);
    widgetMan.registerWidget(&rayLengthSlider);
    
    Slider rayLimitSlider(1250, 250, 200, 50, 1, 0.01);
    rayLimitSlider.setValue(0.1);
    widgetMan.registerWidget(&rayLimitSlider);
    
    sf::RectangleShape background(sf::Vector2f(400, 400));
    background.setFillColor(sf::Color(30, 30, 30));
    background.setPosition(1200, 0);
    
    std::vector<square> squares;
    
    bool canPlaceBox = false;
    
    float raySeperation = 0.1;
    float rayLength = 100;
    bool showRayPath = false;
    bool doReflections = false;
    
    
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            widgetMan.checkEventForStack(event);
            if(event.type == sf::Event::Closed)
                window.close();
        }
        widgetMan.tickStack(window);
        
        showRayPath = showRayPathSwitch.getValue();
        doReflections = doReflectionsSwitch.getValue();
        rayLength = rayLengthSlider.getValue();
        raySeperation = rayLimitSlider.getValue();
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            rayLimitSlider.setValue(rayLimitSlider.getValue() + 0.001);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            rayLimitSlider.setValue(rayLimitSlider.getValue() - 0.001);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            rayLengthSlider.setValue(rayLengthSlider.getValue() - 1);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            rayLengthSlider.setValue(rayLengthSlider.getValue() + 1);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
            squares.clear();
        
        
        if(canPlaceBox && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            squares.push_back(square(sf::Vector2f(c.getMouseOverPixel(window).x-25,c.getMouseOverPixel(window).y-25),sf::Vector2f(50, 50), sf::Color::Green));
            canPlaceBox = false;
        }
        
        
        c.clear();
        std::vector<Ray> rays;
        
        sf::Vector2i pixelMousePos = c.getMouseOverPixel(window);
        sf::Vector2i mp = sf::Mouse::getPosition(window);
        if(pixelMousePos.x == -1 || (mp.x > background.getPosition().x && mp.x < background.getPosition().x + background.getSize().x && mp.y > background.getPosition().y && mp.y < background.getPosition().y + background.getSize().y))
        {
            pixelMousePos = sf::Vector2i(400, 250);
        }
        
        createRays(rays, raySeperation, pixelMousePos);
        
        
        for(int r = 0; r < rays.size(); r++)
        {
            runRayPath(rays[r],
                       c,
                       squares,
                       rayLength,
                       (showRayPath || sf::Mouse::isButtonPressed(sf::Mouse::Left)),
                       (doReflections || sf::Keyboard::isKeyPressed(sf::Keyboard::R))
                       );
        }
        
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            canPlaceBox = true;
        
        window.clear();
        c.display(window);
        window.draw(background);
        widgetMan.renderStack(window);
        window.display();
    }
}
