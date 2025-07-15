#pragma once
#include "tigr.h"
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

v2 operator+(v2 a, v2 b) { return v2(a.x + b.x, a.y + b.y); };
v2 operator-(v2 a, v2 b) { return v2(a.x - b.x, a.y - b.y); };
v2 operator*(v2 a, float b) { return v2(a.x * b, a.y * b); };
v2 operator/(v2 a, float b) { return v2(a.x / b, a.y / b); };
Particle operator+(Particle a, v2 b) { return Particle(a.position + b, a.velocity, a.acceleration, a.mass, a.radius, a.color); }