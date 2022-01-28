#pragma once
#include "environment.h"

Environment::Environment(AppContext* context)
	: Drawable<AppContext>(context), board(context, 27, 18), backgroundTexture(), background()
{
	sf::Vector2i appSize = context->getSize();

	sf::RectangleShape root;

	root.setPosition(sf::Vector2f((float)appSize.x / -2.0f, (float)appSize.y / -2.0f));
	root.setFillColor(sf::Color::Blue);
	root.setSize(sf::Vector2f((float)appSize.x, (float)appSize.y));

	board.init(root);

	backgroundTexture = context->getTexture("background");

	backgroundTexture.setRepeated(true);

	background.setTextureRect(sf::IntRect(0, 0, appSize.x * 2, appSize.y * 2));
	background.setTexture(backgroundTexture);
	background.setOrigin((float)appSize.x, (float)appSize.y);
	background.setPosition(0, 0);
}



void Environment::draw()
{
	context->getWindow().draw(background);
	board.draw();
}


const Board& Environment::getBoard() const
{
	return board;
}