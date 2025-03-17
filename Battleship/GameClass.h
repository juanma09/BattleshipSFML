#pragma once
#include<iostream>
#include <time.h>
#include <vector>
#include <cmath>

struct coord
{
    int x;
    int y;
    int dir;
    bool operator==(const coord& xy)
    {
        return (x == xy.x && y == xy.y);
    }
    friend std::ostream& operator<<(std::ostream& out, const coord xy);
};


class AI
{
private:
    std::vector<std::vector<int> > probabilities;
    std::vector<std::vector<int> > miss;
    std::vector<std::vector<int> > certainties;
    bool sinks[5];
public:
    AI();
    void genProbMap();
    void calculateProbability(int x, int y);
    void countLength(int x, int y, int l);
    void addCertainties();

    void addMiss(int x, int y, int tag);
    void cleanMiss();

    void sinkShip(int i);
    coord getNext();

    void displayProbs();
};

struct ship
{
    int x;
    int y; // Starting position
    int tag;
    int length;
    int dir; // 1: horizontal; -1: vertical
    int score;
};


class battleship
{
private:
    int board[10][10];
    int rival_board[10][10] = { {0} };
    int lengths[5] = { 5, 4, 3, 3, 2 };

public:
    AI ai;
    ship ships[5];
    ship rival_ships[5];
    battleship();
    void initBoards();
    void initBoardR();
    void initializeShips(int arr[][10], ship shipArr[]);
    void initShips(bool random = true);
    void initShipsR();
    void drawShip(ship s, int arr[][10]);
    int getShip(int x, int y);
    int checkShip(int x, int y);
    int checkShipR(int x, int y);
    void changeDir(ship& s, int arr[][10]);
    void changeDirB(ship& s);
    void changePos(ship& s, int x, int y);
    bool checkShipPos(ship& s, int arr[][10]);
    void displayBoard();
    void displayShip(ship s);
    int getcoord(int x, int y);
    int getcoordR(int x, int y);
    void sinkRival(int x, int y);
    int sinkPlayer(int x, int y);
    int AIMove();
    bool checkBoard();
    bool checkBoardR();
    void clearBoard(int arr[][10]);

};
