//
// Created by areeb on 7/27/24.
//

#ifndef CMAKE_SFML_PROJECT_MASTER_GAMEGRID_H
#define CMAKE_SFML_PROJECT_MASTER_GAMEGRID_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"


class GameGrid {
    int Row;
    int Col;
    int** Grid;
    sf::Sprite Block[4];

    //  GameGrid Index
    //  0 = Empty
    //  1 = Unbreakable Wall
    //  2 = Breakable Wall
    //  3 = Player
    //  4 = Bomb
    //  5 = Enemy 1
    //  6 = Enemy 2
    //  7 = Door

public:
    float ScaleFactor;
    int DoorLocation[2];
    int** getGrid(){
        return Grid;
    }
    GameGrid(sf::Texture &SpriteSheet, int Row = 13, int Col = 31) : Row(Row), Col(Col){
        ScaleFactor = 3;

        Block[0].setTexture(SpriteSheet);
        Block[1].setTexture(SpriteSheet);
        Block[2].setTexture(SpriteSheet);
        Block[3].setTexture(SpriteSheet);
        Block[0].setScale(ScaleFactor,ScaleFactor);
        Block[1].setScale(ScaleFactor,ScaleFactor);
        Block[2].setScale(ScaleFactor,ScaleFactor);
        Block[3].setScale(ScaleFactor,ScaleFactor);
        Block[0].setTextureRect(sf::IntRect (0,4*16,16,16));
        Block[1].setTextureRect(sf::IntRect (3*16,3*16,16,16));
        Block[2].setTextureRect(sf::IntRect (4*16,3*16,16,16));
        Block[3].setTextureRect(sf::IntRect (11*16,3*16,16,16));

        int BreakableWalls = ((Row * Col) - (2 * (Row+Col) + ((Row/2 - 1)*((Col/2) - 1))))/6;

        Grid = new int*[Row];
        for (int i=0 ; i<Row ; i++){
            Grid[i] = new int[Col];
            for (int j=0 ; j<Col ; j++){
                if (i==0 || i==Row-1 || (j%2==0 && i%2==0) || (j==0 || j==Col-1))
                    Grid[i][j] = 1;
                else
                    Grid[i][j] = 0;
            }
        }
        int Doorcount = 1;
        srand(time(0));
        for (int i=0 ; i<Row ; i++) {
            for (int j = 0; j < Col; j++) {
                if (!Grid[i][j])
                    if (!(random()%4) && BreakableWalls && (!((i>0 && i<=4) && (j>0 && j<=4)))){
                        Grid[i][j] = 2;
                        BreakableWalls--;
                        if (Doorcount && !(random()%4)){
                            Grid[i][j] = 2;
                            DoorLocation[0] = i;
                            DoorLocation[1] = j;
                            Doorcount=0;
                        }
                    }

            }
        }
        std::cout << DoorLocation[0] << " " << DoorLocation[1] << std::endl;
    }
    void Door(){
        if (Grid[DoorLocation[0]][DoorLocation[1]] == 0){
            Grid[DoorLocation[0]][DoorLocation[1]] = 7;
        }
    }
    void Draw(sf::RenderWindow &window){
        for (int i = 0; i < Row; i++) {
            for (int j = 0; j < Col; j++) {
                if (Grid[i][j] == 0) {
                    Block[0].setPosition(j * 16*3, i * 16*3); // Adjust position as needed
                    window.draw(Block[0]);
                }
                else if (Grid[i][j] == 1) {
                    Block[1].setPosition(j * 16*3, i * 16*3); // Adjust position as needed
                    window.draw(Block[1]);
                }
                else if (Grid[i][j] == 2) {
                    Block[2].setPosition(j * 16*3, i * 16*3); // Adjust position as needed
                    window.draw(Block[2]);
                }
                else if (Grid[i][j] == 7){
                    Block[3].setPosition(j * 16*3, i * 16*3); // Adjust position as needed
                    window.draw(Block[3]);
                }
            }
        }
    }
};


#endif //CMAKE_SFML_PROJECT_MASTER_GAMEGRID_H
