//==============
//FILE TEMPLATES
//==============
/*
 
 
 
 
 */
//=============
//END TEMPLATES
//=============



#ifndef SfAssets_hpp
#define SfAssets_hpp

#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

#ifdef __APPLE__
#include "AppleResPathFinder.hpp"
#endif

namespace sfas
{

//----------------
//RESOURCE PATH
//----------------
void setResPath(std::string nP);
std::string rp();
//----------------
//END RESOURCE PATH
//----------------








//-------------
//WIDGETS
//-------------
class Widget
{
public:
    
    float x, y;
    
    static void setFont(std::string path);
    static void setFont(sf::Font font);

    bool mouseOver = false;
    bool isHeld = false;
    virtual void display(sf::RenderWindow& window);
    virtual void tick(sf::Window& window);
    virtual void setPosition(float x, float y);
    virtual void checkEvent(sf::Event event);
};

class WidgetManager
{
    std::vector<Widget*> widgetStack;
public:
    WidgetManager();
    void registerWidget(Widget* widget);
    void clearStack();
    void tickStack(sf::RenderWindow& window);
    void renderStack(sf::RenderWindow& window);
    void checkEventForStack(sf::Event event);
};

class Button : public Widget
{
    bool usingtextures = false;
    bool mouseDownLastTick = true;
    sf::Text rectString;

    sf::Texture buttonTexture;
    sf::Texture pressedTexture;
public:
    bool clickedOnTick = false;
    sf::RectangleShape rect;
    void setPosition(float x, float y);
    void tick(sf::Window& window);
    void setText(std::string text, sf::Color color, int textSize);
    std::string getText();
    void display(sf::RenderWindow& window);
    void checkEvent(sf::Event event);
    void setColor(sf::Color color);

    void setTexture(std::string defaultTexture, std::string pressedTexture = "-1a");
    void setTexture(sf::Texture defaultTexture);
    void setTexture(sf::Texture defaultTexture, sf::Texture pressedTexture);

    Button(float x, float y, float width, float height);
    Button();
};

class Slider : public Widget
{
    sf::Text valueString;
    float value = 0;
    bool showValue = false;

    sf::Texture baseTexture;
    sf::Texture sliderTexture;
public:
    int min;
    int max;

    bool showValueAsInt = false;
    sf::RectangleShape baseRect;
    sf::RectangleShape sliderRect;
    void doShowValue(bool show, sf::Color color = sf::Color::Black, int size = 30);
    void setPosition(float x, float y);
    void setColor(sf::Color baseColor, sf::Color sliderColor);
    void setTexture(std::string baseTexture, std::string sliderTexture);
    void setTexture(sf::Texture baseTexture, sf::Texture sliderTexture);
    void setValue(float newValue);
    float getValue();
    void tick(sf::Window& window);
    void display(sf::RenderWindow& window);
    void checkEvent(sf::Event event);
    Slider(float x, float y, float width, float height, int min, int max);
    Slider();
};

class Switch : public Widget
{
    bool mouseDownLastTick = true;
    bool value = false;

    sf::Texture offTexture;
    sf::Texture onTexture;

    bool usingTextures = false;
public:
    bool clickedOnTick = false;
    sf::RectangleShape baseRect;
    void setValue(bool newValue);
    bool getValue();
    void setPosition(float x, float y);
    void setTexture(std::string offTexture, std::string onTexture);
    void setTexture(sf::Texture offTexture, sf::Texture onTexture);
    void tick(sf::Window& window);
    void display(sf::RenderWindow& window);
    void checkEvent(sf::Event event);
    Switch(float x, float y, float width, float height);
    Switch();
};

class Input : public Widget
{
    bool mouseDownLastTick = true;
    sf::Text stringText;
    std::vector<int> keysPressedThisTick;
    std::string value;

    sf::Texture rectTexture;
public:
    bool inFocus = false;
    bool clickedOnTick = false;
    sf::RectangleShape rect;
    void setPosition(float x, float y);
    void tick(sf::Window& window);
    void setTextSize(int textSize);
    std::string getText();
    void setText(std::string text);
    void setTexture(sf::Texture texture);
    void setTexture(std::string texture);
    void display(sf::RenderWindow& window);
    void checkEvent(sf::Event event);
    Input(float x, float y, float width, float height, sf::Color color = sf::Color::White);
    Input();
};

class Animation : public Widget
{
    bool mouseDownLastTick = true;
    
    bool playing;
    int frame = 0;
    std::vector<sf::Texture> frames;
    
    sf::Clock clock;
    float aniTime = -1;
    float timer = 0;
public:
    bool clickedOnTick = false;
    bool loop = false;
    sf::RectangleShape baseRect;
    void play();
    void stop();
    void setFrames(std::vector<sf::Texture> nFrames, float time);
    void setPosition(float x, float y);
    void tick(sf::Window& window);
    void display(sf::RenderWindow& window);
    void checkEvent(sf::Event event);
    Animation(float x, float y, float width, float height);
    Animation();
};
 
class Canvas : public Widget
{
    bool mouseDownLastTick = true;
    
    sf::Image img;
    sf::Texture texture;
    sf::RectangleShape rect;
    
public:
    bool clickedOnTick = false;
    void setPosition(float x, float y);
    void tick(sf::Window& window);
    void display(sf::RenderWindow& window);
    void checkEvent(sf::Event event);

    void clear();
    sf::Color brushColor = sf::Color::Black;
    void drawPixel(int x, int y);
    void drawRect(int x, int y, int width, int height);
    void drawLine(float x1, float y1, float x2, float y2);
    
    sf::Vector2i getMouseOverPixel(sf::RenderWindow &window);
    
    
    void create(float width, float height);
    Canvas(float x, float y, float width, float height);
    Canvas();
};
//--------------
//END WIDGETS
//--------------




//--------------------
// WINDOW MACHENICS
//--------------------


class Window
{
public:
    Window(sf::VideoMode Vmode, const std::string name);
    void tick();
    sf::RenderWindow window;
};

}

#endif
