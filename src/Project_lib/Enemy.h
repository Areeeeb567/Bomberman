//
// Created by areeb on 7/28/24.
//

#ifndef CMAKE_SFML_PROJECT_MASTER_ENEMY_H
#define CMAKE_SFML_PROJECT_MASTER_ENEMY_H
#include "Entity.h"
#include <iostream>

class Enemy : public Entity {
public:
    Enemy(sf::Texture &SpriteSheet,short int X, short int Y, int Name ,float ScaleFactor) : Entity(SpriteSheet,X,Y,Name,ScaleFactor) {}
    void move(int** Grid) override{
        if (!Health){
            return;
        }
        if (getState() == -1){
            Death();
            return;
        }
        if (getState() == 0){       //  Left
            if ((Grid[(PosY) / (16*3)][(PosX-2) / (16*3)] != 1) && (Grid[(PosY) / (16*3)][(PosX-2) / (16*3)] != 2) && (Grid[(PosY+47) / (16*3)][(PosX-2) / (16*3)] != 1)  && (Grid[(PosY+47) / (16*3)][(PosX-2) / (16*3)] != 2)){
                PosX -= 1;
                setState(0);
                setFrame();
            }
            else {
                setState(random()%4);
            }
        }
        else if (getState() == 1){  //  Down
            if ((Grid[(PosY+50) / (16*3)][(PosX) / (16*3)] != 1) && (Grid[(PosY+50) / (16*3)][(PosX) / (16*3)] != 2) && (Grid[(PosY+50) / (16*3)][(PosX+47) / (16*3)] != 1)  && (Grid[(PosY+50) / (16*3)][(PosX+47) / (16*3)] != 2)){
                PosY += 1;
                setState(1);
                setFrame();
            }
            else {
                setState(random()%4);
            }
        }
        else if (getState() == 2){  //  Right
            if ((Grid[(PosY) / (16*3)][(PosX+50) / (16*3)] != 1) && (Grid[(PosY) / (16*3)][(PosX+50) / (16*3)] != 2) && (Grid[(PosY+47) / (16*3)][(PosX+50) / (16*3)] != 1)  && (Grid[(PosY+47) / (16*3)][(PosX+50) / (16*3)] != 2)){
                PosX += 1;
                setState(2);
                setFrame();
            }
            else {
                setState(random()%4);
            }
        }
        else if (getState() == 3){  //  Up
            if ((Grid[(PosY-2) / (16*3)][(PosX) / (16*3)] != 1) && (Grid[(PosY-2) / (16*3)][(PosX) / (16*3)] != 2) && (Grid[(PosY+2) / (16*3)][(PosX+47) / (16*3)] != 1)  && (Grid[(PosY+2) / (16*3)][(PosX+47) / (16*3)] != 2)){
                PosY -= 1;
                setState(3);
                setFrame();
            }
            else {
                setState(random()%4);
            }
        }
        EntitySprite.setPosition(PosX,PosY);


    }
    void draw(sf::RenderWindow &window) override{
        window.draw(EntitySprite);
    }
    void setState(int s) override {
        state = s;
        if (s == 0){
            EntityRect.left = 16*3;
            EntityRect.top = 16*15;
            if (PosY%48 >= 0 && PosY%48 <= 12)
                PosY -= PosY%48;
            else if (PosY%48 >= 38 && PosY%48 <= 47)
                PosY += 48 - PosY%48;
        }
        else if (s == 1){
            EntityRect.left = 16*3;
            EntityRect.top = 16*15;
            if (PosX%48 >= 0 && PosX%48 <= 12)
                PosX -= PosX%48;
            else if (PosX%48 >= 38 && PosX%48 <= 47)
                PosX += 48 - PosX%48;
        }
        else if (s == 2){
            EntityRect.left = 0;
            EntityRect.top = 16*15;
            if (PosY%48 >= 0 && PosY%48 <= 12)
                PosY -= PosY%48;
            else if (PosY%48 >= 38 && PosY%48 <= 47)
                PosY += 48 - PosY%48;
        }
        else if (s == 3){
            EntityRect.left = 0;
            EntityRect.top = 16*15;
            if (PosX%48 >= 0 && PosX%48 <= 12)
                PosX -= PosX%48;
            else if (PosX%48 >= 38 && PosX%48 <= 47)
                PosX += 48 - PosX%48;
        }
        else if (s == -1){
            EntityRect.left = 6*16;
            EntityRect.top = 16*15;
        }
    }
    void Death() override {
        if (clock.getElapsedTime() >= sf::milliseconds(200)){
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
};


#endif //CMAKE_SFML_PROJECT_MASTER_ENEMY_H
