//
// Created by areeb on 7/31/24.
//

#ifndef CMAKE_SFML_PROJECT_MASTER_BUTTON_H
#define CMAKE_SFML_PROJECT_MASTER_BUTTON_H
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;


class Button {
    sf::Sprite ButtonSprite;
    sf::IntRect ButtonRect;
    int state;
    sf::Font font;
    sf::Text scoreText;
    int PosX;
    int PosY;
public:
    Button(sf::Texture &SpriteSheet, int PosX, int PosY, string str, bool type = 0) {
        state = 0;
        ButtonSprite.setTexture(SpriteSheet);
        ButtonRect.width = 640;
        ButtonRect.height = 160;
        if (!type){
            ButtonRect.top = 0;
            ButtonRect.left = 0;
            ButtonSprite.setTextureRect(ButtonRect);
        }
        else {
            ButtonRect.top = 640;
            ButtonRect.left = 0;
            ButtonSprite.setTextureRect(ButtonRect);
        }
        ButtonSprite.setScale(0.5,0.5);
        ButtonSprite.setPosition(PosX,PosY);


        font.loadFromFile("../src/Assets/fonts/menuFont.ttf");
        scoreText.setFont(font);
        scoreText.setCharacterSize(55);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setString((str));
        scoreText.setPosition(PosX + PosX/4 - 40 , PosY -15);
        this->PosX = PosX;
        this->PosY = PosY;


    }
    void setState(int s){
        if (!s){
            ButtonRect.left = 0;
            scoreText.setCharacterSize(55);
            ButtonSprite.setTextureRect(ButtonRect);
        }
        else {
            ButtonRect.left = 640;
            scoreText.setCharacterSize(40);
            scoreText.setPosition(PosX + PosX/4 - 40 , PosY -5);
            ButtonSprite.setTextureRect(ButtonRect);
        }
    }
    void draw(sf::RenderWindow& window){
        window.draw(ButtonSprite);
        window.draw(scoreText);
    }

};


#endif //CMAKE_SFML_PROJECT_MASTER_BUTTON_H
