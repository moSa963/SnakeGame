#pragma once
#include "target.h"
#include <ctime>

Target::Target(AppContext* context, const Board& board, const Snake& snake)
	: Colliding(), Drawable<AppContext>(context),
		value(1), board(board), snake(snake), target(), targetTexture(),
		animation(target, 800, 0, {0.8f, 1.0f, 0.8f}, 500)
{
	srand((unsigned int)time(NULL));

	target.setSize(board.getSquareSize());
	animation.setMoves({ 0.0f, 0.4f, 1.0f });

	//animate the target
	animation.setCallBack([](sf::RectangleShape& target, double v) {
		target.setScale((float)v, (float)v);
	});

	animation.start();

	targetTexture = context->getTexture("apple");
	target.setTexture(&targetTexture);

	createTarget(board.getSize().x / 2, board.getSize().y / 2);
}

void Target::newTarget()
{
	//generate a random index
	int x = std::rand() % board.getSize().x;
	int y = std::rand() % board.getSize().y;
	createTarget(x, y);
}

void Target::createTarget(int x, int y)
{
	target = board.getRect(sf::Vector2u(x, y));
	target.setTexture(&targetTexture);
	target.setFillColor(sf::Color::White);
}

void Target::draw()
{
	context->getWindow().draw(target);
}

void Target::process()
{
	animation.process();
}

const sf::FloatRect Target::getCollabseRect() const
{
	sf::FloatRect rect;
	rect.top = target.getPosition().y - (target.getSize().y / 2.0f);
	rect.left = target.getPosition().x - (target.getSize().x / 2.0f);
	rect.width = target.getSize().x;
	rect.height = target.getSize().y;
	return rect;
}