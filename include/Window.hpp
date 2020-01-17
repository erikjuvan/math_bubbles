#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>

class Widget : public sf::Drawable
{
protected:
    using callback_type = std::function<void()>;

    bool m_enabled{true};

public:
    virtual void handle(const sf::Event& event) = 0;
};

class Object : public sf::Drawable
{
protected:
    using callback_type = std::function<void()>;
    bool m_live{true};

public:
    virtual void update() = 0;

    void Live(bool live)
    {
        m_live = live;
    }

    bool isLive() const
    {
        return m_live;
    }
};

class Window
{
protected:
    const sf::Color backgroundColor = sf::Color(190, 220, 240);

    std::unique_ptr<sf::RenderWindow>    m_window;
    std::unique_ptr<sf::Event>           m_event;
    std::vector<std::shared_ptr<Widget>> m_widgets;
    std::vector<std::shared_ptr<Object>> m_objects;

    virtual void Events();
    virtual void Draw();

public:
    Window(int w, int h, const std::string& title, sf::Uint32 style = sf::Style::Default);

    void         Create(int w, int h, const std::string& title, sf::Uint32 style = sf::Style::Default);
    void         Close();
    void         Add(std::shared_ptr<Widget> const& widget);
    void         Add(std::shared_ptr<Object> const& object);
    void         Update();
    void         SetVisible(bool visible);
    bool         IsOpen() const;
    sf::Vector2i GetPosition() const;
    void         SetPosition(const sf::Vector2i& position);
    void         SetTitle(std::string const& title) { m_window->setTitle(title); }

    bool GetEvents(sf::Event& events);
};
