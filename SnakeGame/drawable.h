#pragma once
#include "SFML/Graphics.hpp"

template<typename Context>
class Drawable
{
protected:
    Context* context;

public:
    Drawable(Context* context) : context(context) {}

	virtual void draw() = 0;
};