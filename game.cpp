#include "game.h"
#include "particle.h"
#include <raylib.h>
#include <vector>

Game::Game(Vector2 dragStartPos) {
	this->dragStartPos = dragStartPos;
}

void Game::spawnParticle(std::vector<Particle>& particles) {
	Vector2 currentPos = GetMousePosition();
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		dragStartPos = currentPos;
	}
	if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
		Vector2 velocity = { (dragStartPos.x - currentPos.x), (dragStartPos.y - currentPos.y) };
		Color color = BLUE;
		Vector2 acceleration = { 0, 10.8f };
		int radius = 5;
		Particle newParticle(dragStartPos, velocity, color, acceleration, radius);
		particles.push_back(newParticle);
	}
}
