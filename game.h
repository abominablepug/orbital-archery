#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "particle.h"
#include <vector>
#include "celestialBody.h"

class Game {
private:
	Vector2 dragStartPos;
public:

	Game(Vector2 dragStartPos = {0, 0});

	float Vector2Distance(Vector2 a, Vector2 b);

	void spawnParticle(std::vector<Particle>& particles);

	void spawnCelestialBody(std::vector<CelestialBody>& celestialBodies);
};

#endif
