#pragma once
#include "SFML/Graphics.hpp"
#include "drawable.h"
#include <iostream>
#include <functional>
#include "appContext.h"

class Button : public Drawable<AppContext>
{
private:
	std::string label;
	sf::RectangleShape root;
	sf::Text text;
	sf::Font font;
	bool isMouseEntered;
	std::function<void(void)> action;
	sf::Texture rootTexture;
	sf::Cursor hand;
	sf::Cursor arrow;

public:
	Button(AppContext* context, std::string lable)
		:Drawable(context), label("Start"), font(), text(label, font), isMouseEntered(false), rootTexture()
	{
		font = context->getFont("timesbd");

		text.setFont(font);

		text.setFillColor(sf::Color::Black);

		rootTexture = context->getTexture("button");
		root.setTexture(&rootTexture);

		arrow.loadFromSystem(arrow.Arrow);
		hand.loadFromSystem(hand.Hand);
	}

	void setAction(std::function<void(void)> action)
	{
		this->action = action;
	}

	void setSize(const sf::Vector2f position, const sf::Vector2f size)
	{
		root.setPosition(position);
		root.setSize(size);
		//set text in the center of the button
		text.setPosition(sf::Vector2f(root.getPosition().x + (root.getSize().x - text.getLocalBounds().width) / 2.0f,
			root.getPosition().y + (root.getSize().y - text.getLocalBounds().height) / 2.0f));
	}

	//handle button clicked
	void handleMouseReleased(sf::Vector2f pos)
	{
		if (root.getGlobalBounds().contains(pos))
		{
			context->getWindow().setMouseCursor(arrow);
			if (action) action();
		}
	}

	//handle hover
	void handleMouseMoved(sf::Vector2f pos)
	{
		if (root.getGlobalBounds().contains(pos))
		{
			if (!isMouseEntered) {
				isMouseEntered = true;
				mouseEntered();
			}
		}
		else
		{
			if (isMouseEntered) {
				isMouseEntered = false;
				mouseLeft();
			}
		}
	}

	void mouseEntered()
	{
		context->getWindow().setMouseCursor(hand);
		root.setFillColor(sf::Color(200, 200, 200));
	}

	void mouseLeft()
	{
		context->getWindow().setMouseCursor(arrow);
		root.setFillColor(sf::Color(255, 255, 255));
	}

	void draw() override
	{
		context->getWindow().draw(root);
		context->getWindow().draw(text);
	}
};