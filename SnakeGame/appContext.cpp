#pragma once
#include "appContext.h"

AppContext::AppContext(unsigned int width, unsigned int height, std::string&& name)
	: window(sf::VideoMode(1080, 720), name), size(sf::Vector2i(width, height)), currentScreen(nullptr), screenAction()
{
	window.setView(mainView);
}

sf::RenderWindow& AppContext::getWindow()
{ 
	return window; 
}

sf::View& AppContext::getView() 
{ 
	return mainView;
}

const sf::Vector2i& AppContext::getSize() const
{ 
	return size;
}

void AppContext::setView(sf::View view)
{
	mainView = view;
	window.setView(mainView);
}

bool AppContext::addTexture(std::string key, std::string fileName)
{
	sf::Texture texture;

	if (!texture.loadFromFile(fileName)) return false;

	textures[key] = texture;
	return true;
}

sf::Texture& AppContext::getTexture(std::string key)
{
	return textures[key];
}

bool AppContext::addFont(std::string key, std::string fileName)
{
	sf::Font font;

	if (!font.loadFromFile(fileName)) return false;

	fonts[key] = font;
	return true;
}

sf::Font AppContext::getFont(std::string key)
{
	return fonts[key];
}

void AppContext::setScreen(std::string name, std::map<std::string, std::string> params)
{
	currentScreen.reset(screenAction(name, params));
	currentScreen->init();
}

std::shared_ptr<Screen<AppContext>> AppContext::getScreen()
{
	return currentScreen;
}

void AppContext::setScreenAction(std::function<Screen<AppContext>* (std::string, std::map<std::string, std::string>)> function)
{
	screenAction = function;
}

AppContext::~AppContext()
{
}