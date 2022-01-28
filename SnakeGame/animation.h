#pragma once
#include "SFML/Graphics.hpp"
#include <functional>

template<typename T, typename G = std::function<void(T&, float)>>
class Animation
{
private:
	T& object;
	G func;
	sf::Clock clock;
	std::vector<float> values;
	std::vector<float> moves;
	bool running;
	bool paused;
	int repeat;
	int duration;
	int counter;
	int delay;
	std::function<void(void)> animationEnd;

private:
	float getNext()
	{
		float elapsedRatio = (float)clock.getElapsedTime().asMilliseconds() / duration;
		unsigned int index = 0;

		if (elapsedRatio == 0) return values[0];

		for (unsigned int i = 1; i < moves.size(); ++i)
		{
			if (moves[i] >= elapsedRatio)
			{
				float ratio = (elapsedRatio - moves[i - 1]) / (moves[i] - moves[i - 1]);

				return values[i - 1] + ((values[i] - values[i - 1]) * ratio);
			}
		}

		paused = true;

		if (repeat > 0)
		{
			if (repeat > counter) running = false;
			else ++counter;
		}

		clock.restart();

		return values[values.size() - 1];
	}


public:

	//if repeat is 0 the animation will be repeated until stop method get called
	Animation(T& object, int duration = 300, int repeat = 1, std::vector<float> values = {0.0f, 1.0f}, int delay = 0)
		: running(false), object(object), moves(), counter(0),
			duration(duration), repeat(repeat), values(values), delay(delay), paused(true)
	{
		for (float i = 0; i < values.size(); ++i)
		{
			moves.push_back(i / (values.size() - 1));
		}
	}

	//start the animation
	void start()
	{
		running = true;
		paused = true;
		counter = 0;
		clock.restart();
	}

	//"moves" used to determine how much percentage each jump should take from one value to the next
	//the vector size should be the same as the moves vector size
	//values must range from 0 to 1 in ascending order
	void setMoves(std::vector<float> moves)
	{
		this->moves = moves;
	}

	//stop the animation
	void stop()
	{
		running = false;
		paused = true;
		if (animationEnd) animationEnd();
	}

	//callback after the animation is finished or stoped
	void setAnimationEndCallback(std::function<void(void)> callback)
	{
		this->animationEnd = callback;
	}


	void process()
	{
		if (running)
		{
			if (paused)
			{
				if (clock.getElapsedTime().asMilliseconds() > delay) {
					paused = false;
					clock.restart();
				}
				else
				{
					return;
				}
			}

			float value = getNext();

			func(object, value);

			if (!running)
			{
				stop();
			}
		}
	}

	//callback called each iteration with the object and the animation value
	void setCallBack(G function)
	{
		func = function;
	}

	//delay before the animation start
	//if the animation repeated there will be delay for each repeat
	void setDelay(int duration)
	{
		delay = duration;
	}

	bool isRunning()
	{
		return running;
	}
};