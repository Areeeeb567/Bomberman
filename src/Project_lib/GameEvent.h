//
// Created by areeb on 7/27/24.
//

#ifndef CMAKE_SFML_PROJECT_MASTER_GAMEEVENT_H
#define CMAKE_SFML_PROJECT_MASTER_GAMEEVENT_H
#include <SFML/Graphics.hpp>

class GameEvent {
    sf::RenderWindow & window;
public:
    GameEvent(sf::RenderWindow & window):window(window){};

    sf::RenderWindow & getWindow() {
        return window;
    }

    sf::Event eventHandler() {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                window.close();
            }
        }
        return e;
    }
};


#endif //CMAKE_SFML_PROJECT_MASTER_GAMEEVENT_H
