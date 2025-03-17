#include<iostream>
#include <time.h>
#include <cmath>
#include "GameClass.h"
using namespace std;

std::ostream& operator<<(std::ostream& out, const coord xy)
{
    out << "(" << xy.x << "," << xy.y << ")";
    return out;
}

// Constructor should initialize boards from rival and from 
battleship::battleship()
{
    initBoards();
    initializeShips(board, ships);
    initializeShips(rival_board, rival_ships);
    //displayBoard();
}
void battleship::initBoards()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            board[i][j] = -1;
            rival_board[i][j] = -1;
        }
    }
}
void battleship::initBoardR()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            rival_board[i][j] = -1;
        }
    }
}
void battleship::initializeShips(int arr[][10], ship shipArr[])
{

    for (int i = 0; i < 5; i++)
    {
        shipArr[i].length = lengths[i];
        shipArr[i].score = lengths[i];
        shipArr[i].tag = i;
        do
        {
            shipArr[i].dir = (int)pow(-1, rand() % 2);
            shipArr[i].x = rand() % 10;
            shipArr[i].y = rand() % 10;
        } while (!checkShipPos(shipArr[i], arr));
        if (checkShipPos(shipArr[i], arr))
        {
            drawShip(shipArr[i], arr);
        }
    }
}

void battleship::initShips(bool random)
{
    clearBoard(board);
    for (int i = 0; i < 5; i++)
    {
        ships[i].length = lengths[i];

        ships[i].tag = i;
        ships[i].score = lengths[i];
        do
        {
            if (random)
            {
                ships[i].dir = (int)pow(-1, rand() % 2);
                ships[i].x = rand() % 10;
                ships[i].y = rand() % 10;
            }
        } while (!checkShipPos(ships[i], board));
        if (checkShipPos(ships[i], board))
        {
            drawShip(ships[i], board);
        }
    }
}
void battleship::initShipsR()
{
    clearBoard(rival_board);
    for (int i = 0; i < 5; i++)
    {
        rival_ships[i].x = 0;
        rival_ships[i].y = 0;
    }
    for (int i = 0; i < 5; i++)
    {
        rival_ships[i].length = lengths[i];

        rival_ships[i].tag = i;
        rival_ships[i].score = lengths[i];
        do
        {
            rival_ships[i].dir = (int)pow(-1, rand() % 2);
            rival_ships[i].x = rand() % 10;
            rival_ships[i].y = rand() % 10;
        } while (!checkShipPos(rival_ships[i], rival_board));
        if (checkShipPos(rival_ships[i], rival_board))
        {
            drawShip(rival_ships[i], rival_board);
        }
    }
}

void battleship::drawShip(ship s, int arr[][10])
{
    for (int j = 0; j < s.length; j++)
    {
        if (s.dir == 1)
        {
            arr[s.x][s.y + j] = s.tag;
        }
        else if (s.dir == -1)
        {
            arr[s.x + j][s.y] = s.tag;
        }
    }
}

int battleship::getShip(int x, int y)
{
    if (getcoord(x, y) >= 0)
    {
        return getcoord(x, y);
    }
}

int battleship::checkShipR(int x, int y)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < rival_ships[i].length; j++)
        {
            if (rival_ships[i].dir == 1)
            {
                if (y == rival_ships[i].y + j && x == rival_ships[i].x)
                {
                    return i;
                }
            }
            else
            {
                if (x == rival_ships[i].x + j && y == rival_ships[i].y)
                {
                    return i;
                }
            }
        }
    }

    return -1;
}

int battleship::checkShip(int x, int y)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < ships[i].length; j++)
        {
            if (ships[i].dir == 1)
            {
                if (y == ships[i].y + j && x == ships[i].x)
                {
                    return i;
                }
            }
            else
            {
                if (x == ships[i].x + j && y == ships[i].y)
                {
                    return i;
                }
            }
        }
    }

    return -1;
}

