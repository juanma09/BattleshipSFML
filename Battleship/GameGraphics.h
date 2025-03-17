#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

bool collides(sf::Vector2f position, sf::RectangleShape rect);
void hover(sf::RectangleShape &rect, sf::Text &text);
void setOriginCenterRect(sf::RectangleShape& shape, sf::Text& text, sf::Color color = sf::Color::White, float offset = 30.f);
void randomWig(sf::RectangleShape& shape, sf::Vector2f position);
sf::Sound getSound(std::string filename, sf::SoundBuffer *buffer, float volume = 20);
void setDelay(float ms);
void centerTextAt(sf::Text &text, sf::Vector2f position);
void shakeView(sf::View& view, int times);