#include "MainWindow.hpp"
#include "Game.hpp"
#include <fstream>
#include <functional>
#include <thread>

void MainWindow::textbox_input_clicked()
{
}

MainWindow::MainWindow(int w, int h, std::string const& title, sf::Uint32 style) :
    Window(w, h, title, style)
{
    /*
    //////////////
    // Texboxes //
    //////////////
    m_textbox_input = std::make_shared<Textbox>(10, 10, m_font);

    ////////////
    // Labels //
    ////////////
    m_label_game_time = std::make_shared<sf::Text>();
    m_label_game_time->setPosition(static_cast<float>(20), static_cast<float>(20));
    m_label_game_time->setOutlineThickness(1.f);
    m_label_game_time->setString("Time: ");

    m_label_points = std::make_shared<sf::Text>();
    m_label_points->setPosition(static_cast<float>(200), static_cast<float>(20));
    m_label_points->setOutlineThickness(1.f);
    m_label_points->setString("Points: 20");   

    /////////////////
    // Main window //
    /////////////////

    // Texboxes
    Add(m_textbox_input);

    // Labels
    Add(m_label_game_time);
    Add(m_label_points);
    */
}

MainWindow::~MainWindow()
{
}

void MainWindow::ConnectCrossData(std::shared_ptr<bool> running)
{
    m_running = running;
}
