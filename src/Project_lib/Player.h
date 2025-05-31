//
// Created by areeb on 7/27/24.
//

#ifndef CMAKE_SFML_PROJECT_MASTER_PLAYER_H
#define CMAKE_SFML_PROJECT_MASTER_PLAYER_H
#include "Entity.h"
#include "Bomb.h"
#include <iostream>

class Player : public Entity{
    sf::Clock BombClock;
public:
    Bomb* bomb;
    Player(sf::Texture &SpriteSheet, float ScaleFactor) : Entity(SpriteSheet,16,16,3,ScaleFactor) {
        bomb = new Bomb(SpriteSheet,ScaleFactor);
    }
    void move(int** Grid) override{
        if (!Health)
            return;
        if (getState() == -1){
            Death();
            return;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (PosY%48 >= 0 && PosY%48 <= 12)
                PosY -= PosY%48;
            else if (PosY%48 >= 38 && PosY%48 <= 47)
                PosY += 48 - PosY%48;
            if ((Grid[(PosY) / (16*3)][(PosX-2) / (16*3)] != 1) && (Grid[(PosY) / (16*3)][(PosX-2) / (16*3)] != 2) && (Grid[(PosY+47) / (16*3)][(PosX-2) / (16*3)] != 1)  && (Grid[(PosY+47) / (16*3)][(PosX-2) / (16*3)] != 2)){
                PosX -= 2;
                setState(0);
                setFrame();
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if (PosY%48 >= 0 && PosY%48 <= 12)
                PosY -= PosY%48;
            else if (PosY%48 >= 38 && PosY%48 <= 47)
                PosY += 48 - PosY%48;
            if ((Grid[(PosY) / (16*3)][(PosX+50) / (16*3)] != 1) && (Grid[(PosY) / (16*3)][(PosX+50) / (16*3)] != 2) && (Grid[(PosY+47) / (16*3)][(PosX+50) / (16*3)] != 1)  && (Grid[(PosY+47) / (16*3)][(PosX+50) / (16*3)] != 2)){
                PosX += 2;
                setState(2);
                setFrame();
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if (PosX%48 >= 0 && PosX%48 <= 12)
                PosX -= PosX%48;
            else if (PosX%48 >= 38 && PosX%48 <= 47)
                PosX += 48 - PosX%48;
            if ((Grid[(PosY-2) / (16*3)][(PosX) / (16*3)] != 1) && (Grid[(PosY-2) / (16*3)][(PosX) / (16*3)] != 2) && (Grid[(PosY+2) / (16*3)][(PosX+47) / (16*3)] != 1)  && (Grid[(PosY+2) / (16*3)][(PosX+47) / (16*3)] != 2)){
                PosY -= 2;
                setState(3);
                setFrame();
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (PosX%48 >= 0 && PosX%48 <= 12)
                PosX -= PosX%48;
            else if (PosX%48 >= 38 && PosX%48 <= 47)
                PosX += 48 - PosX%48;
            if ((Grid[(PosY+50) / (16*3)][(PosX) / (16*3)] != 1) && (Grid[(PosY+50) / (16*3)][(PosX) / (16*3)] != 2) && (Grid[(PosY+50) / (16*3)][(PosX+47) / (16*3)] != 1)  && (Grid[(PosY+50) / (16*3)][(PosX+47) / (16*3)] != 2)){
                PosY += 2;
                setState(1);
                setFrame();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
//            if (bomb->clock.getElapsedTime() >= sf::seconds(5)){
//                while (sf::Keyboard::isKeyPressed(sf::Keyboard::X)){}
                bomb->Detonate(*this);
//            }
        }
        EntitySprite.setPosition(PosX,PosY);
//        Grid[PosY/48][PosX/48] = 3;
    }
    void draw(sf::RenderWindow &window) override{
        if (!Health)
            return;
        window.draw(EntitySprite);
    }
    void setState(int s) override {
        state = s;
        if (s == 0){
            EntityRect.left = 0;
            EntityRect.top = 0;
        }
        else if (s == 1){
            EntityRect.left = 16*3;
            EntityRect.top = 0;
        }
        else if (s == 2){
            EntityRect.left = 0;
            EntityRect.top = 16;
        }
        else if (s == 3){
            EntityRect.left = 16*3;
            EntityRect.top = 16;
        }
        else if (s == -1){
            EntityRect.left = 16*3;
            EntityRect.top = 16*2;
        }
    }
    void Death() override {
        if (clock.getElapsedTime() >= sf::milliseconds(100)){
            frame++;
            if (frame >= 3){
                 EntityRect.left = 0;
                 EntityRect.top = 4*16;
                 Health = 0;
            }
            EntityRect.left += 16;
            EntitySprite.setTextureRect(EntityRect);
            clock.restart();
        }
    }
    void Resurrect(){
        state = 0;
        frame = 0;
        Health = 1;
        EntityRect.width = 16;
        EntityRect.height = 16;
        

        PosX = 16;
        PosY = 16;
        EntityRect.left = 0;
        EntityRect.top = 0;
        EntitySprite.setTextureRect(EntityRect);
        EntitySprite.setScale(3,3);
        this->PosX = PosX*3;
        this->PosY = PosY*3;
        EntitySprite.setPosition(PosX, PosY);
    }
};


#endif //CMAKE_SFML_PROJECT_MASTER_PLAYER_H
