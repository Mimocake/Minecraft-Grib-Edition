#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include "Block.hpp"
using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(VideoMode(1000, 1000), "Minecraft", Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    Block block(Vector3f(-0.5, -0.5, 6));
    block.project();
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed: window.close(); break;
            case Event::KeyPressed:
                if (Keyboard::isKeyPressed(Keyboard::Escape))
                {
                    window.close(); break;
                }
            }
        }        
        window.clear();
        for (int i = 0; i < block.proj_tris.size(); i++)
        {
            ConvexShape tri(3);
            for (int j = 0; j < 3; j++)
            {
                float x = (block.proj_tris[i].coords[j].x + 1);
                x *= window.getSize().x * 0.5;
                float y = (block.proj_tris[i].coords[j].y + 1);
                y *= window.getSize().y / 2;
                cout << x << " " << y << endl;
                tri.setPoint(j, Vector2f(x, y));
            }
            tri.setFillColor(Color::Red);
            tri.setOutlineThickness(1);
            window.draw(tri);
        }
        window.display();
    }
    return 0;
}