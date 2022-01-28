#pragma once
#include "screen.h"
#include "Button.h"

class StartScreen : public Screen<AppContext>
{
private:
	sf::Sprite background;
	sf::Texture backgroundTexture;
	Button button;
	sf::Text title;
	sf::Text score;
	sf::Font font;

public:
	StartScreen(AppContext* context, std::map<std::string, std::string> params);

	void init() override {}

	void handleEvent(sf::Event& event) override;

	void process() override;

	void draw() override;

	void setView(unsigned int width, unsigned int height);

	~StartScreen(){}
};