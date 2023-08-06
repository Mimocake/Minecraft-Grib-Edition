#pragma once
#include <SFML/Graphics.hpp>
#include "Block.hpp"

class Screen
{
private:
	sf::RenderWindow window;
public:
	bool keys[6];
	sf::Vector2f mouse_offset;
	float tot_mouse_Yoffset;
	Screen();
	void clear();
	void display();
	void draw_block(math::vec3, Block&, math::mat4x4);
	bool events_handling();
};