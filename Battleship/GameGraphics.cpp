#include "GameGraphics.h"


bool collides(sf::Vector2f position, sf::RectangleShape rect)
{
	if (rect.getPosition().x + rect.getSize().x < position.x)
	{
		return false;
	}
	if (rect.getPosition().x > position.x)
	{
		return false;
	}
	if (rect.getPosition().y + rect.getSize().y < position.y)
	{
		return false;
	}
	if (rect.getPosition().y > position.y)
	{
		return false;
	}
	return true;
}

void hover(sf::RectangleShape &rect, sf::Text &text)
{
	sf::Color hoverColor = sf::Color::Green;
	text.setFillColor(hoverColor);
	rect.setOutlineThickness(5);
	rect.setOutlineColor(hoverColor);	
}

void setOriginCenterRect(sf::RectangleShape& shape, sf::Text& text, sf::Color color, float offset)
{
	text.setFillColor(color);
	text.setCharacterSize(shape.getSize().y - offset);
	text.setOrigin(text.getGlobalBounds().width / 2.f + text.getLocalBounds().left, text.getGlobalBounds().height / 2.f + text.getLocalBounds().top);
	text.setPosition(shape.getPosition() + (shape.getSize() / 2.f));
	shape.setOutlineThickness(5);
	shape.setFillColor(sf::Color::Black);
	shape.setOutlineColor(color);
}

void randomWig(sf::RectangleShape& shape, sf::Vector2f position)
{
	shape.setPosition(position + sf::Vector2f(0, rand()%3 - 1.5f));
}

sf::Sound getSound(std::string filename, sf::SoundBuffer* buffer, float volume)
{
	buffer->loadFromFile("Sounds/" + filename);
	sf::Sound s(*buffer);
	s.setVolume(volume);
	return s;
}

void setDelay(float ms)
{
	sf::Clock Timer;
	while (Timer.getElapsedTime().asMilliseconds() < ms);
}

void centerTextAt(sf::Text &text, sf::Vector2f position)
{
	text.setOrigin(text.getGlobalBounds().width / 2.f + text.getLocalBounds().left, text.getGlobalBounds().height / 2.f + text.getLocalBounds().top);
	text.setPosition(position);
}

