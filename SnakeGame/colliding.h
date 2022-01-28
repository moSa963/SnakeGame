#pragma once
#include "SFML/Graphics.hpp"

class Colliding
{
protected:
	virtual const sf::FloatRect getCollabseRect() const = 0;

	virtual bool isCollaped(sf::FloatRect other) const
	{
		return getCollabseRect().intersects(other);
	}

public:
	bool collapse(const Colliding& obj) const
	{
		return isCollaped(obj.getCollabseRect());
	}

};