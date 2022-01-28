#pragma once
#include "snakeGame.h"

SnakeGame::SnakeGame(AppContext* context, std::map<std::string, std::string> params)
	: Screen(context, params), snake(context, env.getBoard()), target(context, env.getBoard(), snake), clock(), snakeSpeed(110),
	gameoverAnim(context->getView(), 300, 2, { 0.0f, 0.5f, 0.6f, -0.6f, -0.5f, 0.0f }), env(context)
{
	sf::Vector2u size = context->getWindow().getSize();
	setView(size.x, size.y);

	//when game is over this aniamtion will shake the view
	gameoverAnim.setCallBack([&window = context->getWindow()](sf::View& view, float v) {
		view.move(v, v / 2);
		window.setView(view);
	});

	//when gameover animation ends, set the "start" screen and pass the score to it
	gameoverAnim.setAnimationEndCallback([context=context, &snake=snake]() {
		std::map<std::string, std::string> params;
		params["score"] = std::to_string(snake.getList().size() - 3);
		context->setScreen("start", params);
	});

}

void SnakeGame::init(){}

void SnakeGame::handleEvent(sf::Event& event)
{
	if (event.type == sf::Event::Resized) {
		//reset the view with the new window size
		setView(event.size.width, event.size.height);
	}
	else if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::D:
		case sf::Keyboard::Right: snake.setDestination(Snake::Destinations::RIGHT);
			break;
		case sf::Keyboard::A:
		case sf::Keyboard::Left: snake.setDestination(Snake::Destinations::LEFT);
			break;
		case sf::Keyboard::W:
		case sf::Keyboard::Up: snake.setDestination(Snake::Destinations::UP);
			break;
		case sf::Keyboard::S:
		case sf::Keyboard::Down: snake.setDestination(Snake::Destinations::DOWN);
			break;
		default:
			break;
		}
	}
}

void SnakeGame::process()
{
	gameoverAnim.process();

	if (gameover) return;

	snake.process();

	if (clock.getElapsedTime().asMilliseconds() >= snakeSpeed)
	{
		//move the snake if "step callback" returns true
		if (checkCollision())
		{
			snake.move();
		}
		clock.restart();
	}

	target.process();
}

bool SnakeGame::checkCollision()
{
	if (snake.collapse(snake) || !env.getBoard().collapse(snake))
	{
		gameOver();
		return false;
	}

	if (target.collapse(snake))
	{
		snake.startColorAnimation();
		target.newTarget();
		snake.newLevel();
	}

	return true;
}

void SnakeGame::draw()
{
	env.draw();
	snake.draw();
	target.draw();
}

void SnakeGame::setView(unsigned int width, unsigned int height)
{
	sf::View newView(sf::Vector2f(0.0, 0.0), sf::Vector2f((float)width, (float)height));
	newView.zoom((float)(context->getSize().x * 2.0f) / (width + height));
	context->setView(newView);
}

void SnakeGame::gameOver()
{
	gameover = true;
	gameoverAnim.start();
}