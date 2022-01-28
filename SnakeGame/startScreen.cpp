#pragma once
#include "startScreen.h"

StartScreen::StartScreen(AppContext* context, std::map<std::string, std::string> params)
	: Screen<AppContext>(context, params), background(), button(context, "Start"),
	backgroundTexture(), font(), title("Snake Game", font, 100), score("", font, 50)
{
	backgroundTexture = context->getTexture("background");
	backgroundTexture.setRepeated(true);

	sf::Vector2u size = context->getWindow().getSize();
	setView(size.x, size.y);

	background.setTextureRect(sf::IntRect(0, 0, 2000, 2000));
	background.setPosition(sf::Vector2f(-1000, -1000));
	background.setTexture(backgroundTexture);

	button.setSize(sf::Vector2f(-100, 150), sf::Vector2f(200, 75));

	//start the game when the button get clicked
	button.setAction([context = context]() {
		context->setScreen("snakeGame");
		});

	font = context->getFont("timesbd");
	title.setPosition(title.getLocalBounds().width / -2.0f, -300);


	score.setString("Last Score: " + params["score"]);
	score.setPosition(score.getLocalBounds().width / -2.0f, -100);
}

void StartScreen::handleEvent(sf::Event& event)
{
	if (event.type == sf::Event::Resized)
	{
		sf::View view;
		setView(event.size.width, event.size.height);
	}
	else if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			button.handleMouseReleased(context->getWindow().mapPixelToCoords(sf::Mouse::getPosition(context->getWindow())));
		}
	}
	else if (event.type == sf::Event::MouseMoved)
	{
		button.handleMouseMoved(context->getWindow().mapPixelToCoords(sf::Mouse::getPosition(context->getWindow())));
	}
}

void StartScreen::process()
{
}

void StartScreen::draw()
{
	context->getWindow().draw(background);
	button.draw();
	context->getWindow().draw(title);
	context->getWindow().draw(score);
}


void StartScreen::setView(unsigned int width, unsigned int height)
{
	sf::View newView(sf::Vector2f(0.0, 0.0), sf::Vector2f((float)width, (float)height));
	newView.zoom((float)(1080 * 2) / (width + height));
	context->setView(newView);
}