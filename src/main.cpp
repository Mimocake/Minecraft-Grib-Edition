#include "Screen.hpp"
#include "Camera.hpp"
#include <iostream>
#include <Windows.h>

using namespace std;
using namespace sf;
using namespace math;

int main()
{
    Screen screen;
    Camera cam;
    Block block(vec3(-0.5, -0.5, 2));
    vec3 up(0, 1, 0);
    cam.loc = vec3(0, 0, 0);
    cam.look_dir = vec3(0, 0, 1);
    norm(cam.look_dir);

    while (screen.events_handling())
    {   
        vec3 vel(0, 0, 0);
        if (screen.keys[0]) vel = vel + vec3(0, 0, 0.1);
        if (screen.keys[1]) vel = vel + vec3(-0.1, 0, 0);
        if (screen.keys[2]) vel = vel + vec3(0, 0, -0.1);
        if (screen.keys[3]) vel = vel + vec3(0.1, 0, 0);
        if (screen.keys[4]) vel = vel + vec3(0, -0.1, 0);
        if (screen.keys[5]) vel = vel + vec3(0, 0.1, 0);
        cam.loc = cam.loc + vel;

        vec3 target = cam.loc + cam.look_dir;
        mat4x4 matCam = mat_pointAt(cam.loc, target, up);
        mat4x4 matView = mat_inverse(matCam);
        block.project(matView);

        screen.draw_block(cam.loc, block);
    }
    return 0;
}