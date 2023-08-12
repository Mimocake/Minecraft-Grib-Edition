#include "Screen.hpp"
#include <iostream>
using namespace sf;
using namespace math;
using namespace std;

Screen::Screen() : mouse_offset(Vector2f(0, 0)), debug_info_key(false)
{   
    RenderWindow temp(VideoMode(), "", Style::Fullscreen);
    temp.close();
    Mouse::setPosition(Vector2i(temp.getSize().x / 2, temp.getSize().y / 2));
    window.create(VideoMode(), L"Minecraft", Style::Fullscreen);
	window.setMouseCursorVisible(false);
    for (int i = 0; i < 6; i++) keys[i] = false;
}

void Screen::clear() { window.clear(); }
void Screen::display() { window.display(); }

void Screen::draw_block(vec3 cam, Block& block, mat4x4 matView, Texture& tex)
{
    if (window.isOpen())
    {
        for (int i = 0; i < block.tris.size(); i++)
        {
            vec3 cam_dir = cam - block.tris[i].coords[0];
            cam_dir.norm();
            vec3 line1 = block.tris[i].coords[1] - block.tris[i].coords[0];
            vec3 line2 = block.tris[i].coords[2] - block.tris[i].coords[0];
            if (dot_prod(cam_dir, cross_prod(line1, line2)) > 0)
            {
                Triangle viewed, proj;
                for (int j = 0; j < 3; j++)
                {
                    viewed.coords[j] = mat4x4_mult(block.tris[i].coords[j], matView);
                    viewed.t_coords[j] = block.tris[i].t_coords[j];
                }

                vector<Triangle> clipped = viewed.clip_fun(vec3(0, 0, 0.3), vec3(0, 0, 1));
                for (int n = 0; n < clipped.size(); n++)
                {
                    vec2 t_c[3];
                    for (int r = 0; r < 3; r++)
                    {
                        t_c[r] = clipped[n].t_coords[r];
                    }
                    clipped[n] = clipped[n].project();
                    for (int r = 0; r < 3; r++)
                    {
                        clipped[n].t_coords[r] = t_c[r];
                    }
                }

                vector<Triangle> Q = clipped;
                for (int x = 0; x < 4; x++)
                {
                    vector<Triangle> temp;
                    for (int y = 0; y < Q.size(); y++)
                    {
                        Triangle t = Q[y];
                        vector<Triangle> new_t;
                        switch (x)
                        {
                        case 0: new_t = t.clip_fun(vec3(0, -1, 0), vec3(0, 1, 0)); break; //TOP
                        case 1: new_t = t.clip_fun(vec3(0, 1, 0), vec3(0, -1, 0)); break; //BOTTOM
                        case 2: new_t = t.clip_fun(vec3(-1, 0, 0), vec3(1, 0, 0)); break; //LEFT
                        case 3: new_t = t.clip_fun(vec3(1, 0, 0), vec3(-1, 0, 0)); break; //RIGHT
                        }
                        for (int z = 0; z < new_t.size(); z++)
                        {
                            temp.push_back(new_t[z]);
                        }
                    }
                    Q = temp;
                }

                for (auto& t : Q)
                {
                    VertexArray tri(Triangles, 3);
                    
                    VertexArray outline(LinesStrip, 4);
                    for (int j = 0; j < 4; j++)
                    {
                        float x = (t.coords[j % 3].x + 1) * window.getSize().x / 2;
                        float y = (t.coords[j % 3].y + 1) * window.getSize().y / 2;
                        outline[j].position = Vector2f(x, y);
                    }
                    for (int j = 0; j < 3; j++)
                    {
                        float x = (t.coords[j].x + 1) * window.getSize().x / 2;
                        float y = (t.coords[j].y + 1) * window.getSize().y / 2;
                        tri[j].position = Vector2f(x, y);
                        tri[j].texCoords = Vector2f(t.t_coords[j].u * tex.getSize().x, t.t_coords[j].v * tex.getSize().y);
                    }
                    window.draw(tri, &tex);
                    //window.draw(outline);
                }
            }
        }
    }
}

void Screen::show_debug_info(Text& FPS_text, Text& X_text, Text& Y_text, Text& Z_text)
{
    window.draw(FPS_text);
    window.draw(X_text);
    window.draw(Y_text);
    window.draw(Z_text);
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
            if (event.key.code == Keyboard::F3)
            {
                debug_info_key = !debug_info_key;
                window.setVerticalSyncEnabled(!debug_info_key);
            }
            break;
        case Event::KeyReleased:
            if (event.key.code == Keyboard::W) keys[0] = false;
            if (event.key.code == Keyboard::A) keys[1] = false;
            if (event.key.code == Keyboard::S) keys[2] = false;
            if (event.key.code == Keyboard::D) keys[3] = false;
            if (event.key.code == Keyboard::Space) keys[4] = false;
            if (event.key.code == Keyboard::LShift) keys[5] = false;
            break;
        case Event::MouseMoved:
            mouse_offset.x = event.mouseMove.x - (float)window.getSize().x;
            mouse_offset.x = mouse_offset.x / (window.getSize().x / 2) + 1;
            mouse_offset.y = event.mouseMove.y - (float)window.getSize().y;
            mouse_offset.y = mouse_offset.y / (window.getSize().y / 2) + 1;
            mouse_offset.y *= aspect;
            Mouse::setPosition(Vector2i(window.getSize().x / 2, window.getSize().y / 2));
            break;
        }
    }
    if (window.isOpen()) return true;
}