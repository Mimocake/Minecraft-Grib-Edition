#include "Screen.hpp"
#include "Camera.hpp"
#include <iostream>
#include <Windows.h>

using namespace std;
using namespace sf;

int main()
{
    Screen screen;
    Camera cam;
    Block block(Vector3f(-0.5, -0.5, 1));
    Vector3f up(0, 1, 0);

    while (screen.events_handling())
    {   
        Vector3f vel(0, 0, 0);
        if (screen.keys[0]) vel += Vector3f(0, 0, 0.5);
        if (screen.keys[1]) vel += Vector3f(-0.5, 0, 0);
        if (screen.keys[2]) vel += Vector3f(0, 0, -0.5);
        if (screen.keys[3]) vel += Vector3f(0.5, 0, 0.5);
        if (screen.keys[4]) vel += Vector3f(0, -0.5, 0);
        if (screen.keys[5]) vel += Vector3f(0, 0.5, 0);
        cam.loc += vel;

        Vector3f target = cam.loc + cam.look_dir;
        math::mat4x4 matCam = math::mat_pointAt(cam.loc, target, up);
        math::mat4x4 matView = math::mat_inverse(matCam);

        block.project(matView);

        screen.draw_block(cam.loc, block);
    }
    return 0;
}