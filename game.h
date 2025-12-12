#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "particle.h"
#include <vector>

class Game {
private:
	Vector2 dragStartPos;
public:
	Game(Vector2 dragStartPos = {0, 0});
	void spawnParticle(std::vector<Particle>& particles);
};

#endif
