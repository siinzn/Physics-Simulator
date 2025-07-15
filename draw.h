#pragma once
#include"tigr.h"
#include "math.h"
#include <math.h>
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

void draw_circle(v2 a, float r, TPixel color) {
    a = world_to_screen(a);
    tigrCircle(screen, a.x, a.y, r, color);
    tigrFillCircle(screen, a.x, a.y, r, color);
}

v2 screen_to_world(v2 screen_pos) {
    screen_pos.x -= 320.0f;
    screen_pos.y -= 240.0f;
    screen_pos.y = -screen_pos.y;
    return screen_pos;
}


void repelParticles(Particle& p) {
    int mouseX, mouseY, buttons;
    tigrMouse(screen, &mouseX, &mouseY, &buttons);
    v2 mouse_world = screen_to_world(v2(float(mouseX), float(mouseY)));
    v2 direction = p.position - mouse_world;
    float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

    float repulsion_range = 200.0f;
    if (distance < repulsion_range && distance > 0) {
        float repulsion_strength = 300.0f;
        v2 normalized = direction / distance;
        float strength = repulsion_strength * (1.0f - (distance / repulsion_range));
        v2 repel_force = normalized * strength;
        p.acceleration = p.acceleration + repel_force;
    }
}

void update(Particle& p, float dt) {
    p.acceleration = v2(0, 0);
    p.acceleration = p.acceleration + v2(0, -100.0f);
    repelParticles(p);
    p.velocity = p.velocity + p.acceleration * dt;
    p.position = p.position + p.velocity * dt;


    float bottom_boundary = -240.0f + p.radius;
    float right_side_boundary = 320.0f - p.radius;
    float left_side_boundary = -320.0f + p.radius;
    float top_boundary = 240.0f + p.radius;

    if (p.position.y > top_boundary) {
        p.velocity.y = -p.velocity.y * 0.75f;
        p.position.y = 240.0f - p.radius;
    }

    if (p.position.y < bottom_boundary) {
        p.velocity.y = -p.velocity.y * 0.75f;
        p.position.y = -240.0f + p.radius;
    }

    if (p.position.x > right_side_boundary) {
        p.velocity.x = -p.velocity.x * 0.75f;
        p.position.x = 320.0f - p.radius;

    }
    if (p.position.x < left_side_boundary) {
        p.velocity.x = -p.velocity.x * 0.75f;
        p.position.x = -320.0f + p.radius;
    }
}

