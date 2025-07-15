#include "tigr.h"
#include <iostream>

Tigr* screen;

struct v2 {
    v2() {};
    v2(float x, float y) {
        this->x = x;
        this->y = y;
    }
    float x;
    float y;
};

struct Particle {
    Particle() {};
    Particle(v2 position, v2 velocity, v2 acceleration, float mass, float radius, TPixel color) {
        this->position = position;
        this->velocity = velocity;
        this->acceleration = acceleration;
        this->mass = mass;
        this->radius = radius;
        this->color = color;
    };
    v2 position;
    v2 velocity;
    v2 acceleration;
    float mass = 0.0f;
    float radius = 0.0f;
    TPixel color = tigrRGB(0xff, 0xff, 0xff);
};
v2 world_to_screen(v2 p) {
    p.y = -p.y;
    float half_screen_height = 480.0f / 2.0f;
    float half_screen_width = 640.0f / 2.0f;
    p.x += half_screen_width;
    p.y += half_screen_height;
    return p;
}

TPixel color_white() { return tigrRGB(0xff, 0xff, 0xff); };
TPixel color_black() { return tigrRGB(0, 0, 0); };
TPixel color_red() { return tigrRGB(0xFF, 0, 0); };
TPixel color_green() { return tigrRGB(0, 0xFF, 0); };
TPixel color_blue() { return tigrRGB(0, 0, 0xFF); };

v2 operator+(v2 a, v2 b) { return v2(a.x + b.x, a.y + b.y); };
v2 operator-(v2 a, v2 b) { return v2(a.x - b.x, a.y - b.y); };
v2 operator*(v2 a, float b) { return v2(a.x * b, a.y * b); };
v2 operator/(v2 a, float b) { return v2(a.x / b, a.y / b); };
Particle operator+(Particle a, v2 b) { return Particle(a.position + b, a.velocity, a.acceleration, a.mass, a.radius, a.color); }


void update(Particle& p, float dt) {
    p.acceleration.y = -100;
    p.velocity = p.velocity + p.acceleration * dt;
    p.position = p.position + p.velocity * dt;


    float bottom_boundary = -240.0f + p.radius;
    if (p.position.y < bottom_boundary) {
        p.velocity.y = - p.velocity.y * 0.75f;
        p.position.y = -241.0f + p.radius;
    }
}

void draw_circle(v2 a, float r, TPixel color) {
    a = world_to_screen(a);
    tigrCircle(screen, a.x, a.y, r, color);
    tigrFillCircle(screen, a.x, a.y, r, color);
}

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
