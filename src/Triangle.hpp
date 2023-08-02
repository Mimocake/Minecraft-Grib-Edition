#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include "Functions.hpp"
using namespace std;
using namespace sf;

class Triangle
{
public:
	vector<sf::Vector3f> coords;
	Triangle(sf::Vector3f, sf::Vector3f, sf::Vector3f);
	Triangle() {}
};