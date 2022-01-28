#pragma once
#include "drawable.h"
#include "board.h"
#include "snake.h"
#include "animation.h"
#include "colliding.h"
#include "appContext.h"

class Target : public Drawable<AppContext>, public Colliding
{
private:
	const int value;
	const Board& board;
	const Snake& snake;
	sf::Texture targetTexture;
	sf::RectangleShape target;
	Animation<sf::RectangleShape> animation;

	void createTarget(int x, int y);
	const sf::FloatRect getCollabseRect() const override;

public:
	Target(AppContext* context, const Board& board, const Snake& snake);

	//generate a new target
	void newTarget();

	void draw() override;

	void process();
};