void battleship::changeDir(ship& s, int arr[][10])
{
    // displayBoard();
    s.dir *= -1;
    if (!checkShipPos(s, arr))
    {
        cout << "Error";
        s.dir *= -1;
    }
    else
    {
        for (int j = 0; j < s.length; j++)
        {
            if (s.dir == 1)
            {
                // Delete vertical
                arr[s.x + j][s.y] = -1;
            }
            else
            {
                arr[s.x][s.y + j] = -1;
            }
        }
        drawShip(s, arr);
    }
}
void battleship::changeDirB(ship& s)
{
    s.dir *= -1;
    if (!checkShipPos(s, board))
    {
        //cout << "Error";
        s.dir *= -1;
    }
    else
    {
        for (int j = 0; j < s.length; j++)
        {
            if (s.dir == 1)
            {
                // Delete vertical
                board[s.x + j][s.y] = -1;
            }
            else
            {
                board[s.x][s.y + j] = -1;
            }
        }
        drawShip(s, board);
    }
}
void battleship::changePos(ship& s, int x, int y)
{
    // Check new position
    int tmpx = s.x, tmpy = s.y;
    s.x = x;
    s.y = y;
    if (!checkShipPos(s, board))
    {
        s.x = tmpx;
        s.y = tmpy;
        return;
    }
    else
    {
        for (int j = 0; j < s.length; j++)
        {
            if (s.dir == -1)
            {
                // Delete vertical
                board[tmpx + j][tmpy] = -1;
            }
            else
            {
                board[tmpx][tmpy + j] = -1;

            }
        }
        drawShip(s, board);
    }

}
bool battleship::checkShipPos(ship& s, int arr[][10])
{
    for (int j = 0; j < s.length; j++)
    {
        if (s.dir == 1)
        {
            if (s.y + j > 9) return false;
            if (arr[s.x][s.y + j] != -1 && arr[s.x][s.y + j] != s.tag)
            {
                return false;
            }
        }
        else if (s.dir == -1)
        {
            if (s.x + j > 9) return false;
            if (arr[s.x + j][s.y] != -1 && arr[s.x + j][s.y] != s.tag)
            {
                return false;
            }
        }

    }
    return true;
}


void battleship::displayBoard()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (board[i][j] != -1)
                cout << board[i][j] << "  ";
            else
                cout << ".  ";
        }
        cout << "\t";
        for (int j = 0; j < 10; j++)
        {
            if (rival_board[i][j] != -1)
                cout << rival_board[i][j] << "  ";
            else
                cout << ".  ";
        }

        cout << endl;
    }
    cout << endl;
}

void battleship::displayShip(ship s)
{
    cout << "Pos: (" << s.x << ", " << s.y << ")" << endl;
    cout << "Tag:" << s.tag << endl;
    cout << "Dir: " << s.dir << endl;
    cout << "Length: " << s.length << endl;
    cout << "Score: " << s.score << endl << endl;
}

int battleship::getcoord(int x, int y)
{
    return board[x][y];
}

int battleship::getcoordR(int x, int y)
{
    return rival_board[x][y];
}

void battleship::sinkRival(int x, int y)
{
    if (getcoordR(x, y) == -1) rival_board[x][y] = -3;
    if (getcoordR(x, y) < 0) return;

    if (rival_ships[getcoordR(x, y)].score >  0)
        rival_ships[getcoordR(x, y)].score -= 1;
    rival_board[x][y] = -2;
    if (rival_ships[getcoordR(x, y)].score == 0)
        rival_ships[getcoordR(x, y)].tag *= -1;
    //displayBoard();
}
int battleship::sinkPlayer(int x, int y)
{
    if (getcoord(x, y) == -1) board[x][y] = -3;
    if (getcoord(x, y) < 0) return board[x][y];

    if (ships[getcoord(x, y)].score > 0)
        ships[getcoord(x, y)].score -= 1;
    board[x][y] = -2;
    if (ships[getcoord(x, y)].score == 0)
        ships[getcoord(x, y)].tag *= -1;

    return board[x][y];
    //displayBoard();
}


bool battleship::checkBoard()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (board[i][j] > -1)
            {
                return true;
            }
        }
    }
    return false;
}

bool battleship::checkBoardR()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (rival_board[i][j] > -1)
            {
                return true;
            }
        }
    }
    return false;
}

void battleship::clearBoard(int arr[][10])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            arr[i][j] = -1;
            ai.cleanMiss();
        }
    }
}

int battleship::AIMove()
{
    coord next = ai.getNext();
    while (getcoord(next.x, next.y) < -1)
    {
        next = ai.getNext();
    }
    if (sinkPlayer(next.x, next.y) == -2)
    {
        ai.addMiss(next.x, next.y, ships[checkShip(next.x, next.y)].score);
        //ai.displayProbs();
        if (ships[checkShip(next.x, next.y)].score == 0)
            return 2;
        return 1;
    }
    for (int i = 0; i < 5; i++)
    {
        if (ships[i].tag < 0)
        {
            ai.sinkShip(i);
        }
    }
    ai.addMiss(next.x, next.y, false);
    //ai.displayProbs();
    return 0;
}

