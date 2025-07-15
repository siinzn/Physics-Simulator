#pragma once
#include"tigr.h"
#include "math.h"
Tigr* screen;

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

void update(Particle& p, float dt) {
    p.acceleration.y = -100;
    p.velocity = p.velocity + p.acceleration * dt;
    p.position = p.position + p.velocity * dt;


    float bottom_boundary = -240.0f + p.radius;
    if (p.position.y < bottom_boundary) {
        p.velocity.y = -p.velocity.y * 0.75f;
        p.position.y = -241.0f + p.radius;
    }
}

void draw_circle(v2 a, float r, TPixel color) {
    a = world_to_screen(a);
    tigrCircle(screen, a.x, a.y, r, color);
    tigrFillCircle(screen, a.x, a.y, r, color);
}

