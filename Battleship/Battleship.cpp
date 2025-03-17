// Battleship.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include "GameClass.h"
#include "GameGraphics.h"  
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
float w = modes[0].width , h = modes[0].height;
//float w = 1920.f, h = 1080.f;
// Color Palette
sf::Color shipColor(156, 153, 153);
sf::Color shipOutlineColor(113, 112, 110);
sf::Color selectedShipColor = sf::Color::Yellow;
sf::Color waterColor(36, 76, 219);
sf::Color waterCircleColor(33, 57, 143);
sf::Color waterSinkColor(190, 190, 190, 100);
sf::Color shipSinkColor(153, 3, 3, 230);


int gameLoop(battleship b)
{
    //Init game
    float ratio = w / 1920.f;
    float gridSizeF = 75.f * ratio;
    unsigned gridSizeU = 75 * ratio;
    float dt = 0.f;
    sf::Clock dtClock;
    sf::Vector2i mousePosScreen = sf::Mouse::getPosition();
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosScreenF;
    sf::Vector2f mousePosView;
    sf::Vector2u mousePosGrid;
    sf::Text text;
    sf::Font font;
    if (!font.loadFromFile("Fonts/SourceSansPro-Regular.ttf"))
    {
        return 1;
    }
    ship s;
    text.setCharacterSize(28);
    text.setFillColor(sf::Color::White);
    text.setFont(font);
    text.setPosition(20.f, 20.f);
    text.setString("TEST");

    //Init windows
    sf::RenderWindow window(sf::VideoMode(w, h), "Battleship");
    //sf::Window window;
    sf::View view;
    view.setSize(w, h);
    view.setCenter((window.getSize().x - gridSizeF / 2)/2.f, (window.getSize().y - gridSizeF)/2.f);
    float viewSpeed = 200.f;

    //Init game elements
    //sf::RectangleShape shape(sf::Vector2f(gridSizeF, gridSizeF));
    // Initialize sounds
    sf::Sound sound;
    sf::SoundBuffer* buffer = new sf::SoundBuffer;
    
    const int mapSize = 10;
    //Init Player Board
    std::vector<std::vector<sf::RectangleShape>> tilemap;
    std::vector<std::vector<sf::CircleShape>> tilemapC;
    std::vector<std::vector<sf::Text>> textTileMap;
    tilemap.resize(mapSize, std::vector<sf::RectangleShape>());
    tilemapC.resize(mapSize, std::vector<sf::CircleShape>());
    textTileMap.resize(mapSize, std::vector<sf::Text>());

    std::vector<sf::RectangleShape> shipOutline;
    shipOutline.resize(5);
    for (int i = 0; i < 5; i++)
    {
        shipOutline[i].setOutlineColor(shipOutlineColor);
        shipOutline[i].setFillColor(sf::Color::Transparent);
        shipOutline[i].setOutlineThickness(-4);
    }

    std::vector<sf::RectangleShape> shipOutlineR;
    shipOutlineR.resize(5);
    for (int i = 0; i < 5; i++)
    {
        shipOutlineR[i].setOutlineColor(sf::Color::Transparent);
        shipOutlineR[i].setFillColor(sf::Color::Transparent);
        shipOutlineR[i].setOutlineThickness(-4);

    }

    // Init Rival Board
    std::vector<std::vector<sf::RectangleShape>> tilemapRival;
    std::vector<std::vector<sf::CircleShape>> tilemapCRival;
    std::vector<std::vector<sf::Text>> textTileRival;
    tilemapRival.resize(mapSize, std::vector<sf::RectangleShape>());
    tilemapCRival.resize(mapSize, std::vector<sf::CircleShape>());
    textTileRival.resize(mapSize, std::vector<sf::Text>());

    int selectedShip = -1;
    // Set player board
    for (int i = 0; i < mapSize; i++)
    {
        tilemap[i].resize(mapSize, sf::RectangleShape());
        tilemapC[i].resize(mapSize, sf::CircleShape());
        textTileMap[i].resize(mapSize, sf::Text());
        for (int j = 0; j < mapSize; j++)
        {
            tilemap[i][j].setSize(sf::Vector2f(gridSizeF, gridSizeF));
            tilemap[i][j].setOutlineThickness(1.f);
            tilemap[i][j].setOutlineColor(sf::Color::Black);
            tilemap[i][j].setPosition(i * gridSizeF, j * gridSizeF);

            tilemapC[i][j].setRadius(5 * gridSizeF / 16);
            tilemapC[i][j].setPosition(i * gridSizeF + 3*gridSizeF/16, j * gridSizeF + 3* gridSizeF / 16);
            //tilemapC[i][j].setFillColor(waterCircleColor);

            textTileMap[i][j].setFont(font);
            textTileMap[i][j].setCharacterSize(24);
            textTileMap[i][j].setFillColor(sf::Color::Red);
            textTileMap[i][j].setFont(font);
            textTileMap[i][j].setPosition(i * gridSizeF + 2, j * gridSizeF + 2);
        }
    }

    // Set RivalBoard
    float offset = gridSizeF * (mapSize + 5);
    for (int i = 0; i < mapSize; i++)
    {
        tilemapRival[i].resize(mapSize, sf::RectangleShape());
        textTileRival[i].resize(mapSize, sf::Text());
        tilemapCRival[i].resize(mapSize, sf::CircleShape());
        textTileMap[i].resize(mapSize, sf::Text());
        for (int j = 0; j < mapSize; j++)
        {
            tilemapRival[i][j].setSize(sf::Vector2f(gridSizeF, gridSizeF));
            tilemapRival[i][j].setOutlineThickness(1.f);
            tilemapRival[i][j].setOutlineColor(sf::Color::Black);
            tilemapRival[i][j].setPosition((i + mapSize + 5) * gridSizeF, j * gridSizeF);

            tilemapCRival[i][j].setRadius(5 * gridSizeF / 16);
            tilemapCRival[i][j].setPosition((i + mapSize + 5)*gridSizeF + 3 * gridSizeF / 16, j * gridSizeF + 3 * gridSizeF / 16);
            //tilemapCRival[i][j].setFillColor(waterCircleColor);

            textTileRival[i][j].setFont(font);
            textTileRival[i][j].setCharacterSize(24);
            textTileRival[i][j].setFillColor(sf::Color::Red);
            textTileRival[i][j].setFont(font);
            textTileRival[i][j].setPosition(i * gridSizeF + 2, j * gridSizeF + 2);
        }
    }

    // Tile selector
    sf::RectangleShape tileSelector(sf::Vector2f(gridSizeF, gridSizeF));
    tileSelector.setFillColor(sf::Color::Transparent);
    tileSelector.setOutlineThickness(1.f);
    tileSelector.setOutlineColor(sf::Color::Green);

    // Init Background images
    sf::Texture backGroundImage;
    if (!backGroundImage.loadFromFile("Images/background2.png"))
        return 1;
    sf::Sprite bg(backGroundImage);
    // Init Buttons
    sf::RectangleShape startB(sf::Vector2f(gridSizeF * 3, gridSizeF));
    sf::Text startBtext;
    startB.setPosition(gridSizeF * 11, gridSizeF);
    startBtext.setFont(font);
    setOriginCenterRect(startB, startBtext);

    sf::RectangleShape randomB(sf::Vector2f(gridSizeF * 3, gridSizeF));
    sf::Text randomBtext;
    randomB.setPosition(gridSizeF * 11, 3 * gridSizeF);
    setOriginCenterRect(randomB, randomBtext);
    randomBtext.setFont(font);

    sf::Text gameOvertext;
    gameOvertext.setFont(font);
    gameOvertext.setOutlineColor(sf::Color::Black);
    gameOvertext.setOutlineThickness(10 * ratio);
    gameOvertext.setCharacterSize(200 * ratio);

    sf::RectangleShape gameOverRect(sf::Vector2f(w, h));
    gameOverRect.setFillColor(sf::Color(100, 100, 100, 0));

    sf::Text turnText;
    turnText.setFont(font);
    turnText.setCharacterSize(50 * ratio);

    //sf::RectangleShape muteRect(sf::Vector2f(40 * ratio, 40 * ratio));
    //muteRect.setFillColor(sf::Color::Transparent);
    //muteRect.setOutlineThickness(5 * ratio);
    //muteRect.setOutlineColor(sf::Color::White);
    //muteRect.setPosition(w - 50 * ratio - gridSizeF / 2, h - 145 * ratio - gridSizeF / 2);

    //sf::Text muteText;
    //muteText.setFont(font);
    //muteText.setCharacterSize(30 * ratio);


    bool locked = false;
    bool aiMove = false;
    bool mute = false;
    float aiTimer = 0.2f, aiTime = 0.2f;
    bool gameOver = false;
    int moves = 0;

    while (window.isOpen())
    {
        // Update dt
        dt = dtClock.restart().asSeconds();

        //Update mouse positions
        mousePosScreen = sf::Mouse::getPosition();
        mousePosWindow = sf::Mouse::getPosition(window);
        mousePosScreenF = sf::Vector2f(mousePosScreen.x, mousePosScreenF.y);
        window.setView(view);
        mousePosView = window.mapPixelToCoords(mousePosWindow);
        if (mousePosView.x > -gridSizeF)
            mousePosGrid.x = mousePosView.x / gridSizeU;
        if (mousePosView.y > -gridSizeF)
            mousePosGrid.y = mousePosView.y / gridSizeU;
        window.setView(window.getDefaultView());
        
        // Update game elements
        tileSelector.setPosition(mousePosGrid.x * gridSizeF, mousePosGrid.y * gridSizeF);

        //Update UI
        std::stringstream ss;
        ss << "Screen: " << mousePosScreen.x << " " << mousePosScreen.y << "\n"
            << "Window: " << mousePosWindow.x << " " << mousePosWindow.y << "\n"
            << "View: " << mousePosView.x << " " << mousePosView.y << "\n"
            << "Grid: " << mousePosGrid.x << " " << mousePosGrid.y << "\n";
        text.setString(ss.str());

        ss.str("");
        
        if (!locked)
        {
            ss << "Start";
            setOriginCenterRect(startB, startBtext);
        }
        else
        {
            ss << "Restart";
            setOriginCenterRect(startB, startBtext, sf::Color(255, 255, 255, 100));
        }
        startBtext.setString(ss.str());


        ss.str("");
        ss << "Random";
        randomBtext.setString(ss.str());
        if (!locked)
            setOriginCenterRect(randomB, randomBtext);
        else
            setOriginCenterRect(randomB, randomBtext, sf::Color(255, 255, 255, 100));


        ss.str("");
        if (gameOver && locked)
        {
            if (!b.checkBoard())
            {
                ss << "You lost :(" << std::endl;
                gameOverRect.setFillColor(sf::Color(200, 200, 200, 100));
            }
            else if (!b.checkBoardR())
            {
                ss << "You won!!";
                gameOverRect.setFillColor(sf::Color(200, 200, 200, 100));
            }
            //startB.setFillColor(sf::Color::Yellow);
        }
        gameOvertext.setString(ss.str());
        centerTextAt(gameOvertext, sf::Vector2f(gridSizeF * 12.5f, 7 * gridSizeF));

        ss.str("");
        if (aiMove && locked)
        {
            ss << "AI's turn.";
        }
        else if (locked)
        {
            ss << "Your turn.";
        }
        turnText.setString(ss.str());
        centerTextAt(turnText, sf::Vector2f(gridSizeF * 12.5f, 6 * gridSizeF));

        //ss.str("");
        //if (collides(mousePosView, muteRect))
        //{
        //    ss << "Press (M) to mute" << std::endl << "Press (esc) to exit";
        //    muteRect.setOutlineColor(sf::Color::Transparent);
        //    muteText.setString(ss.str());
        //    muteText.setPosition(w - 2 * muteText.getLocalBounds().width, h - 2*muteText.getLocalBounds().height);
        //}
        //else
        //{
        //    ss << "?";
        //    muteRect.setOutlineColor(sf::Color::White);
        //    muteText.setString(ss.str());
        //    muteText.setPosition(muteRect.getPosition());
        //    //centerTextAt(muteText, sf::Vector2f(w - 35 * ratio - gridSizeF / 2, h - 125 * ratio - gridSizeF / 2));
        //}


        //Events
        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();

            // Handle Clicks
            if (e.type == sf::Event::MouseButtonPressed)
            {
                if (mousePosView.x > 0 && mousePosView.y > 0)
                {
                    // In first grid
                    //Rotate
                    if (e.mouseButton.button == sf::Mouse::Right && !locked)
                    {
                        if (mousePosGrid.x >= 0 && mousePosGrid.y >= 0 && mousePosGrid.x < mapSize && mousePosGrid.y < mapSize)
                        {
                            if (b.getcoord(mousePosGrid.y, mousePosGrid.x) >= 0)
                            {
                                b.changeDirB(b.ships[b.getShip(mousePosGrid.y, mousePosGrid.x)]);
                            }
                        }
                    }
                    //Select
                    if (e.mouseButton.button == sf::Mouse::Left && !locked)
                    {
                        if (mousePosGrid.x >= 0 && mousePosGrid.y >= 0 && mousePosGrid.x < mapSize && mousePosGrid.y < mapSize)
                        {
                            if ((b.getcoord(mousePosGrid.y, mousePosGrid.x) == -1 || b.getcoord(mousePosGrid.y, mousePosGrid.x) == selectedShip) && selectedShip != -1)
                            {
                                b.changePos(b.ships[selectedShip], mousePosGrid.y, mousePosGrid.x);
                                selectedShip = -1;
                            }
                            else
                            {
                                selectedShip = b.getShip(mousePosGrid.y, mousePosGrid.x);
                            }
                        }
                    }


                    //Buttons
                    for (int i = 0; i < mapSize; i++)
                    {
                        for (int j = 0; j < mapSize; j++)
                        {
                            if (collides(mousePosView, tilemapRival[i][j]) && !(b.getcoordR(j,i) < -1) && !aiMove && !gameOver)
                            {
                                locked = true;
                                selectedShip = -1;
                                b.sinkRival(j, i);
                                if (b.getcoordR(j, i) == -3)
                                {
                                    sound = getSound("sinkWater.wav", buffer);
                                    aiMove = true;
                                }
                                if (b.getcoordR(j, i) == -2)
                                {
                                    if (b.rival_ships[b.checkShipR(j, i)].score == 0)
                                        sound = getSound("shipIsSink2.wav", buffer);
                                    else
                                        sound = getSound("sinkExplosion.wav", buffer);
                                    aiMove = false;
                                }

                                if (!b.checkBoard() || !b.checkBoardR())
                                {
                                    gameOver = true;
                                }
                                else
                                {
                                    gameOver = false;
                                }

                                if (!mute) sound.play();
                                
                            }
                        }
                    }
                    if (e.mouseButton.button == sf::Mouse::Left)
                    {
                        if (collides(mousePosView, startB))
                        {
                            gameOverRect.setFillColor(sf::Color(200, 200, 200, 0));
                            b.initShipsR();
                            b.initShips(false);
                            selectedShip = -1;
                            locked = !locked;
                            gameOver = false;
                            moves = 0;
                            aiMove = false;
                        }
                        if (collides(mousePosView, randomB) && !locked)
                        {
                            b.initBoards();
                            b.initShips();
                            b.initShipsR();
                            //b.displayBoard();
                        }
                    }

                    
                }
            }
            if (e.type == sf::Event::KeyReleased)
            {
                if (e.key.code == sf::Keyboard::M)
                {
                    mute = !mute;
                    aiTime = mute ? 0.5f : 0.1f;
                }
                if (e.key.code ==  sf::Keyboard::Escape)
                {
                    window.close();
                }
            }
        }

        if (aiMove && locked && !gameOver)
        {
            if (sound.getStatus() != sf::Music::Status::Playing)
            aiTimer -= dt;
            if (aiTimer <= 0)
            {
                int c = b.AIMove();
                if (c == 1)
                {
                    sound = getSound("sinkExplosion.wav", buffer);
                    aiMove = true;
                }
                else if (c == 2)
                {
                    sound = getSound("shipIsSink2.wav", buffer);
                    aiMove = true;
                }
                else
                {
                    sound = getSound("sinkWater.wav", buffer);
                    aiMove = false;
                }
                if (!mute) sound.play();
                aiTimer = aiTime;
                moves++;

                if (!b.checkBoard() || !b.checkBoardR())
                {
                    gameOver = true;
                }
            }
        }

        // Check Hover
        if (collides(mousePosView, startB))
        {
            hover(startB, startBtext);
        }
        if (collides(mousePosView, randomB) && !locked)
        {
            hover(randomB, randomBtext);
        }


       
        //Update
        // Update board
        for (int i = 0; i < mapSize; i++)
        {
            for (int j = 0; j < mapSize; j++)
            {
                std::stringstream tss;
                sf::Color textColor;
                if (b.getcoord(j, i) == -1)
                {
                    tilemap[i][j].setFillColor(waterColor);
                    tilemapC[i][j].setFillColor(waterCircleColor);
                    
                }
                else if(selectedShip != -1 && b.getcoord(j, i) == b.ships[selectedShip].tag)
                {
                    tss << "";
                    tilemap[i][j].setFillColor(sf::Color(212, 175, 55));
                    tilemapC[i][j].setFillColor(sf::Color::Transparent);
                }
                else if (b.getcoord(j, i) == -2)
                {
                    tilemap[i][j].setFillColor(shipColor);
                    tilemapC[i][j].setFillColor(shipSinkColor);
                }
                else if (b.getcoord(j, i) == -3)
                {
                    tilemap[i][j].setFillColor(waterColor);
                    tilemapC[i][j].setFillColor(waterSinkColor);
                }
                else
                {
                    tilemap[i][j].setFillColor(shipColor);
                    tilemapC[i][j].setFillColor(sf::Color::Transparent);
                }
                textTileMap[i][j].setString(tss.str());
            }
        }
        for (int i = 0; i < mapSize; i++)
        {
            for (int j = 0; j < mapSize; j++)
            {
                std::stringstream tss;
                sf::Color textColor;
                if (b.getcoordR(j, i) == -1)
                {
                    tilemapRival[i][j].setFillColor(waterColor);
                    tilemapCRival[i][j].setFillColor(waterCircleColor);
                }
                else if (b.getcoordR(j, i) == -2)
                {
                    //tilemapRival[i][j].setFillColor();
                    if (b.rival_ships[b.checkShipR(j , i)].score == 0)
                    {
                        tilemapRival[i][j].setFillColor(shipColor);
                        shipOutlineR[b.checkShipR(j, i)].setOutlineColor(shipOutlineColor);
                    }
                    tilemapCRival[i][j].setFillColor(shipSinkColor);
                }
                else if(b.getcoordR(j, i) == -3)
                {
                    tilemapRival[i][j].setFillColor(waterColor);
                    tilemapCRival[i][j].setFillColor(waterSinkColor);
                }
                else
                {
                    shipOutlineR[b.checkShipR(j, i)].setOutlineColor(sf::Color::Transparent);
                    tilemapRival[i][j].setFillColor(waterColor);
                    tilemapCRival[i][j].setFillColor(waterCircleColor);
                }
            }
        }
        for (int i = 0; i < 5; i++)
        {
            shipOutline[i].setPosition(b.ships[i].y * gridSizeF, b.ships[i].x * gridSizeF);
            if (b.ships[i].dir == 1)
            {
                shipOutline[i].setSize(sf::Vector2f(gridSizeF * b.ships[i].length, gridSizeF));
            }
            else
            {
                shipOutline[i].setSize(sf::Vector2f(gridSizeF, gridSizeF * b.ships[i].length));
            }
            shipOutline[i].setOutlineThickness(-4.f);
            if (!locked)
            {
                randomWig(shipOutline[i], sf::Vector2f(b.ships[i].y* gridSizeF, b.ships[i].x* gridSizeF));
                shipOutline[i].setOutlineThickness(-6.f);
            }
        }

        for (int i = 0; i < 5; i++)
        {
            shipOutlineR[i].setPosition((b.rival_ships[i].y + 15)* gridSizeF, b.rival_ships[i].x * gridSizeF);
            if (b.rival_ships[i].dir == 1)
            {
                shipOutlineR[i].setSize(sf::Vector2f(gridSizeF * b.rival_ships[i].length, gridSizeF));
            }
            else
            {
                shipOutlineR[i].setSize(sf::Vector2f(gridSizeF, gridSizeF * b.rival_ships[i].length));
            }
        }
        // Update Rival board
        if (mousePosGrid.x >= 0 && mousePosGrid.y >= 0 && mousePosGrid.x < mapSize && mousePosGrid.y < mapSize)
        {
            tileSelector.setPosition(mousePosGrid.x * gridSizeF, mousePosGrid.y * gridSizeF);
            tileSelector.setOutlineColor(sf::Color::Green);
        }
        else if (mousePosGrid.x >= mapSize + 5 && mousePosGrid.y >= 0 && mousePosGrid.x < 2 * mapSize + 5 && mousePosGrid.y < mapSize)
        {
            tileSelector.setPosition(mousePosGrid.x * gridSizeF, mousePosGrid.y * gridSizeF);
            tileSelector.setOutlineColor(sf::Color::Green);
        }
        else
        {
            tileSelector.setOutlineColor(sf::Color::Transparent);
        }

        // Update Input
        /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //Left
        {
            view.move(viewSpeed * dt, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) //Up
        {
            view.move(0.f, viewSpeed * dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //Down
        {
            view.move(0.f, -viewSpeed * dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //Right
        {
            view.move(-viewSpeed * dt, 0.f);
        }*/

        // Render
        window.clear();
        window.setView(window.getDefaultView());
        //window.draw(bg);
        window.setView(view);

        // Render game elements
        for (int x = 0; x < mapSize; x++)
        {
            for (int y = 0; y < mapSize; y++)
            {
                window.draw(tilemap[x][y]);
                window.draw(tilemapC[x][y]);
                window.draw(textTileMap[x][y]);
                window.draw(tilemapRival[x][y]);
                window.draw(tilemapCRival[x][y]);
                window.draw(textTileRival[x][y]);
            }
        }
        for (int i = 0; i < 5; i++)
        {
            window.draw(shipOutline[i]);
            window.draw(shipOutlineR[i]);
        }
        window.draw(tileSelector);

        window.draw(randomB);
        window.draw(randomBtext);
        window.setView(window.getDefaultView());
        window.draw(gameOverRect);
        window.setView(view);

        window.draw(startB);
        window.draw(startBtext);
        window.draw(turnText);

        //window.draw(muteText);
        //window.draw(muteRect);

        window.setView(window.getDefaultView());
        window.draw(gameOvertext);

        // Render ui

        //window.draw(text);
        window.display();
    }
    delete buffer;
    return 0;
}


int main(void)
{
    srand(time(NULL));
    battleship b;
    b.displayBoard();
    gameLoop(b);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file