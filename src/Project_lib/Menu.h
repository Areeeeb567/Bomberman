//
// Created by areeb on 7/27/24.
//

#ifndef CMAKE_SFML_PROJECT_MASTER_MENU_H
#define CMAKE_SFML_PROJECT_MASTER_MENU_H


#include "GameEvent.h"
#include "Gameplay.h"
#include "Button.h"

class Menu {
    GameEvent & handler;
    sf::RenderWindow & window;
    Button* buttonArr[3];
public:
    Menu(GameEvent & handler): handler(handler), window(handler.getWindow()){
        sf::Texture MenuSprites;
        MenuSprites.loadFromFile("../src/Assets/MenuSprites.png");
        buttonArr[0] = new Button(MenuSprites, 572,272,"Start");
        buttonArr[1] = new Button(MenuSprites, 572,272+100,"Continue");
        buttonArr[2] = new Button(MenuSprites, 572,272+200,"Quit");
        window.setFramerateLimit(60);
        int ButtonIndex = 0;

        while (window.isOpen()){
            window.clear(sf::Color(32, 87, 47));
            this->handler.eventHandler();

            int Level = 1;
            int Lives = 3;
            SetButtonStates(ButtonIndex, buttonArr);
            for (int i=0 ; i<3 ; i++){
                buttonArr[i]->draw(window);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                while (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){}
                if (ButtonIndex == 2){
                    break;
                }
                else if (ButtonIndex == 0){
                    Gameplay gameplay(handler, Level, Lives);
                    if (Lives)
                        Gameplay gameplay2(handler, ++Level, Lives);

                    break;
                }

            }


            window.display();
        }
    }
    void SetButtonStates(int &index, Button* buttons[]){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            while (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){}
            index++;
            if (index == 3){
                index = 2;
            }
            for (int i=0 ; i<3 ; i++){
                if (i==index){
                    buttons[index]->setState(1);
                }
                else {
                    buttons[i]->setState(0);
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            while (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){}
            index--;
            if (index == -1){
                index = 0;
            }
            for (int i=0 ; i<3 ; i++){
                if (i==index){
                    buttons[index]->setState(1);
                }
                else {
                    buttons[i]->setState(0);
                }
            }
        }
    }
    ~Menu(){
        for (int i=0 ; i<3 ; i++){
            delete buttonArr[i];
            buttonArr[i] = nullptr;
        }
    }
};



#endif //CMAKE_SFML_PROJECT_MASTER_MENU_H
