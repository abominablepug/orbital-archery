#include <raylib.h>
#include "particle.h"
#include <vector>

std::vector<Particle> particles;

void drawParticles(float dt) {
	for (size_t i = 0; i < particles.size(); i++) {
		particles[i].update(dt);
		particles[i].draw();
		particles[i].particleCollision(particles, i);
	}
}

void spawnParticle() {
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		Vector2 mousePos = GetMousePosition();
		Vector2 velocity = { 50.0f, -50.0f };
		Color color = BLUE;
		Vector2 acceleration = { 0, 10.8f };
		int radius = 5;
		Particle newParticle(mousePos, velocity, color, acceleration, radius);
		particles.push_back(newParticle);
	}
};

int main() {
    
    const int SCREEN_WIDTH = 1920;
    const int SCREEN_HEIGHT = 1080;
    const int TARGET_FPS = 60;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Orbital Archery");
    SetTargetFPS(TARGET_FPS);

    while (!WindowShouldClose()) {

        float dt = GetFrameTime() * 3;
		spawnParticle();

        BeginDrawing();

        ClearBackground(BLACK);

		drawParticles(dt);

        EndDrawing();
    }
    
    return 0;
}
