#include "Screen.hpp"
using namespace sf;
using namespace math;

Screen::Screen() : window(VideoMode(), "Minecraft", Style::Fullscreen)
{
	window.setVerticalSyncEnabled(true);
	window.setMouseCursorVisible(false);
    for (int i = 0; i < 6; i++) keys[i] = false;
}

void Screen::draw_block(vec3 cam, Block& block)
{
    if (window.isOpen())
    {
        window.clear();
        for (int i = 0; i < block.tris.size(); i++)
        {
            vec3 cam_dir = cam - block.tris[i].coords[0];
            norm(cam_dir);
            if (dot_prod(cam_dir, block.tris[i].normal) > 0)
            {
                VertexArray tri(LinesStrip, 4);
                for (int j = 0; j < 4; j++)
                {
                    float x = (block.tris[i].proj_coords[j % 3].x + 1) * window.getSize().x / 2;
                    float y = (block.tris[i].proj_coords[j % 3].y + 1) * window.getSize().y / 2;
                    tri[j] = Vector2f(x, y);
                }
                window.draw(tri);
            }
        }
        window.display();
    }
}

bool Screen::events_handling()
{
    Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case Event::Closed: window.close(); break;
        case Event::KeyPressed:
            if (event.key.code == Keyboard::Escape) window.close();
            if (event.key.code == Keyboard::W) keys[0] = true;
            if (event.key.code == Keyboard::A) keys[1] = true;
            if (event.key.code == Keyboard::S) keys[2] = true;
            if (event.key.code == Keyboard::D) keys[3] = true;
            if (event.key.code == Keyboard::Space) keys[4] = true;
            if (event.key.code == Keyboard::LShift) keys[5] = true;
            break;
        case Event::KeyReleased:
            if (event.key.code == Keyboard::W) keys[0] = false;
            if (event.key.code == Keyboard::A) keys[1] = false;
            if (event.key.code == Keyboard::S) keys[2] = false;
            if (event.key.code == Keyboard::D) keys[3] = false;
            if (event.key.code == Keyboard::Space) keys[4] = false;
            if (event.key.code == Keyboard::LShift) keys[5] = false;
            break;
        }
    }
    if (window.isOpen()) return true;
}