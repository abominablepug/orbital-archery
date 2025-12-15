#include <raylib.h>
#include <vector>
#include "particle.h"
#include "celestialBody.h"
#include "game.h"

Game game = Game();
std::vector<Particle> particles;
std::vector<CelestialBody> celestialBodies;

void drawParticles(float dt) {
	for (size_t i = 0; i < particles.size(); i++) {
		particles[i].update(dt);
		particles[i].draw();
		particles[i].particleCollision(particles, i);
		particles[i].boundsCollision(GetScreenWidth(), GetScreenHeight());
	}
}

void drawCelestialBodies() {
	for (size_t i = 0; i < celestialBodies.size(); i++) {
		celestialBodies[i].draw();
	}
}

int main() {
    
    const int SCREEN_WIDTH = 1920;
    const int SCREEN_HEIGHT = 1080;
    const int TARGET_FPS = 60;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Orbital Archery");
    SetTargetFPS(TARGET_FPS);

    while (!WindowShouldClose()) {

        float dt = GetFrameTime() * 3;


        BeginDrawing();

        ClearBackground(BLACK);

		game.spawnParticle(particles);
		game.spawnCelestialBody(celestialBodies);
		drawParticles(dt);
		drawCelestialBodies();

        EndDrawing();
    }
    
    return 0;
}
