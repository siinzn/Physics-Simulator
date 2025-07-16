#pragma once
#include"tigr.h"
#include "math.h"
#include <math.h>
#include <vector>
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

void particleCollision(Particle& p1, Particle& p2) {
    v2 distance_bw_particles = p1.position - p2.position;
    float distance = sqrt(distance_bw_particles.x * distance_bw_particles.x + distance_bw_particles.y * distance_bw_particles.y);
    if (distance < (p1.radius + p2.radius)) {
        v2 normal = (p1.position - p2.position) / distance;
        v2 relative_velocity = p1.velocity - p2.velocity;
        float velocity_normal = dot(relative_velocity, normal);

        if (velocity_normal > 0) return;
        float e = 1.0f;
        float j = -(1 + e) * velocity_normal / (1 / p1.mass + 1 / p2.mass);


        v2 impulse = normal * j;
        p1.velocity += impulse / p1.mass;
        p2.velocity -= impulse / p2.mass;

        float penetration = (p1.radius + p2.radius) - distance;
        float percent = 0.8f;
        v2 correction = normal * (penetration / (1 / p1.mass + 1 / p2.mass)) * percent;
        p1.position += correction * (1 / p1.mass);
        p2.position -= correction * (1 / p2.mass);
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
    float top_boundary = 240.0f - p.radius;

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

