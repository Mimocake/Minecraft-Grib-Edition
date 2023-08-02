#include "Block.hpp"
using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(), "Minecraft", Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    window.setMouseCursorVisible(false);
    Block block(Vector3f(3, 5, 7));
    block.project();
    Vector3f cam(0, 0, 0);
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
            if (math::dot_prod(cam - block.proj_tris[i].coords[0], block.proj_tris[i].normal) > 0)
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
    return 0;
}