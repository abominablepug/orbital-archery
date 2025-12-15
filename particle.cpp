#include "raylib.h"
#include "raymath.h"
#include "particle.h"
#include "celestialBody.h"
#include <cmath>
#include <vector>

Particle::Particle(Vector2 pos, Vector2 vel, Color col, int rad) {
	position = pos;
	velocity = vel;
	color = col;
	radius = rad;
}

void Particle::setVelocity(Vector2 vel) {
	velocity = vel;
}

void Particle::setAcceleration(std::vector<CelestialBody>& celestialBodies) {
	Vector2 totalAcceleration = {0, 0};
	for (size_t i = 0; i < celestialBodies.size(); i++) {
		totalAcceleration = Vector2Add(totalAcceleration, celestialBodies[i].resultantAcceleration(this->position));
	}
	this->acceleration = totalAcceleration;
}

void Particle::particleCollision(std::vector<Particle>& particles, int index) {
	for (size_t j = 0; j < particles.size(); j++) {

		if (j == index) continue; // Skip self-collision

		Particle &other = particles[j];

		// Distance vector calculation
		float dx = this->position.x - other.position.x;
		float dy = this->position.y - other.position.y;
		float distanceSquared = dx * dx + dy * dy;
		float distance = std::sqrt(distanceSquared);

		// Check collision
		if (distance < this->radius + other.radius) {

			// Fix overlapping
			float overlap = (distance - this->radius - other.radius) / 2.0f;
			float moveX = overlap * (dx / distance);
			float moveY = overlap * (dy / distance);

			this->position.x -= moveX;
			this->position.y -= moveY;
			other.position.x += moveX;
			other.position.y += moveY;

			// Physics Calculation
			float m1 = this->radius * this->radius;
			float m2 = other.radius * other.radius;

			// Dot product of velocities
			float vDiffX = this->velocity.x - other.velocity.x;
			float vDiffY = this->velocity.y - other.velocity.y;
			float dotProduct = (dx * vDiffX + dy * vDiffY);

			// Avoid division by zero
			if (distanceSquared == 0) continue;

			// Scalar for collision response
			float collisionScale = dotProduct / ((m1 + m2) * distanceSquared);

			// Calculate new velocities
			float colX = dx * collisionScale;
			float colY = dy * collisionScale;

			this->velocity.x -= 2 * m2 * colX;
			this->velocity.y -= 2 * m2 * colY;

			other.velocity.x += 2 * m1 * colX;
			other.velocity.y += 2 * m1 * colY;
		}
	}
}

void Particle::boundsCollision(int screenWidth, int screenHeight) {
	if (position.x - radius < 0) {
		position.x = radius;
		velocity.x *= -1;
	} else if (position.x + radius > screenWidth) {
		position.x = screenWidth - radius;
		velocity.x *= -1;
	}

	if (position.y - radius < 0) {
		position.y = radius;
		velocity.y *= -1;
	} else if (position.y + radius > screenHeight) {
		position.y = screenHeight - radius;
		velocity.y *= -1;
	}
}

void Particle::collisionCheck(std::vector<Particle>& particles, int index, int screenWidth, int screenHeight, bool enableWallCollision) {
	particleCollision(particles, index);
	if (enableWallCollision) boundsCollision(screenWidth, screenHeight);
	}

void Particle::celestialCollision(std::vector<CelestialBody>& celestialBodies) {
	for (size_t i = 0; i < celestialBodies.size(); i++) {
		CelestialBody& body = celestialBodies[i];

        float dx = this->position.x - body.getPosition().x;
        float dy = this->position.y - body.getPosition().y;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance < this->radius + body.getRadius()) {
            
            float nx = dx / distance;
            float ny = dy / distance;

            float overlap = (this->radius + body.getRadius() - distance);
            this->position.x += nx * overlap;
            this->position.y += ny * overlap;

            float vn = this->velocity.x * nx + this->velocity.y * ny;

            if (vn > 0.0f) continue;

            float restingThreshold = 40.0f; // You may need to tweak this based on your gravity scale

            float restitution = 0.5f; 

            if (std::abs(vn) < restingThreshold) {
                this->velocity.x -= vn * nx;
                this->velocity.y -= vn * ny;
            } else {
                float impulse = -(1.0f + restitution) * vn;
                this->velocity.x += impulse * nx;
                this->velocity.y += impulse * ny;
            }
        }
	}
}

void Particle::update(float dt) {
	velocity.x += acceleration.x * dt;
	velocity.y += acceleration.y * dt;
	position.x += velocity.x * dt;
	position.y += velocity.y * dt;
}

void Particle::draw() {
	DrawCircle(position.x, position.y, radius, color);
}

