#include "tigr.h"
#include "math.h"
#include "draw.h"
#include <iostream>

int main()
{
    screen = tigrWindow(640, 480, "Physics Simulator", 0);
    float dt = 1.0f / 60.0f;
    for (float i{ 1 }; i < 150; i++) {
        float random_height = height(gen);
        float random_width = width(gen);
        float random_VelX = velocityX(gen);
        float random_VelY = velocityY(gen);
        float random_radius = radius(gen);
        TPixel random_color = tigrRGB(colorDist(gen), colorDist(gen), colorDist(gen)); 


        particles.push_back(Particle(
            v2(random_width, random_height), 
            v2(random_VelX,random_VelY), 
            v2(0, 0), 
            10.0f * i, 
            random_radius,
            random_color));
    };
    while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {
        tigrClear(screen, color_black());
        for (auto& p : particles) {
            update(p, dt);
            draw_circle(p.position, p.radius, p.color);
        }
        for (size_t i{ 0 }; i < particles.size(); i++) {
            for (size_t j{ i + 1 }; j < particles.size(); j++) {
                particleCollision(particles[i], particles[j]);
            }
        }
        tigrUpdate(screen);
    }
    tigrFree(screen);
    return 0;
}
