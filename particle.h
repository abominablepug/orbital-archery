#ifndef PARTICLE_H
#define PARTICLE_H

#include "raylib.h"
#include <vector>

class Particle {
    private:
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    int radius;
    Color color;

    public:
    Particle(Vector2 pos, Vector2 vel, Color col, Vector2 acc = {0, 9.81f}, int rad = 5);

	void setVelocity(Vector2 vel);

	void particleCollision(std::vector<Particle>& particles, int index);

    void update(float dt);

    void draw();
};

#endif // PARTICLE_H
