//
// Created by areeb on 7/27/24.
//

#ifndef CMAKE_SFML_PROJECT_MASTER_ENTITY_H
#define CMAKE_SFML_PROJECT_MASTER_ENTITY_H
#include <iostream>
#include <SFML/Graphics.hpp>

class Entity {
public:
    short int frame;                  //  3 Frames per Movement
    short int state;                  //  States of Character
    sf::IntRect EntityRect;
    sf::Sprite EntitySprite;
    short int PosX;
    short int PosY;
    short int Health;
    sf::Clock clock;

    Entity(sf::Texture &SpriteSheet,short int PosX, short int PosY, int Name, float ScaleFactor) {
        state = 0;
        frame = 0;
        Health = 1;
        EntitySprite.setTexture(SpriteSheet);
        EntityRect.width = 16;
        EntityRect.height = 16;

        switch (Name) {
            case 2:
                EntityRect.left = 4 * 16;
                EntityRect.top = 3 * 16;
                break;
            case 3:
                EntityRect.left = 0;
                EntityRect.top = 0;
                break;
            case 4:
                EntityRect.left = 0;
                EntityRect.top = 3 * 16;
                break;
            case 5:
                EntityRect.left = 0;
                EntityRect.top = 15 * 16;
                break;
            case 6:
                EntityRect.left = 0;
                EntityRect.top = 16 * 16;
                break;
            case 7:
                EntityRect.left = 11 * 16;
                EntityRect.top = 3 * 16;
                break;
        }
        EntitySprite.setTextureRect(EntityRect);
        EntitySprite.setScale(ScaleFactor,ScaleFactor);
        this->PosX = PosX*ScaleFactor;
        this->PosY = PosY*ScaleFactor;
        EntitySprite.setPosition(PosX,PosY);
    }

    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void move(int** ) = 0;

    short getState() const {
        return state;
    }

    virtual void setFrame() {
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
    virtual void Death(){}
    virtual void setState(int s){}
};

#endif //CMAKE_SFML_PROJECT_MASTER_ENTITY_H