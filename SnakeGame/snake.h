#pragma once
#include <list>
#include "SFML/Graphics.hpp"
#include "drawable.h"
#include "board.h"
#include "colliding.h"
#include "appContext.h"
#include "animation.h"

class Snake : public Drawable<AppContext>, public Colliding
{
public:
	enum class Destinations
	{
		RIGHT, DOWN, LEFT, UP
	};

private:
	std::list<sf::RectangleShape> items;
	const Board& board;
	Destinations destination;
	Destinations oldDestination;
	sf::Texture snakeHead[4];
	sf::Texture snakeBody;
	sf::Texture snakeTail;
	sf::Texture snakeCorner;
	Animation<std::list<sf::RectangleShape>> headAnim;
	Animation<std::list<sf::RectangleShape>> anim;

private:
	sf::Vector2f shift(const sf::RectangleShape& shape, Destinations destination) const;
	void setRotation(sf::RectangleShape& rect, Destinations destinations, bool revers = false);
	const sf::FloatRect getCollabseRect() const override;
	bool isCollaped(sf::FloatRect other) const override;

public:
	Snake(AppContext* context, const Board& board);

	void startColorAnimation();

	void draw() override;

	void setDestination(Destinations destination);

	//move the snake, movement depends on the value set by "setDestination" method
	bool move();

	bool process();

	//add one item to the snake so it get taller
	void newLevel();

	const std::list<sf::RectangleShape> getList() const;
};