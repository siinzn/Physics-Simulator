#include "tigr.h"
#include "math.h"
#include "draw.h"
#include <iostream>

int main()
{
    screen = tigrWindow(640, 480, "Physics Simulator", 0);
    Particle p;
    p.radius = 20.0f;
    p.position = v2(0, 200);
    float dt = 1.0f / 60.0f;
    p.velocity = v2(0, 0);
    p.acceleration = v2(0, 0);
    while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {
        tigrClear(screen, color_black());
        update(p, dt);
        draw_circle(p.position, p.radius, color_green());
        tigrUpdate(screen);
    }
    tigrFree(screen);
    return 0;
}
