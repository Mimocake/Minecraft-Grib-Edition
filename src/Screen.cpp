#include "Screen.hpp"
using namespace sf;

Screen::Screen() : window(VideoMode(), "Minecraft", Style::Fullscreen)
{
	window.setVerticalSyncEnabled(true);
	window.setMouseCursorVisible(false);
}

void Screen::draw_block(Vector3f cam, Block& block)
{
    if (window.isOpen())
    {
        window.clear();
        for (int i = 0; i < block.proj_tris.size(); i++)
        {
            Vector3f cam_dir = cam - block.proj_tris[i].coords[0];
            math::norm(cam_dir);
            if (math::dot_prod(cam_dir, block.proj_tris[i].normal) > 0)
            {
                VertexArray tri(LinesStrip, 4);
                for (int j = 0; j < 4; j++)
                {
                    float x = (block.proj_tris[i].coords[j % 3].x + 1) * window.getSize().x / 2;
                    float y = (block.proj_tris[i].coords[j % 3].y + 1) * window.getSize().y / 2;
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
            // window closed
        case Event::Closed: window.close(); break;
        case Event::KeyPressed:
            if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
            break;
        default:
            break;
        }
    }
    if (window.isOpen()) return true;
}