#include "SfAssets.hpp"
using namespace sfas;


//----------------
//RESOURCE PATH
//----------------
std::string _ResPath_ = "Resources/";

std::string sfas::rp()
{
    
#ifdef _WIN32
    return _ResPath_;
#endif
    
#ifdef __APPLE__
        return (getenv("PWD") + std::string("/") + _ResPath_);
#endif
}

void sfas::setResPath(std::string nP)
{
    _ResPath_ = nP;
}
//----------------
//END RESOURCE PATH
//----------------





//-------------
//WIDGETS
//-------------
sf::Font _sfasFont_;

//================
//    DEFAULT
//================
void Widget::display(sf::RenderWindow& window){}
void Widget::tick(sf::Window& window){}
void Widget::setPosition(float x, float y){}
void Widget::checkEvent(sf::Event event) {}
void Widget::setFont(std::string path)
{
    _sfasFont_ = sf::Font();
    _sfasFont_.loadFromFile(path);
}

void Widget::setFont(sf::Font font)
{
    font = font;
}

//================
//    WIDGET manager CLASS
//================

WidgetManager::WidgetManager()
{
     widgetStack = std::vector<Widget*>();
}

void WidgetManager::registerWidget(Widget* widget){
    widgetStack.push_back(widget);
}

void WidgetManager::clearStack() {
    widgetStack.clear();
}

void WidgetManager::tickStack(sf::RenderWindow& window) {
    for (Widget* widget : widgetStack)
    {
        widget->tick(window);
    }
}

void WidgetManager::renderStack(sf::RenderWindow& window) {
    for (Widget* widget : widgetStack)
    {
        widget->display(window);
    }
}

void WidgetManager::checkEventForStack(sf::Event event)
{
    for (Widget* widget : widgetStack)
    {
        widget->checkEvent(event);
    }
}

//================
//    BUTTON
//================

Button::Button(float x, float y, float width, float height)
{
    rect = sf::RectangleShape(sf::Vector2f(width, height));
    setPosition(x, y);
}

Button::Button(){}

void Button::tick(sf::Window& window)
{
    sf::Mouse mouse;
    sf::Vector2i mousePos = mouse.getPosition(window);

    mouseOver = (mousePos.x > x && mousePos.x < x + rect.getSize().x &&
                 mousePos.y > y && mousePos.y < y + rect.getSize().y);

    bool mouseDown = mouse.isButtonPressed(mouse.Left);

    isHeld = (mouseOver && mouseDown);

    if (usingtextures)
    {
        if (isHeld)
            rect.setTexture(&pressedTexture);
        else if (mouseDownLastTick && !mouseDown)
            rect.setTexture(&buttonTexture);
    }

    clickedOnTick = (isHeld && !mouseDownLastTick);

    mouseDownLastTick = mouseDown;
}

void Button::setColor(sf::Color color)
{
    rect.setFillColor(color);
}

void Button::setTexture(std::string defaultTextureStr, std::string pressedTextureStr)
{
    if (pressedTextureStr == "-1a")
        pressedTextureStr = defaultTextureStr;

    buttonTexture.loadFromFile(defaultTextureStr);
    pressedTexture.loadFromFile(pressedTextureStr);
    usingtextures = true;
    rect.setTexture(&buttonTexture);
}

void Button::setTexture(sf::Texture defaultTexture)
{
    usingtextures = true;
    buttonTexture = defaultTexture;
    this->pressedTexture = defaultTexture;
    rect.setTexture(&buttonTexture);
}

void Button::setTexture(sf::Texture defaultTexture, sf::Texture pressedTexture)
{
    usingtextures = true;
    buttonTexture = defaultTexture;
    this->pressedTexture = pressedTexture;
    rect.setTexture(&buttonTexture);
}

void Button::setText(std::string text, sf::Color color, int textSize)
{
    rectString.setFont(_sfasFont_);
    rectString.setString(text);
    rectString.setCharacterSize(textSize);
    rectString.setFillColor(color);
    rectString.setPosition(rect.getPosition().x + rect.getSize().x/2-rectString.getLocalBounds().width/2,
    rect.getPosition().y + rect.getSize().y / 2 - rectString.getLocalBounds().height / 2);
}

std::string Button::getText()
{
    return rectString.getString();
}

