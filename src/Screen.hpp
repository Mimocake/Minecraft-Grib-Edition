#pragma once
#include <SFML/Graphics.hpp>
#include "Block.hpp"

class Screen
{
private:
	sf::RenderWindow window;
public:
	bool keys[6];
	bool debug_info_key;
	sf::Vector2f mouse_offset;
	Screen();
	void clear();
	void display();
	void draw_block(math::vec3, Block&, math::mat4x4, sf::Texture&);
	void show_debug_info(sf::Text&, sf::Text&, sf::Text&, sf::Text&);
	bool events_handling();
};