// AI implementation

AI::AI()
{
    miss.resize(10);
    probabilities.resize(10);
    certainties.resize(10);
    for (int i = 0; i < 10; i++)
    {
        miss[i].resize(10, 0);
        probabilities[i].resize(10);
        certainties[i].resize(10, 0);
    }
    for (int i = 0; i < 5; i++)
    {
        sinks[i] = false;
    }
}

void AI::addMiss(int x, int y, int tag)
{
    if (tag > 0)
    {
        if (x > 0 && x < 9)
        {
            certainties[x + 1][y] = 1;
            certainties[x - 1][y] = 1;
        }
        else if (x == 0 || x == 9)
        {
            if (y == 0) certainties[x][1] = 1;
            if (y == 9) certainties[x][8] = 1;
            if (x == 0) certainties[x + 1][y] = 1;
            if (x == 9) certainties[x - 1][y] = 1;
        }

        if (y > 0 && y < 9)
        {
            certainties[x][y + 1] = 1;
            certainties[x][y - 1] = 1;
        }
        else if (y == 0 || y == 9)
        {
            if (x == 0) certainties[1][y] = 1;
            if (x == 9) certainties[8][y] = 1;
            if (y == 0) certainties[x][y + 1] = 1;
            if (y == 9) certainties[x][y - 1] = 1;
        }

        // delete sides from certainties
        if (x > 0 && x < 9)
        {
            if (miss[x - 1][y] == 2 || miss[x + 1][y] == 2) // Horizontal
            {
                if (y < 9)
                {
                    certainties[x][y + 1] = 0;
                }
                if (y > 0) 
                {
                    certainties[x][y - 1] = 0;
                }
            }
        }
        if (y > 0 && y < 9)
        {
            if (miss[x][y - 1] == 2 || miss[x][y + 1] == 2)
            {
                if (x < 9)
                {
                    certainties[x + 1][y] = 0;

                }
                if (x > 0)
                {
                    certainties[x - 1][y] = 0;
                }
            }
        }


         miss[x][y] = 2;
    }
    else 
    {
        miss[x][y] = 1;
    }
}



void AI::countLength(int x, int y, int l)
{
    if (miss[x][y] > 0)
    {
        probabilities[x][y] = 0;
        return;
    }
    
    for (int j = 1; j <= l; j++)
    {
        if (x - j < 0) continue;
        // Check if a ship is possible in x y with starting point x - j y
        bool sum = true;

        for (int i = 0; i < l; i++)
        {
            if (x - j + i >= 10) 
            {
                sum = false;
                break;
            }
            if (miss[x - j + i][y] == 1)
            {
                sum = false;
                break;
            }
        }
        if (sum)
            probabilities[x][y] += 1;
    }

    for (int j = 0; j < l; j++)
    {
        if (y - j < 0) continue;
        // Check if a ship is possible in x y with starting point x - j y
        bool sum = true;
        for (int i = 0; i < l; i++)
        {
            if (y - j + i >= 10) 
            {
                sum = false;
                break;
            }
            if (miss[x][y - j + i] == 1)
            {
                sum = false;
                break;
            }
        }
        if (sum)
            probabilities[x][y] += 1;
    }
}
void AI::genProbMap()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            probabilities[i][j] = 0;
            calculateProbability(i, j);
        }
    }
}
void AI::calculateProbability(int x, int y)
{
    int ships[5] = { 5, 4, 3, 3, 2 };
    for (int i = 0; i < 5; i++)
    {
        if (!sinks[i])
            countLength(x, y, ships[i]);
    }
}

coord AI::getNext()
{
    coord next = { 0, 0 };
    genProbMap();
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (certainties[i][j] > 0)
            {
                next = { i, j };
                certainties[i][j] = 0;
                return next;
            }
            if (miss[i][j] > 0) { continue; }
            if (probabilities[next.x][next.y] < probabilities[i][j])
            {
                next = { i, j };
            }
        }
    }
    return next;
}

void AI::cleanMiss()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            miss[i][j] = 0;
        }
    }
    for (int i = 0; i < 5; i++)
    {
        sinks[i] = false;
    }
}

void AI::sinkShip(int i)
{
    sinks[i] = true;
}

void AI::displayProbs()
{
    cout << endl;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            std::cout << probabilities[i][j] << " ";
        }
        std::cout << endl;
    }
}