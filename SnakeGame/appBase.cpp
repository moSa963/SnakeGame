#pragma once
#include "appBase.h"


AppBase::AppBase(unsigned int width, unsigned int height, std::string&& name)
	:context(width, height, std::move(name))
{
	context.setScreenAction([this](std::string key, std::map<std::string, std::string> params) {
		return getScreen(key, params);
	});
}

//add resources to the app context
int AppBase::init()
{
	auto textures = initTextures();
	for (auto texture : textures)
	{
		if (!context.addTexture(texture.first, texture.second)) return EXIT_FAILURE;
	}

	auto fonts = initFonts();
	for (auto font : fonts)
	{
		if (!context.addFont(font.first, font.second)) return EXIT_FAILURE;
	}

	context.setScreen(firstScreenKey());

	return EXIT_SUCCESS;
}


int AppBase::start()
{
	if (init() == EXIT_FAILURE) return EXIT_FAILURE;

	while (context.getWindow().isOpen())
	{
		sf::Event event;

		while (context.getWindow().pollEvent(event))
		{
			//pass event to the current screen
			context.getScreen()->handleEvent(event);

			if (event.type == sf::Event::Closed) context.getWindow().close();
		}

		context.getScreen()->process();

		context.getWindow().clear();

		context.getScreen()->draw();

		context.getWindow().display();
	}

	return EXIT_SUCCESS;
}