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
    Block block(vec3(-0.5, -0.5, 2));
    vec3 up(0, 1, 0);
    
    while (screen.events_handling())
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
        vec3 rot_vel = mat4x4_mult(vel, Matrix_MakeRotationY(phi));
        cam.loc += rot_vel;

        cam.turn(screen.mouse_offset.x, screen.mouse_offset.y);
        vec3 target = cam.loc + cam.look_dir;
        mat4x4 matCam = mat_pointAt(cam.loc, target, up);
        mat4x4 matView = mat_inverse(matCam);

        screen.clear();
        screen.draw_block(cam.loc, block, matView);
        screen.display();
    }
    return 0;
}