void Button::setPosition(float aX, float aY)
{
    x = aX;
    y = aY;
    rect.setPosition(x, y);
    rectString.setPosition(rect.getPosition().x + rect.getSize().x/2-rectString.getLocalBounds().width/2,
    rect.getPosition().y + rect.getSize().y / 2 - rectString.getLocalBounds().height / 2);
}

void Button::display(sf::RenderWindow& window)
{
    rectString.setFont(_sfasFont_);
    window.draw(rect);
    window.draw(rectString);
}

void Button::checkEvent(sf::Event event)
{

}

//================
//    SLIDER
//================

Slider::Slider(float x, float y, float width, float height, int min, int max)
{
    this->min = min;
    this->max = max;



    baseRect = sf::RectangleShape(sf::Vector2f(width, height));
    sliderRect = sf::RectangleShape(sf::Vector2f(5, height));
    baseRect.setFillColor(sf::Color::White);
    sliderRect.setFillColor(sf::Color::Blue);
    setPosition(x, y);
}

Slider::Slider() {
    min = 0;
    max = 1;
}

void Slider::doShowValue(bool show, sf::Color color, int size)
{
    showValue = show;
    valueString.setFillColor(color);
    valueString.setCharacterSize(size);
}

void Slider::setPosition(float x, float y)
{
    this->x = x;
    this->y = y;
    sliderRect.setPosition(x + (sliderRect.getPosition().x - baseRect.getPosition().x), y);
    baseRect.setPosition(x, y);
    valueString.setPosition(baseRect.getPosition().x + baseRect.getSize().x / 2 - valueString.getLocalBounds().width / 2,
    baseRect.getPosition().y + baseRect.getSize().y / 2 - valueString.getLocalBounds().height / 2);
}

void Slider::setColor(sf::Color baseColor, sf::Color sliderColor)
{
    baseRect.setFillColor(baseColor);
    sliderRect.setFillColor(sliderColor);
}

void Slider::setTexture(std::string baseTextureStr, std::string sliderTextureStr)
{
    baseTexture.loadFromFile(baseTextureStr);
    sliderTexture.loadFromFile(sliderTextureStr);
    baseRect.setTexture(&baseTexture);
    sliderRect.setTexture(&sliderTexture);
}

void Slider::setTexture(sf::Texture baseTexture, sf::Texture sliderTexture)
{
    this->baseTexture = baseTexture;
    this->sliderTexture = sliderTexture;

    baseRect.setTexture(&baseTexture);
    sliderRect.setTexture(&sliderTexture);
}

void Slider::tick(sf::Window& window)
{
    sf::Mouse mouse;
    sf::Vector2i mousePos = mouse.getPosition(window);

    mouseOver = (mousePos.x > x && mousePos.x < x + baseRect.getSize().x &&
                 mousePos.y > y && mousePos.y < y + baseRect.getSize().y);

    isHeld = (mouseOver && mouse.isButtonPressed(mouse.Left));

    if (isHeld)
    {
        sliderRect.setPosition(mousePos.x, sliderRect.getPosition().y);

        float perc = ((baseRect.getSize().x - (sliderRect.getPosition().x - baseRect.getPosition().x)) / baseRect.getSize().x);
        value = perc * (min - max) + max;
    }

    std::string newValueString = (showValueAsInt) ? std::to_string((int)value) : std::to_string(value);
    valueString.setString(newValueString);
    valueString.setPosition(baseRect.getPosition().x + baseRect.getSize().x / 2 - valueString.getLocalBounds().width / 2,
    baseRect.getPosition().y + baseRect.getSize().y / 2 - valueString.getLocalBounds().height / 2);
}

float Slider::getValue()
{
    return value;
}

void Slider::setValue(float newValue)
{
    value = newValue;
    sliderRect.setPosition(baseRect.getPosition().x + ((newValue-min)/(max-min)*baseRect.getSize().x), sliderRect.getPosition().y);
}

void Slider::display(sf::RenderWindow& window)
{
    window.draw(baseRect);
    if (showValue)
    {
        valueString.setFont(_sfasFont_);
        window.draw(valueString);
    }
    window.draw(sliderRect);
}

void Slider::checkEvent(sf::Event event)
{

}

//================
//    SWITCH
//================

