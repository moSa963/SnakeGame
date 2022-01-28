#pragma once 
#include "snake.h"

Snake::Snake(AppContext* context, const Board& board)
:Drawable<AppContext>(context), board(board), destination(Destinations::RIGHT),
	  snakeBody(), snakeHead(), snakeTail(), oldDestination(Destinations::RIGHT), snakeCorner(),
	headAnim(items, 1000, 0, { 0.0f, 1.0f, 2.0f, 3.0f, 2.0f, 1.0f, 0.0f }, 5000),
	anim(items, 200, 1, {0.0f, 100.0f, 0.0f })
{
	snakeTail = context->getTexture("snakeTail");
	snakeBody = context->getTexture("snakeBody");
	snakeHead[0] = context->getTexture("snakeHead");
	snakeHead[1] = context->getTexture("snakeHead2");
	snakeHead[2] = context->getTexture("snakeHead3");
	snakeHead[3] = context->getTexture("snakeHead4");
	snakeCorner = context->getTexture("snackCorner");

	sf::RectangleShape taile(board.getRect(sf::Vector2u(0, board.getSize().y / 2)));
	sf::RectangleShape body(board.getRect(sf::Vector2u(1, board.getSize().y / 2)));
	sf::RectangleShape head(board.getRect(sf::Vector2u(2, board.getSize().y / 2)));

	//head width should be two time more the normal block, for the snake tongue animation
	head.setSize(sf::Vector2f(head.getSize().x * 2, head.getSize().y));

	taile.setTexture(&snakeTail);
	body.setTexture(&snakeBody);
	head.setTexture(&snakeHead[0]);

	taile.setFillColor(sf::Color::White);
	body.setFillColor(sf::Color::White);
	head.setFillColor(sf::Color::White);

	items.push_back(taile);
	items.push_back(body);
	items.push_back(head);


	//snake tongue animation
	headAnim.setCallBack([&t=snakeHead](std::list<sf::RectangleShape>& l, float value) {
		l.back().setTexture(&t[(int)std::floor(value)]);
	});

	//snake color animation
	anim.setCallBack([](std::list<sf::RectangleShape>& l, float value) {
		for (auto& item : l)
		{
			item.setFillColor(sf::Color(255, 255 - value, 255 - value));
		}
	});

	headAnim.start();
}

void Snake::setDestination(Destinations destination)
{
	switch (destination)
	{
	case Destinations::LEFT:
	case Destinations::RIGHT:
	{
		if (this->oldDestination == Destinations::DOWN || this->oldDestination == Destinations::UP)
		{
			this->destination = destination;
		}
		break;
	}
	case Destinations::DOWN:
	case Destinations::UP:
	{
		if (this->oldDestination == Destinations::LEFT || this->oldDestination == Destinations::RIGHT)
		{
			this->destination = destination;
		}
		break;
	}
	default:
		break;
	}
}

void Snake::draw()
{
	for (sf::RectangleShape& item : items)
	{
		context->getWindow().draw(item);
	}
}

bool Snake::process()
{
	anim.process();
	headAnim.process();

	return true;
}


bool Snake::move()
{
	//shift the head one step
	sf::RectangleShape head = items.back();
	head.setPosition(shift(head, destination));

	//if old destination equal to the new one, means there is no corner
	if (oldDestination == destination)
	{
		items.back().setTexture(&snakeBody);
	}
	else
	{
		items.back().setTexture(&snakeCorner, true);
		setRotation(items.back(), destination, true);
	}
	
	//resize because this is the old heade and the width of the heade is twice the width of the normal part
	items.back().setSize(board.getSquareSize());

	//pop the taile and push the new head
	items.pop_front();
	items.push_back(head);

	//set the new tail texture
	items.front().setTexture(&snakeTail);

	//rotate the new head
	setRotation(items.back(), destination);

	oldDestination = destination;
	return true;
}

void Snake::newLevel()
{
	//copy the last item and push it
	sf::RectangleShape shape = items.front();
	items.push_front(shape);
}

void Snake::setRotation(sf::RectangleShape& rect, Destinations destinations, bool revers)
{
	switch (destination)
	{
	case Destinations::RIGHT: rect.setRotation(0.0f);
		break;
	case Destinations::DOWN: rect.setRotation(90.0f);
		break;
	case Destinations::LEFT: rect.setRotation(180.0f);
		break;
	case Destinations::UP: rect.setRotation(270.0f);
		break;
	default:
		break;
	}

	if (!revers) return;

	if ((oldDestination > destination && (int)oldDestination - (int)destination == 1) || (oldDestination == Destinations::RIGHT && destination == Destinations::UP))
	{
		rect.setScale(1, -1);
		return;
	}

	rect.setScale(1, 1);
}

//shift the shape one step (the size of the square board) to the specified direction
sf::Vector2f Snake::shift(const sf::RectangleShape& shape, Destinations destination) const
{
	sf::Vector2f position = shape.getPosition();
	sf::Vector2f size = board.getSquareSize();

	switch (destination)
	{
	case Destinations::LEFT: return sf::Vector2f(position.x - size.x, position.y);
	case Destinations::DOWN: return sf::Vector2f(position.x, position.y + size.y);
	case Destinations::UP: return sf::Vector2f(position.x, position.y - size.y);
	default: return sf::Vector2f(position.x + size.x, position.y);
	}
}

bool Snake::isCollaped(sf::FloatRect other) const
{
	int i = 0;

	//check collision of the other rect with each part of the snake except the head

	for (const sf::RectangleShape& item : items)
	{
		++i;
		sf::FloatRect rect;

		rect.width = board.getSquareSize().x;
		rect.height = board.getSquareSize().y;
		rect.top = item.getPosition().y - (rect.height / 2.0f);
		rect.left = item.getPosition().x - (rect.width / 2.0f);

		if (i != items.size() && rect.intersects(other))
		{
			return true;
		}
	}

	return false;
}

const std::list<sf::RectangleShape> Snake::getList() const
{
	return items;
}

const sf::FloatRect Snake::getCollabseRect() const
{
	sf::RectangleShape head = items.back();
	head.setPosition(shift(head, destination));
	sf::FloatRect rect;
	rect.width = board.getSquareSize().x;
	rect.height = board.getSquareSize().y;
	rect.top = head.getPosition().y - (rect.height / 2.0f);
	rect.left = head.getPosition().x - (rect.width / 2.0f);
	return rect;
}

void Snake::startColorAnimation()
{
	anim.start();
}