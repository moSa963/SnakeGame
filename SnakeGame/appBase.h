#pragma once
#include "appContext.h"

class AppBase
{
protected:
	AppContext context;

	//get screen by key
	virtual Screen<AppContext>* getScreen(std::string key, std::map<std::string, std::string> params) = 0;

	virtual int init();

public:
	AppBase(unsigned int width, unsigned int height, std::string&& name);

	//load textures
	//first value should be the key and second value is the file path
	virtual std::map<std::string, std::string> initTextures() = 0;

	//load fonts
	//first value should be the key and second value is the file path
	virtual std::map<std::string, std::string> initFonts() = 0;

	virtual std::string firstScreenKey() = 0;

	//main loop
	int start();
};