Switch::Switch(float x, float y, float width, float height)
{
    baseRect = sf::RectangleShape(sf::Vector2f(width, height));
    baseRect.setFillColor(sf::Color::Red);

    setPosition(x, y);
    setValue(false);
}

Switch::Switch() {}

bool Switch::getValue()
{
    return value;
}

void Switch::setValue(bool newValue)
{
    value = newValue;
    if (usingTextures) {
        if (newValue)
            baseRect.setTexture(&onTexture);
        else
            baseRect.setTexture(&offTexture);
    }
    else {
        if (!newValue)
            baseRect.setFillColor(sf::Color::Red);
        else
            baseRect.setFillColor(sf::Color::Green);
    }
}

void Switch::setTexture(std::string offTextureStr, std::string onTextureStr)
{
    offTexture.loadFromFile(offTextureStr);
    onTexture.loadFromFile(onTextureStr);

    baseRect.setFillColor(sf::Color::White);
    usingTextures = true;
    setValue(value);
}
void Switch::setTexture(sf::Texture offTexture, sf::Texture onTexture)
{
    this->offTexture = offTexture;
    this->onTexture = onTexture;

    baseRect.setTexture(&offTexture);
    baseRect.setFillColor(sf::Color::White);
    usingTextures = true;
}

void Switch::tick(sf::Window& window)
{
    sf::Mouse mouse;
    sf::Vector2i mousePos = mouse.getPosition(window);

    mouseOver = (mousePos.x > x && mousePos.x < x + baseRect.getSize().x &&
        mousePos.y > y && mousePos.y < y + baseRect.getSize().y);

    isHeld = (mouseOver && mouse.isButtonPressed(mouse.Left));

    clickedOnTick = (isHeld && !mouseDownLastTick);

    if (clickedOnTick)
        setValue(!value);

    mouseDownLastTick = mouse.isButtonPressed(mouse.Left);
}


void Switch::setPosition(float aX, float aY)
{
    x = aX;
    y = aY;
    baseRect.setPosition(x, y);
    setValue(value);
}

void Switch::display(sf::RenderWindow& window)
{
    window.draw(baseRect);
}

void Switch::checkEvent(sf::Event event)
{

}

//================
//    INPUT
//================



Input::Input(float x, float y, float width, float height, sf::Color color)
{
    stringText.setFont(_sfasFont_);
    stringText.setFillColor(sf::Color::Black);

    rect = sf::RectangleShape(sf::Vector2f(width, height));
    rect.setFillColor(color);
    setPosition(x, y);
}

Input::Input() {}

void Input::tick(sf::Window& window)
{
    sf::Mouse mouse;
    sf::Vector2i mousePos = mouse.getPosition(window);

    mouseOver = (mousePos.x > x && mousePos.x < x + rect.getSize().x &&
        mousePos.y > y && mousePos.y < y + rect.getSize().y);

    clickedOnTick = (mouseOver && mouse.isButtonPressed(mouse.Left) && !mouseDownLastTick);

    if (clickedOnTick)
        inFocus = true;

    if (mouse.isButtonPressed(mouse.Left) && !mouseOver)
        inFocus = false;

    if (inFocus) {
        while (keysPressedThisTick.size() > 0)
        {
            int key = keysPressedThisTick[0];
            char keyChar = static_cast<char>(key);
            if (key == 8) {
                value = value.substr(0, value.size() - 1);
                setText(value);
            }
            else {
                value += keyChar;
                setText(value);
            }
                keysPressedThisTick.erase(keysPressedThisTick.begin(), keysPressedThisTick.begin() + 1);
        }
    }


    mouseDownLastTick = mouse.isButtonPressed(mouse.Left);
}

void Input::setTextSize(int textSize)
{
    stringText.setCharacterSize(textSize);
}

std::string Input::getText()
{
    return value;
}

void Input::setText(std::string text)
{
    value = text;
    stringText.setString(text);
    stringText.setPosition(rect.getPosition().x,
    rect.getPosition().y + rect.getSize().y / 2 - stringText.getGlobalBounds().height);
}

void Input::setTexture(sf::Texture texture)
{
    rectTexture = texture;
    rect.setTexture(&rectTexture);
}
void Input::setTexture(std::string textureStr)
{
    rectTexture.loadFromFile(textureStr);
    rect.setTexture(&rectTexture);
}

