#include "game.h"
#include "particle.h"
#include "celestialBody.h"
#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <cmath>

const float mult = 2.0f;

Game::Game(Vector2 dragStartPos) {
	this->dragStartPos = dragStartPos;
}

void Game::spawnParticle(std::vector<Particle>& particles) {
	Vector2 currentPos = GetMousePosition();
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		dragStartPos = currentPos;
	}
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
		float angle = atan2f(dragStartPos.y - currentPos.y, dragStartPos.x - currentPos.x);
		float arrowSize = 20.0f;
		float arrowAngle = 30.0f * DEG2RAD;

		float triangleHeight = arrowSize * cosf(arrowAngle);
		Vector2 shaftEnd = {
			dragStartPos.x - triangleHeight * cosf(angle),
			dragStartPos.y - triangleHeight * sinf(angle)
		};

		Vector2 rightWing = {
			dragStartPos.x - arrowSize * cosf(angle - arrowAngle),
			dragStartPos.y - arrowSize * sinf(angle - arrowAngle)
		};
		Vector2 leftWing = {
			dragStartPos.x - arrowSize * cosf(angle + arrowAngle),
			dragStartPos.y - arrowSize * sinf(angle + arrowAngle)
		};

		if (currentPos.x != dragStartPos.x || currentPos.y != dragStartPos.y) {
			DrawLineEx(shaftEnd, currentPos, 10.0f, RED);
			DrawTriangle(dragStartPos, leftWing, rightWing, RED);
		}
	}
	if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
		Vector2 velocity = { (dragStartPos.x - currentPos.x) * mult, (dragStartPos.y - currentPos.y) * mult };
		Color color = BLUE;
		int radius = 5;
		Particle newParticle(currentPos, velocity, color, radius);
		particles.push_back(newParticle);
	}
}

void Game::spawnCelestialBody(std::vector<CelestialBody>& celestialBodies) {
	Vector2 currentPos = GetMousePosition();
	if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
		dragStartPos = currentPos;
	}
	if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
		float radius = Vector2Distance(dragStartPos, currentPos);
		DrawCircleV(dragStartPos, radius, GREEN);
	}
	if (IsMouseButtonReleased(MOUSE_RIGHT_BUTTON)) {
		float radius = Vector2Distance(dragStartPos, currentPos);
		CelestialBody newBody(dragStartPos, radius);
		celestialBodies.push_back(newBody);
	}
}
