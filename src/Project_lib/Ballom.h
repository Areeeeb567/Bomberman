//
// Created by areeb on 7/30/24.
//

#ifndef CMAKE_SFML_PROJECT_MASTER_BALLOM_H
#define CMAKE_SFML_PROJECT_MASTER_BALLOM_H

#include "Enemy.h"

class Ballom : public Enemy {
public:
    Ballom(sf::Texture &SpriteSheet,short int X, short int Y, int Name ,float ScaleFactor) : Enemy(SpriteSheet,X,Y,5,ScaleFactor){}
};

#endif //CMAKE_SFML_PROJECT_MASTER_BALLOM_H
