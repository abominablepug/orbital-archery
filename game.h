#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include <vector>
#include "particle.h"
#include "celestialBody.h"

class Game {
private:
	Vector2 dragStartPos;
public:

	Game(Vector2 dragStartPos = {0, 0});

	void spawnParticle(std::vector<Particle>& particles);

	void spawnCelestialBody(std::vector<CelestialBody>& celestialBodies);
};

#endif
