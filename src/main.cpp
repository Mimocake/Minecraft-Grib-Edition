#include "Screen.hpp"
using namespace std;
using namespace sf;

int main()
{
    Screen screen;
    Block block(Vector3f(-1.2, -0.2, -0.5));
    block.project();
    Vector3f cam(0, 0, 0);
    while (screen.events_handling())
    {        
        screen.draw_block(cam, block);
    }
    return 0;
}