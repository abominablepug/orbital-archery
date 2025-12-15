#include <raylib.h>
#include <vector>
#include "particle.h"
#include "celestialBody.h"
#include "game.h"

Game game = Game();
std::vector<Particle> particles;
std::vector<CelestialBody> celestialBodies;

void update(float dt) {
	for (size_t i = 0; i < particles.size(); i++) {
		particles[i].setAcceleration(celestialBodies);
		particles[i].update(dt);
		particles[i].collisionCheck(particles, i, GetScreenWidth(), GetScreenHeight(), game.enableWallCollision);
		particles[i].celestialCollision(celestialBodies);
		particles[i].draw();
	}
	for (size_t i = 0; i < celestialBodies.size(); i++) {
		celestialBodies[i].draw();
	}
}

int main() {
    
    const int SCREEN_WIDTH = 1920;
    const int SCREEN_HEIGHT = 1080;
    const int TARGET_FPS = 180;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Orbital Archery");
    SetTargetFPS(TARGET_FPS);

    while (!WindowShouldClose()) {

        float dt = GetFrameTime();


        BeginDrawing();

        ClearBackground(BLACK);

		if (game.currentState == MENU) {
			game.drawStartScreen();
		} else if (game.currentState == PLAYING) {
			BeginMode2D(game.camera);
				DrawRectangleLines(0, 0, GetScreenWidth(), GetScreenHeight(), DARKGRAY);
				game.spawnParticle(particles);
				game.spawnCelestialBody(celestialBodies);
				update(dt);
			EndMode2D();
			game.drawSideBar(particles, celestialBodies);
		}

        EndDrawing();
    }
    
	CloseWindow();
    return 0;
}
