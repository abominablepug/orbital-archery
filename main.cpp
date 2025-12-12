#include <raylib.h>
#include "particle.h"
#include "game.h"
#include <vector>

Game game = Game();
std::vector<Particle> particles;

void drawParticles(float dt) {
	for (size_t i = 0; i < particles.size(); i++) {
		particles[i].update(dt);
		particles[i].draw();
		particles[i].particleCollision(particles, i);
		particles[i].boundsCollision(GetScreenWidth(), GetScreenHeight());
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

		game.spawnParticle(particles);

        BeginDrawing();

        ClearBackground(BLACK);

		drawParticles(dt);

        EndDrawing();
    }
    
    return 0;
}
