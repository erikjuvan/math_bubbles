#include "Window.hpp"

Window::Window(int w, int h, const std::string& title, sf::Uint32 style)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;
    m_window                   = std::make_unique<sf::RenderWindow>(sf::VideoMode(w, h), title, style, settings);
    m_event                    = std::make_unique<sf::Event>();

    m_window->setFramerateLimit(30); // currently already m_running at 60 fps even without limit
}

bool Window::GetEvents(sf::Event& events)
{
    return m_window->pollEvent(events);
}

void Window::Events()
{
    while (m_window->pollEvent(*m_event)) {
        if (m_event->type == sf::Event::Closed) {
            m_window->close();
        }

        for (auto& w : m_widgets) {
            w->handle(*m_event);
        }
    }

    for (auto& w : m_objects) {
        w->update();
    }
}

void Window::Create(int w, int h, const std::string& title, sf::Uint32 style)
{
    m_window->create(sf::VideoMode(w, h), title, style);
}

void Window::Close()
{
    m_window->close();
}

void Window::Add(std::shared_ptr<Widget> const& widget)
{
    m_widgets.push_back(widget);
}

void Window::Add(std::shared_ptr<Object> const& object)
{
    m_objects.push_back(object);
}

void Window::Draw()
{
    m_window->clear(backgroundColor);

    for (const auto& w : m_widgets) {
        m_window->draw(*w);
    }

    for (const auto& o : m_objects) {
        if (o->isLive())
            m_window->draw(*o);
    }

    m_window->display();
}

void Window::Update()
{
    //Events();
    Draw();
}

void Window::SetVisible(bool visible)
{
    m_window->setVisible(visible);
}

bool Window::IsOpen() const
{
    return m_window->isOpen();
}

sf::Vector2i Window::GetPosition() const
{
    return m_window->getPosition();
}

void Window::SetPosition(const sf::Vector2i& position)
{
    m_window->setPosition(position);
}
