#include "Game.hpp"

int main(int argc, char* argv[])
{
    Game app;

    app.Run();

    return 0;
}

/*
#include <SFML/Graphics.hpp>

sf::Font font;

class Raindrop : public sf::Drawable
{
private:
    float delta_move{ 2.f };
    sf::RectangleShape m_shape;
    sf::Text m_text;
    //sf::Font m_font;

    bool m_live{ true };

public:
    Raindrop()
    {
        m_shape.setFillColor(sf::Color(64, 128, 128));
        m_shape.setPosition(sf::Vector2f(200, 0));
        m_shape.setSize(sf::Vector2f(100.f, 30.f));

        //m_font.loadFromFile("segoeui.ttf");
        m_text.setFont(font);
        m_text.setString("10 + 3");
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

        if (loc.y > 700)
            m_live = false;
    }

    bool isLive() const
    {
        return m_live;
    }
};

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;

    sf::RenderWindow window(sf::VideoMode(900, 700), "Math Bubbles", sf::Style::None | sf::Style::Close, settings);
    sf::Event event;
    const sf::Color bg_color(190, 220, 240);

    window.setFramerateLimit(60);

    std::vector<Raindrop> raindrops;

    font.loadFromFile("segoeui.ttf");

    //auto rd = Raindrop();
    raindrops.push_back(Raindrop());

    while (window.isOpen())
    {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(bg_color);

        // update raindrops
        auto it = raindrops.begin();
        while (it != raindrops.end())
        {
            it->update();
            if (it->isLive())
                ++it;
            else 
                it = raindrops.erase(it);
        }

        // draw raindrops
        for (auto const& r : raindrops)
        {
            window.draw(r);
        }

        window.display();
    }

}
*/