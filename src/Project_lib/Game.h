//
// Created by areeb on 7/27/24.
//

#ifndef CMAKE_SFML_PROJECT_MASTER_GAME_H
#define CMAKE_SFML_PROJECT_MASTER_GAME_H


#include "GameEvent.h"
#include "Menu.h"

const int resolutionX = 16*31*3;
const int resolutionY = 48*15;
const int boxPixels = 16;

class Game {
    sf::RenderWindow window;
    int gameState;
public:
    Game(): window(sf::VideoMode(resolutionX, resolutionY), "BomberMan", sf::Style::Close | sf::Style::Titlebar) {
        Run();
    }

    void Run() {
        GameEvent handler(window);
        if (window.isOpen()) {
            handler.eventHandler();
            Menu menu(handler);

            window.clear(sf::Color::Black);
            window.display();
        }
    }
};


#endif //CMAKE_SFML_PROJECT_MASTER_GAME_H
