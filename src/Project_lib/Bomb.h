//
// Created by areeb on 7/27/24.
//

#ifndef CMAKE_SFML_PROJECT_MASTER_BOMB_H
#define CMAKE_SFML_PROJECT_MASTER_BOMB_H
#include <iostream>
#include "Entity.h"
#include "Enemy.h"

class Bomb : public Entity {
    short int PlaceX;
    short int PlaceY;
    sf::Clock BombClock;
public:
    Bomb(sf::Texture &SpriteSheet, float ScaleFactor) : Entity(SpriteSheet,-1,-1,4,ScaleFactor) {
        Health = 0;
    }
    void draw(sf::RenderWindow &window) override{
        window.draw(EntitySprite);
    }
    void move(int **) override {}
    void Detonate(Entity &player){
        if (!Health){
//            std::cout << "Started" << std::endl;
            PosX = ((player.PosX+24) / 48) * 48;
            PosY = ((player.PosY+24) / 48) * 48;
            PlaceX = PosX;
            PlaceY = PosY;
            Health = 1;
            EntitySprite.setPosition(PlaceX,PlaceY);
        }
    }
    void Explode(int** Grid, Entity &player, Enemy** EnemyArr) {
        if (BombClock.getElapsedTime() >= sf::Time(sf::seconds(8)) && Health){
            std::cout << "Started" << std::endl;
            if (CheckCollision(player))
                player.setState(-1);
            for (int i=0 ; i<6 ; i++){
                if (CheckCollision(*EnemyArr[i])){
                    std::cout << "Kill" << std::endl;
                    EnemyArr[i]->setState(-1);
                }
            }
            if (Grid[(PosY - 48) / 48][PosX / 48] != 1) {
                if (Grid[(PosY - 48) / 48][PosX / 48] == 2) {
                    Grid[(PosY - 48) / 48][PosX / 48] = 0;
                } else {
                    PosY -= 48;
                    if (CheckCollision(player))
                        player.setState(-1);
                    for (int i=0 ; i<6 ; i++){
                        if (CheckCollision(*EnemyArr[i]))
                            EnemyArr[i]->setState(-1);
                    }
                    if (Grid[(PosY - (48)) / 48][PosX / 48] != 1)
                        if (Grid[(PosY - (48)) / 48][PosX / 48] == 2) {
                            Grid[(PosY - (48)) / 48][PosX / 48] = 0;
                        } else {
                            PosY -= 48;
                            if (CheckCollision(player))
                                player.setState(-1);
                            for (int i=0 ; i<6 ; i++){
                                if (CheckCollision(*EnemyArr[i]))
                                    EnemyArr[i]->setState(-1);
                            }
                            if (Grid[(PosY - (48)) / 48][PosX / 48] != 1)
                                if (Grid[(PosY - (48)) / 48][PosX / 48] == 2) {
                                    Grid[(PosY - (48)) / 48][PosX / 48] = 0;
                                }
                        }
                }
                PosY = PlaceY;
                PosX = PlaceX;
            }
            if (Grid[(PosY + 48) / 48][PosX / 48] != 1) {
                if (Grid[(PosY + 48) / 48][PosX / 48] == 2) {
                    Grid[(PosY + 48) / 48][PosX / 48] = 0;
                } else {
                    PosY += 48;
                    if (CheckCollision(player))
                        player.setState(-1);
                    for (int i=0 ; i<6 ; i++){
                        if (CheckCollision(*EnemyArr[i]))
                            EnemyArr[i]->setState(-1);
                    }
                    if (Grid[(PosY + (48)) / 48][PosX / 48] != 1)
                        if (Grid[(PosY + (48)) / 48][PosX / 48] == 2) {
                            Grid[(PosY + (48)) / 48][PosX / 48] = 0;
                        } else {
                            PosY += 48;
                            if (CheckCollision(player))
                                player.setState(-1);
                            for (int i=0 ; i<6 ; i++){
                                if (CheckCollision(*EnemyArr[i]))
                                    EnemyArr[i]->setState(-1);
                            }
                            if (Grid[(PosY + (48)) / 48][PosX / 48] != 1)
                                if (Grid[(PosY + (48)) / 48][PosX / 48] == 2) {
                                    Grid[(PosY + (48)) / 48][PosX / 48] = 0;
                                }
                        }
                }
                PosY = PlaceY;
                PosX = PlaceX;
            }
            if (Grid[(PosY) / 48][(PosX + 48) / 48] != 1) {
                if (Grid[(PosY) / 48][(PosX + 48) / 48] == 2) {
                    Grid[(PosY) / 48][(PosX + 48) / 48] = 0;
                } else {
                    PosX += 48;
                    if (CheckCollision(player))
                        player.setState(-1);
                    for (int i=0 ; i<6 ; i++){
                        if (CheckCollision(*EnemyArr[i]))
                            EnemyArr[i]->setState(-1);
                    }
                    if (Grid[(PosY) / 48][(PosX + (48)) / 48] != 1)
                        if (Grid[(PosY) / 48][(PosX + (48)) / 48] == 2) {
                            Grid[(PosY) / 48][(PosX + (48)) / 48] = 0;
                        } else {
                            PosX += 48;
                            if (CheckCollision(player))
                                player.setState(-1);
                            for (int i=0 ; i<6 ; i++){
                                if (CheckCollision(*EnemyArr[i]))
                                    EnemyArr[i]->setState(-1);
                            }
                            if (Grid[(PosY) / 48][(PosX + (48)) / 48] != 1)
                                if (Grid[(PosY) / 48][(PosX + (48)) / 48] == 2) {
                                    Grid[(PosY) / 48][(PosX + (48)) / 48] = 0;
                                }
                        }
                }
                PosY = PlaceY;
                PosX = PlaceX;
            }
            if (Grid[(PosY) / 48][(PosX - 48) / 48] != 1) {
                if (Grid[(PosY) / 48][(PosX - 48) / 48] == 2) {
                    Grid[(PosY) / 48][(PosX - 48) / 48] = 0;
                } else {
                    PosX -= 48;
                    if (CheckCollision(player))
                        player.setState(-1);
                    for (int i=0 ; i<6 ; i++){
                        if (CheckCollision(*EnemyArr[i]))
                            EnemyArr[i]->setState(-1);
                    }
                    if (Grid[(PosY) / 48][(PosX - (48)) / 48] != 1)
                        if (Grid[(PosY) / 48][(PosX - (48)) / 48] == 2) {
                            Grid[(PosY) / 48][(PosX - (48)) / 48] = 0;
                        } else {
                            PosX -= 48;
                            if (CheckCollision(player))
                                player.setState(-1);
                            for (int i=0 ; i<6 ; i++){
                                if (CheckCollision(*EnemyArr[i]))
                                    EnemyArr[i]->setState(-1);
                            }
                            if (Grid[(PosY) / 48][(PosX - (48)) / 48] != 1)
                                if (Grid[(PosY) / 48][(PosX - (48)) / 48] == 2) {
                                    Grid[(PosY) / 48][(PosX - (48)) / 48] = 0;
                                }
                        }
                }
                PosY = PlaceY;
                PosX = PlaceX;
            }
            BombClock.restart();
            Health = 0;
//        std::cout << PosX << " " << PosY << std::endl;
        }
    }
    void setFrame() override {
        if (clock.getElapsedTime() >= sf::Time(sf::seconds(4))){

        }
        if (clock.getElapsedTime() >= sf::milliseconds(100)){
            frame++;
            if (frame >= 3){
                frame = 0;
                EntityRect.left -= 16;
            }
            EntityRect.left += 16;
            EntitySprite.setTextureRect(EntityRect);
            clock.restart();
        }
    }
    bool CheckCollision(Entity &player){
        if ((PosX >= player.PosX && PosX <= player.PosX+48)&&(PosY >= player.PosY && PosY <= player.PosY+48)){
            return true;
        }
        if ((PosX+48 >= player.PosX && PosX+48 <= player.PosX+48)&&(PosY >= player.PosY && PosY <= player.PosY+48)){
            return true;
        }
        if ((PosX >= player.PosX && PosX <= player.PosX+48)&&(PosY+48 >= player.PosY && PosY+48 <= player.PosY+48)){
            return true;
        }
        if ((PosX+48 >= player.PosX && PosX+48 <= player.PosX+48)&&(PosY+48 >= player.PosY && PosY+48 <= player.PosY+48)){
            return true;
        }
        return false;
    }
};



#endif //CMAKE_SFML_PROJECT_MASTER_BOMB_H
