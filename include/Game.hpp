#pragma once

#include <Window.hpp>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <optional>
#include <string>
#include <thread>

// Forward decleration since including headers with said classes causes Application.hpp to be included last and we get bunch of "variable undefined" errors
// TODO: check into it
class MainWindow;

class Raindrop : public Object
{
private:
    float              delta_move{2.f};
    sf::RectangleShape m_shape;
    sf::Text           m_text;
    sf::Font           m_font;
    int                result{0};
    char               sign{0}; // 0+ 1- 2* 3/

public:
    Raindrop()
    {
        m_shape.setFillColor(sf::Color(64, 128, 128));
        m_shape.setPosition(sf::Vector2f(50 + rand() % 750, 0));
        m_shape.setSize(sf::Vector2f(90.f, 30.f));

        m_font.loadFromFile("segoeui.ttf");
        m_text.setFont(m_font);
        sign  = rand() % 4;
        int a = 1 + rand() % 30;
        int b = 1 + rand() % 30;
        switch (sign) {
        case 0:
            sign   = '+';
            result = a + b;
            break;
        case 1:
            sign = '-';
            if (a < b) {
                int tmp = a;
                a       = b;
                b       = tmp;
            }
            result = a - b;
            break;
        case 2:
            sign   = '*';
            a      = 1 + rand() % 15;
            b      = 1 + rand() % 15;
            result = a * b;
            break;
        case 3:
            sign = '/';
            a    = 1 + rand() % 100;
            b    = 1 + rand() % 100;
            if (a < b) {
                int tmp = a;
                a       = b;
                b       = tmp;
            }
            result = a / b;
            a      = result * b;
            result = a / b;
            break;
        }
        m_text.setString(std::to_string(a) + sign + std::to_string(b));
        m_text.setCharacterSize(20);
        auto loc = m_shape.getPosition();
        loc.y += delta_move;
        m_shape.setPosition(loc);
        m_text.setPosition(loc.x + m_shape.getLocalBounds().width / 2.f - m_text.getLocalBounds().width / 2.f, loc.y);

        m_live = true;
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(m_shape);
        target.draw(m_text);
    }

    void update()
    {
        auto loc = m_shape.getPosition();
        loc.y += delta_move;
        m_shape.setPosition(loc);
        m_text.setPosition(loc.x + m_shape.getLocalBounds().width / 2.f - m_text.getLocalBounds().width / 2.f, loc.y);

        if (loc.y > 670)
            m_live = false;
    }

    int getResult() const
    {
        return result;
    }
};

class Game
{
private:
    // Members
    std::unique_ptr<MainWindow> m_mainWindow;

    std::shared_ptr<bool> m_running;

    std::vector<std::shared_ptr<Raindrop>> m_raindrops;

public:
    Game();
    ~Game();

    void Run();
    void Update();
};