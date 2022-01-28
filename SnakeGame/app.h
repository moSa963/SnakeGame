#pragma once
#include "SFML/Graphics.hpp"
#include "appBase.h"
#include <memory>

class App : public AppBase
{
protected:
	Screen<AppContext>* getScreen(std::string key, std::map<std::string, std::string> params) override;

public:
	App();

	//returns a map contains a key and a textures path
	std::map<std::string, std::string> initTextures() override;

	//returns a map contains a key and a fonts path
	std::map<std::string, std::string> initFonts() override;

	//returns the screen key to start the application with this screen
	std::string firstScreenKey() override;
};