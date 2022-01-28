#pragma once
#include "app.h"
#include <cstdlib>
#include "snakeGame.h"
#include "startScreen.h"


App::App()
	: AppBase(1080, 720, "Snake Game")
{
	context.getWindow().setFramerateLimit(120);
}

Screen<AppContext>* App::getScreen(std::string key, std::map<std::string, std::string> params)
{
	if (key == "start")
	{
		return new StartScreen(&context, params);
	}
	else if (key == "snakeGame")
	{
		return new SnakeGame(&context, params);
	}
	return nullptr;
}

std::map<std::string, std::string> App::initTextures()
{
	std::map<std::string, std::string> map;

	map["apple"] = "res/apple.png";
	map["background"] = "res/backitem.png";
	map["snakeHead"] = "res/snake_head.png";
	map["snakeHead2"] = "res/snake_head2.png";
	map["snakeHead3"] = "res/snake_head3.png";
	map["snakeHead4"] = "res/snake_head4.png";
	map["snakeTail"] = "res/snake_tail.png";
	map["snakeBody"] = "res/snake_body.png";
	map["snackCorner"] = "res/snake_corner.png";
	map["button"] = "res/button.png";

	return map;
}


std::map<std::string, std::string> App::initFonts()
{
	std::map<std::string, std::string> map;

	map["timesbd"] = "res/timesbd.ttf";

	return map;
}

std::string App::firstScreenKey()
{
	return "start";
}