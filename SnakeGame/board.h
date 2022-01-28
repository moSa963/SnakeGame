#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include "drawable.h"
#include "colliding.h"
#include "appContext.h"

class Board : public Colliding, public Drawable<AppContext>
{
private:
	sf::RectangleShape root;
	sf::Vector2i size;
	std::vector<sf::RectangleShape> shapes;
	float squareSize;

private:
	const sf::FloatRect getCollabseRect() const override;

public:
	// x, y is the size of the grid mean the amount of squares
	// the calculation of the width of each square depends on the width of the root shape
	Board(AppContext* context, int x, int y);
	
	void init(sf::RectangleShape root);

	void draw() override;

	//get the size of each square on the grid
	sf::Vector2f getSquareSize() const;

	const sf::RectangleShape& getRect(sf::Vector2u index) const;

	const sf::Vector2i getIndex(const sf::Vector2f& point) const;

	const sf::Vector2i& getSize() const;
};