#pragma once
#include "tigr.h"
#include <vector>
#include <random>
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
    Particle(v2 position, v2 velocity, v2 acceleration, float mass, float radius) {
        this->position = position;
        this->velocity = velocity;
        this->acceleration = acceleration;
        this->mass = mass;
        this->radius = radius;
    };
    v2 position;
    v2 velocity;
    v2 acceleration;
    float mass = 0.0f;
    float radius = 0.0f;
};

std::vector<Particle> particles;

v2 operator+(v2 a, v2 b) { return v2(a.x + b.x, a.y + b.y); };
v2 operator-(v2 a, v2 b) { return v2(a.x - b.x, a.y - b.y); };
v2 operator*(v2 a, float b) { return v2(a.x * b, a.y * b); };
v2 operator/(v2 a, float b) { return v2(a.x / b, a.y / b); };
Particle operator+(Particle a, v2 b) { return Particle(a.position + b, a.velocity, a.acceleration, a.mass, a.radius); }

Particle p;
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> height(-240.0f + p.radius, 240.0f - p.radius);
std::uniform_real_distribution<> width(-320.0f + p.radius, 320.0f - p.radius);
std::uniform_real_distribution<> velocityX(5, 50);
std::uniform_real_distribution<> velocityY(10, 50);
std::uniform_real_distribution<> radius(5, 25);


