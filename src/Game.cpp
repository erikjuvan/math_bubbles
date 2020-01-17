#include "Game.hpp"
#include "MainWindow.hpp"
#include <fstream>
#include <future>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std::chrono_literals;

class Label : public Widget
{
    const int m_margin{5};

    sf::Font m_font;
    sf::Text m_text;

    bool m_mouseover{false};

public:
    Label()
    {
        m_font.loadFromFile("segoeui.ttf");
        m_text.setFont(m_font);
        m_text.setPosition(sf::Vector2f(830, 10));
    }

    virtual void handle(const sf::Event& event) override
    {
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(m_text);
    }

    void setText(std::string text)
    {
        m_text.setString(text);
    }
};

void Game::Update()
{
    if (m_raindrops.size() <= 0)
        return;

    auto it = m_raindrops.begin();
    while (it != m_raindrops.end()) {
        (*it)->update();
        if ((*it)->isLive())
            ++it;
        else {
            it = m_raindrops.erase(it);
        }
    }
}

void Game::Run()
{
    sf::Event              events;
    std::shared_ptr<Label> guess_label = std::make_shared<Label>();
    int                    i           = 0;
    int                    next_cnt    = 50 + rand() % 100;
    int                    guess       = 0;
    int                    guess_idx   = 0;

    m_mainWindow->Add(guess_label);

    while (m_mainWindow->IsOpen()) {
        m_mainWindow->Update();
        Update();

        if (++i % next_cnt == 0) {
            m_raindrops.push_back(std::make_shared<Raindrop>());
            m_mainWindow->Add(m_raindrops.back());
            i        = 0;
            next_cnt = 10 + rand() % 60;
        }

        // check events
        while (m_mainWindow->GetEvents(events)) {
            if (events.type == sf::Event::Closed) {
                m_mainWindow->Close();
            }

            if (events.type == sf::Event::KeyReleased) {
                if (events.key.code == sf::Keyboard::Delete) {
                    guess     = 0;
                    guess_idx = 0;
                }

                if (events.key.code >= sf::Keyboard::Numpad0 &&
                    events.key.code <= sf::Keyboard::Numpad9) {

                    int number = events.key.code - sf::Keyboard::Numpad0;

                    guess *= 10;
                    guess += number;
                    guess_idx++;
                }

                if (events.key.code == sf::Keyboard::Enter) {
                    bool correct = false;
                    auto it      = m_raindrops.begin();
                    while (it != m_raindrops.end()) {
                        if ((*it)->isLive() && guess == (*it)->getResult()) {
                            (*it)->Live(false);
                            correct = true;
                        } else
                            ++it;
                    }
                    guess     = 0;
                    guess_idx = 0;
                }

                guess_label->setText(std::to_string(guess));
            }
        }
    }
}

Game::Game()
{
    // Set state variables
    m_running = std::make_shared<bool>(false);

    // Create main window
    m_mainWindow = std::make_unique<MainWindow>(900, 700, "Sorting Control", sf::Style::None | sf::Style::Close);

    // Now that all objects are created pass all neccessary data to mainwindow
    m_mainWindow->ConnectCrossData(m_running);

    // seed a random number generator
    srand(std::chrono::system_clock::now().time_since_epoch().count());
}

Game::~Game()
{
}