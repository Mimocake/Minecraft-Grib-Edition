#pragma once
#include <SFML/Graphics.hpp>
#include "Block.hpp"

class Screen
{
private:
	sf::RenderWindow window;
public:
	bool keys[6];
	Screen();
	void draw_block(math::vec3, Block&);
	bool events_handling();
};