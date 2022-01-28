#pragma once
#include "SFML/Graphics.hpp"
#include "drawable.h"

template<typename Context>
class Screen : public Drawable<Context>
{
protected:
    const std::map<std::string, std::string> params;

public:
    Screen(Context* context) 
        : Drawable<Context>(context), params() 
    {}

    Screen(Context* context, std::map<std::string, std::string> params) 
        : Drawable<Context>(context), params(params)
    {}

    virtual void init() {};
    
    virtual void handleEvent(sf::Event& event) {};
    virtual void process() {};
    virtual void draw() = 0;
};