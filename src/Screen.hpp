#include "Block.hpp"

class Screen
{
private:
	sf::RenderWindow window;
public:
	Screen();
	void draw_block(sf::Vector3f, Block&);
	bool events_handling();
};