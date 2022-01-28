#pragma once
#include "board.h"
#include <cmath>

Board::Board(AppContext* context, int x, int y)
	: Colliding(), Drawable(context), root(), size(x, y), squareSize()
{
}

void Board::init(sf::RectangleShape rectRoot)
{
	root = rectRoot;

	squareSize = rectRoot.getSize().x / size.x;
	float offsetX = rectRoot.getGlobalBounds().left;
	float offsetY = rectRoot.getGlobalBounds().top;
	bool x = false;

	for (int j = 0; j < size.y; ++j)
	{
		for (int i = 0; i < size.x; ++i)
		{
			sf::RectangleShape rect;
			rect.setOrigin(sf::Vector2f(squareSize / 2.0f , squareSize / 2.0f));
			rect.setSize(sf::Vector2f(squareSize, squareSize));
			rect.setPosition(sf::Vector2f((i * squareSize) + offsetX + (squareSize / 2.0f) , (j * squareSize) + offsetY + (squareSize / 2.0f) ));
			rect.setFillColor(x ? sf::Color(80, 80, 80) : sf::Color(100, 100, 100));
			
			shapes.push_back(rect);
			x = !x;
		}
	}
}


void Board::draw()
{
	for (sf::RectangleShape& shape : shapes)
	{
		context->getWindow().draw(shape);
	}
}

sf::Vector2f Board::getSquareSize() const
{
	return sf::Vector2f(squareSize, squareSize);
}

const sf::RectangleShape& Board::getRect(sf::Vector2u index) const
{
	int i = (size.x * index.y) + index.x;
	return shapes[i];
}

const sf::Vector2i Board::getIndex(const sf::Vector2f& point) const
{
	int x = (int)std::floor((point.x - root.getGlobalBounds().left) / squareSize);
	int y = (int)std::floor((point.y - root.getGlobalBounds().top) / squareSize);
	return sf::Vector2i(x, y);
}

const sf::Vector2i& Board::getSize() const
{
	return size;
}

const sf::FloatRect Board::getCollabseRect() const
{
	return root.getGlobalBounds();
}

