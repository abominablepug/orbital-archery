#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include <vector>
#include <string>
#include "particle.h"
#include "celestialBody.h"

enum GameState {
	MENU,
	PLAYING
};

class Game {
private:
	Vector2 dragStartPos;
	bool isSideBarOpen;
	Rectangle sideBarRect;
	Rectangle sideBarToggleRect;
public:
	GameState currentState;
	Camera2D camera;

	bool enableWallCollision;
	float particleMass;
	float zoomLevel;
	float timeScale;

	Game(Vector2 dragStartPos = {0, 0});

	Vector2 getWorldMousePosition();

	void spawnParticle(std::vector<Particle>& particles);
	void spawnCelestialBody(std::vector<CelestialBody>& celestialBodies);

	void drawStartScreen();
	void drawSideBar(std::vector<Particle>& particles, std::vector<CelestialBody>& celestialBodies);
};

#endif
