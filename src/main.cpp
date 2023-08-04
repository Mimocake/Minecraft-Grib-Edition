#include "Screen.hpp"
#include "Camera.hpp"
#include <iostream>
#include <Windows.h>

using namespace std;
using namespace sf;
using namespace math;

int main()
{
    Camera cam;
    Screen screen;
    Block block(vec3(-0.5, -0.5, 2));
    vec3 up(0, 1, 0);
    norm(cam.look_dir);
     
    while (screen.events_handling())
    {   
        vec3 vel(0, 0, 0);
        if (screen.keys[0]) vel += vec3(0, 0, 0.1);
        if (screen.keys[1]) vel += vec3(-0.1, 0, 0);
        if (screen.keys[2]) vel += vec3(0, 0, -0.1);
        if (screen.keys[3]) vel += vec3(0.1, 0, 0);
        if (screen.keys[4]) vel += vec3(0, -0.1, 0);
        if (screen.keys[5]) vel += vec3(0, 0.1, 0);
        cam.loc += vel;

        cam.turn(screen.mouse_offset.x, screen.mouse_offset.y);
        vec3 target = cam.loc + cam.look_dir;
        mat4x4 matCam = mat_pointAt(cam.loc, target, up);
        mat4x4 matView = mat_inverse(matCam);
        block.project(matView);

        screen.draw_block(cam.loc, block);
    }
    return 0;
}