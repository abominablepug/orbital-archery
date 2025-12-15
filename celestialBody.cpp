#include "celestialBody.h"
#include "raylib.h"
#include <cmath>

CelestialBody::CelestialBody(Vector2 position, float radius) {
	this->radius = radius;
	this->position = position;
}

Vector2 CelestialBody::resultantAcceleration(Vector2& otherPosition) {
	const double G = 6.67430e-11;
	float mass = radius * radius;

	float dx = otherPosition.x - position.x;
	float dy = otherPosition.y - position.y;
	float distanceSquared = dx * dx + dy * dy;

	if (distanceSquared == 0) {
		return { 0.0f, 0.0f };
	}

	float distance = std::sqrt(distanceSquared);
	float forceMagnitude = G * mass / distanceSquared;

	float directionX = dx / distance;
	float directionY = dy / distance;

	float accelerationX = forceMagnitude * directionX;
	float accelerationY = forceMagnitude * directionY;

	return { accelerationX, accelerationY };
}

void CelestialBody::draw() {
	DrawCircleV(position, radius, GREEN);
}

