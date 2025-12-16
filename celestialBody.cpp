#include "celestialBody.h"
#include "raylib.h"
#include <cmath>

CelestialBody::CelestialBody(Vector2 position, float radius, int texIndex) {
	this->radius = radius;
	this->position = position;
	this->texIndex = texIndex;
}

Vector2 CelestialBody::resultantAcceleration(Vector2& otherPosition) {
	const float G = 1000.0f;  // Scaled gravitational constant for game physics
	float mass = radius * radius * 100.0f;  // Mass proportional to area, scaled for effect

	float dx = otherPosition.x - position.x;
	float dy = otherPosition.y - position.y;
	float distanceSquared = dx * dx + dy * dy;

	if (distanceSquared == 0) {
		return { 0.0f, 0.0f };
	}

	float distance = std::sqrt(distanceSquared);
	float forceMagnitude = G * mass / distanceSquared;

	float directionX = -dx / distance;
	float directionY = -dy / distance;

	float accelerationX = forceMagnitude * directionX;
	float accelerationY = forceMagnitude * directionY;

	return { accelerationX, accelerationY };
}

void CelestialBody::draw() {
	float scale = (radius * 2.0f) / celestialTex[texIndex].width;
	Vector2 pos = { position.x - radius, position.y - radius };
	DrawTextureEx(celestialTex[texIndex], pos, 0.0f, scale, WHITE);
}

