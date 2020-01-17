#pragma once

#include <deque>

#include "Game.hpp"
#include "Window.hpp"

class Textbox : public sf::Drawable
{
private:
    const int m_margin{5};

    std::shared_ptr<sf::Font> m_font;

    sf::RectangleShape m_rect;
    sf::Text           m_text;

    bool m_mouseover{false};

public:
    Textbox(int w, int h, std::shared_ptr<sf::Font> font) :
        m_font(font)
    {
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(m_rect);
        target.draw(m_text);
    }

    void Textbox::Handle(const sf::Event& event)
    {
        if (event.type == sf::Event::TextEntered && m_mouseover) {

            std::string str = m_text.getString();

            if (event.text.unicode == '\b') {
                if (str.length() > 0)
                    str.pop_back();
            } else {
                str += event.text.unicode;
            }

            // temporary text to see if the added character is too long to fit into the textbox
            sf::Text txt(m_text);
            txt.setString(str);

            if (txt.getGlobalBounds().width < (m_rect.getGlobalBounds().width - m_margin))
                m_text.setString(str);

            /*if (m_keyPress != nullptr)
                m_keyPress();*/

        } else if (event.type == sf::Event::MouseMoved) {
            if (m_rect.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                m_mouseover = true;
            } else {
                m_mouseover = false;
            }
        }
    }
};

class MainWindow : public Window
{
private:
    // Members
    const uint32_t m_Colors[10]{0xFF0000FF, 0x00FF00FF, 0x0000FFFF, 0xFFFF00FF, 0x00FFFFFF, 0xFF00FFFF, 0xFF8000FF, 0xC0C0C0FF, 0x800000FF, 0x808000FF};

    std::chrono::time_point<std::chrono::steady_clock> m_run_start_time;

    std::shared_ptr<bool> m_running;

    void textbox_input_clicked();

public:
    // Methods
    MainWindow(int w, int h, std::string const& title, sf::Uint32 style);
    ~MainWindow();

    auto const& GetRunStartTime() { return m_run_start_time; }
    void        ConnectCrossData(std::shared_ptr<bool> m_running);
};
