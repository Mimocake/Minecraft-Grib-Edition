#include "Screen.hpp"
#include "Camera.hpp"
#include <iostream>

using namespace std;
using namespace sf;
using namespace math;

int main()
{
    Camera cam;
    Screen screen;
    Block block(vec3(0, 0, 2));
    vec3 up(0, 1, 0);
    
    Clock clock;
    Clock clock_for_movement;
    Clock clock_for_FPS;

    Text FPS_text;
    Font font;
    font.loadFromFile("fonts/videotype.ttf");
    FPS_text.setFont(font);
    FPS_text.setFillColor(Color::White);
    FPS_text.setPosition(sf::Vector2f(10, 10));
    FPS_text.setCharacterSize(25);
    FPS_text.setString("FPS: ");

    while (screen.events_handling())
    {   
        if (clock_for_movement.getElapsedTime().asMilliseconds() >= 10)
        {
            vec3 vel(0, 0, 0);
            if (screen.keys[0]) vel += vec3(0, 0, 0.1);
            if (screen.keys[1]) vel += vec3(-0.1, 0, 0);
            if (screen.keys[2]) vel += vec3(0, 0, -0.1);
            if (screen.keys[3]) vel += vec3(0.1, 0, 0);
            if (screen.keys[4]) vel += vec3(0, -0.1, 0);
            if (screen.keys[5]) vel += vec3(0, 0.1, 0);

            vec3 temp_dir(cam.look_dir.x, 0, cam.look_dir.z);
            temp_dir.norm();
            float phi = acos(dot_prod(temp_dir, vec3(0, 0, 1)));
            phi = (temp_dir.x < 0) ? phi : -phi;
            vec3 rot_vel = mat4x4_mult(vel, rot_y(phi));
            cam.loc += rot_vel;
            clock_for_movement.restart();
        }

        cam.turn(screen.mouse_offset.x, screen.mouse_offset.y);
        vec3 target = cam.loc + cam.look_dir;
        mat4x4 matCam = mat_pointAt(cam.loc, target, up);
        mat4x4 matView = mat_inverse(matCam);

        screen.clear();
        screen.draw_block(cam.loc, block, matView);

        if (clock_for_FPS.getElapsedTime().asMilliseconds() >= 500)
        {
            float elapsed_time = clock.getElapsedTime().asSeconds();
            int fps = 1.0f / elapsed_time;
            FPS_text.setString("FPS: " + to_string(fps));
            clock_for_FPS.restart();
        }
        clock.restart();
        if(screen.debug_info_key) screen.show_debug_info(FPS_text);

        screen.display();
    }
    return 0;
}