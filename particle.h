#ifndef PARTICLE_H
#define PARTICLE_H

#include "raylib.h"
#include "celestialBody.h"
#include <vector>

class Particle {
    private:
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration = { 0.0f, 0.0f };
    int radius;
    Color color;

	void particleCollision(std::vector<Particle>& particles, int index);

	void boundsCollision(float left, float right, float top, float bottom);

    public:
    Particle(Vector2 pos, Vector2 vel, Color col, int rad = 5);

	void setVelocity(Vector2 vel);

	void setAcceleration(std::vector<CelestialBody>& celestialBodies);

	void celestialCollision(std::vector<CelestialBody>& celestialBodies);

	void collisionCheck(std::vector<Particle>& particles, int index, float left, float right, float top, float bottom, bool enableWallCollision);

    void update(float dt);

    void draw();

	Vector2 getPosition() { return position; }

	float getRadius() { return radius; }
};

#endif
