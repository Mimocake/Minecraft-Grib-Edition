#pragma once
#include "Block.hpp"

class Screen
{
private:
	sf::RenderWindow window;
public:
	bool keys[6];
	Screen();
	void draw_block(sf::Vector3f, Block&);
	bool events_handling();
};