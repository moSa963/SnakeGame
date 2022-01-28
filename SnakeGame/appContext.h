#pragma once
#include "SFML/Graphics.hpp"
#include <map>
#include "screen.h"
#include <functional>

class AppContext
{
private:
	sf::RenderWindow window;
	sf::View mainView;
	const sf::Vector2i size;
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, sf::Font> fonts;
	std::shared_ptr<Screen<AppContext>> currentScreen;
	std::function<Screen<AppContext>* (std::string, std::map<std::string, std::string>)> screenAction;

public:
	AppContext(unsigned int width, unsigned int height, std::string&& name);

	sf::RenderWindow& getWindow();

	sf::View& getView();

	const sf::Vector2i& getSize() const;

	void setView(sf::View view);

	//add new Texture
	bool addTexture(std::string key, std::string fileName);

	sf::Texture& getTexture(std::string key);

	//add new font
	bool addFont(std::string key, std::string fileName);

	sf::Font getFont(std::string key);

	//start a new screen
	//"params" used to pass key values to the new screen
	void setScreen(std::string name, std::map<std::string, std::string> params = std::map<std::string, std::string>());

	//get current screen
	std::shared_ptr<Screen<AppContext>> getScreen();
	
	//an action called to get a screen by its key
	//get called when "setScreen" method is called
	void setScreenAction(std::function<Screen<AppContext>* (std::string, std::map<std::string, std::string>)> function);

	~AppContext();
};