void Input::setPosition(float aX, float aY)
{
    x = aX;
    y = aY;
    rect.setPosition(x, y);
}

void Input::display(sf::RenderWindow& window)
{
    stringText.setFont(_sfasFont_);
    window.draw(rect);
    window.draw(stringText);
}

void Input::checkEvent(sf::Event event)
{
    keysPressedThisTick.clear();
    if (event.type == sf::Event::TextEntered)
    {
        if (event.text.unicode < 128)
            keysPressedThisTick.push_back(event.text.unicode);
    }
}


//============
//ANIMATION
//============



Animation::Animation(float x, float y, float width, float height)
{
    baseRect = sf::RectangleShape(sf::Vector2f(width, height));
    setPosition(x, y);
}

Animation::Animation(){}

void Animation::setPosition(float x, float y)
{
    this-> x = x;
    this-> y = y;
    baseRect.setPosition(x, y);
}

void Animation::tick(sf::Window& window)
{
    
    if(playing)
    {
    timer += clock.restart().asSeconds();
    if(timer >= aniTime/(frames.size()+1))
    {
        timer -= aniTime/(frames.size()+1);
        frame++;
        if(frame >= frames.size())
        {
            frame = 0;
            if(!loop)
                stop();
        }
        if(playing){
            baseRect.setTexture(&frames[frame]);
            
        }
    }
    }else{
        clock.restart();
    }
}

void Animation::play()
{
    frame = 0;
    timer = 0;
    playing = true;
}

void Animation::stop()
{
    playing = false;
    frame = 0;
}

void Animation::setFrames(std::vector<sf::Texture> nFrames, float time)
{
    aniTime = time;
    frames = nFrames;
    baseRect.setTexture(&frames[0]);
}

void Animation::display(sf::RenderWindow& window)
{
    window.draw(baseRect);
}
void Animation::checkEvent(sf::Event event)
{}








//====================
// CANVAS
//====================

Canvas::Canvas(float x, float y, float width, float height)
{
    rect = sf::RectangleShape(sf::Vector2f(width, height));
    setPosition(x, y);
}
Canvas::Canvas(){}

void Canvas::setPosition(float Ax, float Ay)
{
    x = Ax;
    y = Ay;
    rect.setPosition(x, y);
}
void Canvas::tick(sf::Window& window)
{
        
}
void Canvas::display(sf::RenderWindow& window)
{
    texture.loadFromImage(img);
    window.draw(rect);
}
void Canvas::checkEvent(sf::Event event){}

void Canvas::create(float width, float height)
{
    img.create(width, height);
    texture.create(width, height);
    rect.setTexture(&texture);
}


void Canvas::clear()
{
    img.create(img.getSize().x, img.getSize().y);
}

void Canvas::drawPixel(int x, int y)
{
    if(x >= 0 && x < img.getSize().x && y >= 0 && y < img.getSize().y)
        img.setPixel(x, y, brushColor);
}

void Canvas::drawRect(int x, int y, int width, int height)
{
    for(int column = 0; column < width; column++)
    {
        for(int row = 0; row < height; row++)
        {
            drawPixel(x+column, y+row);
        }
    }
}

void Canvas::drawLine(float x1, float y1, float x2, float y2)
{
    
    //float angle = atan(( x1 - x2)/(y1 - y2));
   // angle = (angle/M_PI*180) + (angle > 0 ? 0 : 360);
   // std::cout << angle << "\n";
}

sf::Vector2i Canvas::getMouseOverPixel(sf::RenderWindow &window)
{
    sf::Vector2i pos = sf::Mouse::getPosition(window);
    
    if(pos.x > x && pos.x < x + rect.getSize().x && pos.y > y && pos.y < y + rect.getSize().y){
        
        pos.x -= rect.getPosition().x;
        pos.y -= rect.getPosition().y;
        return sf::Vector2i(pos.x/(rect.getSize().x/img.getSize().x),pos.y/(rect.getSize().y/img.getSize().y));

    }
        return sf::Vector2i(-1, -1);
    
    }

//-------------
//END WIDGETS
//-------------



//--------------------
// WINDOW MACHENICS
//--------------------
Window::Window(sf::VideoMode Vmode, const std::string name)
{
    window.create(Vmode, name);
}

void Window::tick()
{
    
};


