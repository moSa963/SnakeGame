#pragma once
#include "screen.h"
#include "environment.h"
#include "snake.h"
#include "target.h"

class SnakeGame : public Screen<AppContext>
{
private:
	Environment env;
	Snake snake;
	Target target;
	bool gameover = false;
	Animation<sf::View> gameoverAnim;
	sf::Clock clock;
	int snakeSpeed;

public:
	SnakeGame(AppContext* context, std::map<std::string, std::string> params);

	void init() override;

	void handleEvent(sf::Event& event) override;

	void process() override;

	void draw() override;

	void setView(unsigned int width, unsigned int height);

	void gameOver();

	bool checkCollision();

	~SnakeGame() {}
};