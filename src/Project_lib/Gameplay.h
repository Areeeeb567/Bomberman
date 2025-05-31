//
// Created by areeb on 7/27/24.
//

#ifndef CMAKE_SFML_PROJECT_MASTER_GAMEPLAY_H
#define CMAKE_SFML_PROJECT_MASTER_GAMEPLAY_H
#include <iostream>
#include "GameEvent.h"
#include "GameGrid.h"
#include "Player.h"
#include "Enemy.h"
#include "Ballom.h"
#include "Onil.h"

class Gameplay {
    GameEvent & handler;
    sf::RenderWindow & window;
    sf::Texture SpriteSheetTex;

public:
    Gameplay(GameEvent & handler, int &level, int& lives) : handler(handler), window(handler.getWindow()){
        window.setFramerateLimit(60);
        SpriteSheetTex.loadFromFile("../src/Assets/NewSprites.png");
        GameGrid gameGrid(SpriteSheetTex);
        Enemy** EnemyArr = new Enemy*[6];
        int Enemyloc[6][2] = {};
        setEnemyLocations(Enemyloc, gameGrid.getGrid());

        for (int i=0 ; i<6 ; i++){
            if (level == 1){
                EnemyArr[i] = new Ballom(SpriteSheetTex, Enemyloc[i][0]*16, Enemyloc[i][1]*16, 5,gameGrid.ScaleFactor);
            }
            else {
                if (i<3){
                    EnemyArr[i] = new Ballom(SpriteSheetTex, Enemyloc[i][0]*16, Enemyloc[i][1]*16, 5,gameGrid.ScaleFactor);
                }
                else {
                    EnemyArr[i] = new Onil(SpriteSheetTex, Enemyloc[i][0]*16, Enemyloc[i][1]*16, 6,gameGrid.ScaleFactor);
                }
            }
        }

        sf::Clock clock;
        sf::Text timerText;
        sf::Font font;
        font.loadFromFile("../src/Assets/fonts/JustMeAgainDownHere-Regular.ttf");
        timerText.setFont(font);
        timerText.setCharacterSize(55);
        timerText.setFillColor(sf::Color::White);
        timerText.setPosition(10, 48*13);

        sf::Text Lives;
        Lives.setFont(font);
        Lives.setCharacterSize(55);
        Lives.setFillColor(sf::Color::White);
        Lives.setPosition(48 * 8, 48*13);





        Player player(SpriteSheetTex, gameGrid.ScaleFactor);

        while (window.isOpen()){
            if (clock.getElapsedTime() >= sf::Time(sf::seconds(190)))
            window.clear(sf::Color::Black);
            handler.eventHandler();

            gameGrid.Draw(window);

            player.move(gameGrid.getGrid());
            player.draw(window);

            for (int i=0 ; i<6 ; i++){
                EnemyArr[i]->move(gameGrid.getGrid());
                EnemyArr[i]->draw(window);
            }
            for (int i=0 ; i<6 ; i++){
                if (EnemyArr[i]->Health && CheckCollision(player,*EnemyArr[i])){
                    player.setState(-1);
                }
            }
            player.bomb->Explode(gameGrid.getGrid(), player, EnemyArr);
            if(player.bomb->Health)
                player.bomb->draw(window);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
                while (sf::Keyboard::isKeyPressed(sf::Keyboard::E)){}
                Kill(EnemyArr);
            }
            sf::Time elapsed = clock.getElapsedTime();
            std::string str = "Timer: ";
            str += std::to_string(elapsed.asSeconds());
            timerText.setString(str);
//            std::cout << str[7] << str[8] << std::endl;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
                if (NextLevelCheck(player, gameGrid.getGrid(), EnemyArr, str) || !lives){
                    break;
                }
            }
            if ((level == 1 && (str[7] == '6' && str[8] == '0')) || !lives){
                lives = 0;
                break;
            }
            if (!player.Health){
                lives--;
                player.Resurrect();
            }
            gameGrid.Door();
//            std::cout << level;
            std::string str2 = "Lives: ";
            str2+=std::to_string(lives);
            Lives.setString(str2);
            if (level == 1){
                window.draw(timerText);
            }
            window.draw(Lives);

            window.display();
            window.clear();
        }
    }
    bool NextLevelCheck(Player& player, int** Grid, Enemy** EnemyArr, std::string& str){
        for (int i=0 ; i<6 ; i++){
            if (EnemyArr[i]->Health)
                return false;
        }
        if ((Grid[(player.PosY) / (16*3)][(player.PosX-2) / (16*3)] == 7) && (Grid[(player.PosY+47) / (16*3)][(player.PosX-2) / (16*3)] ==7))
            return true;
        if ((Grid[(player.PosY) / (16*3)][(player.PosX+50) / (16*3)] == 7) && (Grid[(player.PosY+47) / (16*3)][(player.PosX+50) / (16*3)] ==7))
            return true;
        if ((Grid[(player.PosY-2) / (16*3)][(player.PosX) / (16*3)] == 7) && (Grid[(player.PosY+2) / (16*3)][(player.PosX+47) / (16*3)] == 7))
            return true;
        if ((Grid[(player.PosY+50) / (16*3)][(player.PosX) / (16*3)] == 7) && (Grid[(player.PosY+50) / (16*3)][(player.PosX+47) / (16*3)] == 7))
            return true;
        return false;
    }
    bool CheckCollision(Entity &player, Entity &enemy){
        if (player.PosX >= 0 && player.PosX <= 4*48 && player.PosY >= 0 && player.PosY<=4*48)
            return false;
        if ((enemy.PosX >= player.PosX && enemy.PosX <= player.PosX+48)&&(enemy.PosY >= player.PosY && enemy.PosY <= player.PosY+48)){
            return true;
        }
        if ((enemy.PosX+48 >= player.PosX && enemy.PosX+48 <= player.PosX+48)&&(enemy.PosY >= player.PosY && enemy.PosY <= player.PosY+48)){
            return true;
        }
        if ((enemy.PosX >= player.PosX && enemy.PosX <= player.PosX+48)&&(enemy.PosY+48 >= player.PosY && enemy.PosY+48 <= player.PosY+48)){
            return true;
        }
        if ((enemy.PosX+48 >= player.PosX && enemy.PosX+48 <= player.PosX+48)&&(enemy.PosY+48 >= player.PosY && enemy.PosY+48 <= player.PosY+48)){
            return true;
        }
        return false;
    }
    void Kill(Enemy** Arr){
        for (int i=0 ; i<6 ; i++){
            Arr[i]->setState(-1);
        }
    }
    void setEnemyLocations(int Arr[][2], int **Grid){
        srand(time(0));
        int count = 6;
//        for (int i=0 ; i<6 ; i++){
        int i=0;
            for (int j=0 ; j<13 ; j++) {
                for (int k = 0; k < 31; k++) {
                    if (Grid[j][k] == 0 && !(rand() % 10) && ((k+j)) && ((!((i>0 && i<=4) && (j>0 && j<=4))))) {
                        Arr[i][0] = k;
                        Arr[i++][1] = j;
                        count--;
                    }
                    if (i == 6)
                        break;
                }
                if (i == 6)
                    break;
        }
    }

};


#endif //CMAKE_SFML_PROJECT_MASTER_GAMEPLAY_H
