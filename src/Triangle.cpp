#include "Triangle.hpp"

Triangle::Triangle(sf::Vector3f p1, sf::Vector3f p2, sf::Vector3f p3) : coords(3)
{
	coords[0] = p1; coords[1] = p2; coords[2] = p3;
}