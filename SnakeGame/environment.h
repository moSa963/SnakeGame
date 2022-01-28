#pragma once
#include "SFML/Graphics.hpp"
#include "board.h"
#include "drawable.h"
#include "appContext.h"

class Environment : public Drawable<AppContext>
{
private:
	sf::Sprite background;
	sf::Texture backgroundTexture;
	Board board;

public:
	Environment(AppContext* context);

	void draw() override;

	const Board& getBoard() const;

	Board& getRoot()
	{
		return board;
	}
};