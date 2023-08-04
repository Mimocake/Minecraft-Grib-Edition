#pragma once
#include <SFML/Graphics.hpp>
#include "Block.hpp"

class Screen
{
private:
	sf::RenderWindow window;
public:
	bool keys[6];
	sf::Vector2i starting_mouse_coords;
	sf::Vector2f mouse_offset;
	float tot_mouse_Yoffset;
	Screen();
	void draw_block(math::vec3, Block&);
	bool events_handling();
};