#include <raylib.h>
#include <vector>
#include "particle.h"
#include "celestialBody.h"
#include "game.h"
#include "embedded_assets.h"

Game game = Game();
std::vector<Particle> particles;
std::vector<CelestialBody> celestialBodies;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int WORLD_WIDTH = 4000;
const int WORLD_HEIGHT = 4000;
const int TARGET_FPS = 180;

Texture2D projectileTex;
Texture2D celestialTex[8];

Texture2D LoadTextureFromEmbedded(const unsigned char* data, int dataSize) {
    Image img = LoadImageFromMemory(".png", data, dataSize);
    Texture2D tex = LoadTextureFromImage(img);
    UnloadImage(img);
    return tex;
}

void update(float dt) {
	float left = game.camera.target.x - (SCREEN_WIDTH / 2.0f) / game.camera.zoom;
	float right = game.camera.target.x + (SCREEN_WIDTH / 2.0f) / game.camera.zoom;
	float top = game.camera.target.y - (SCREEN_HEIGHT / 2.0f) / game.camera.zoom;
	float bottom = game.camera.target.y + (SCREEN_HEIGHT / 2.0f) / game.camera.zoom;

	for (size_t i = 0; i < particles.size(); i++) {
		particles[i].setAcceleration(celestialBodies);
		particles[i].update(dt);
		particles[i].collisionCheck(particles, i, left, right, top, bottom, game.enableWallCollision);
		particles[i].celestialCollision(celestialBodies);
		particles[i].draw(game.isDebug);
	}
	for (size_t i = 0; i < celestialBodies.size(); i++) {
		celestialBodies[i].draw();
	}
}

int main() {
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Orbital Archery");
    SetTargetFPS(TARGET_FPS);

	projectileTex = LoadTextureFromEmbedded(assets_arrow_png, assets_arrow_png_len);

	const unsigned char* planetData[] = {
        assets_planet1_png, assets_planet2_png, assets_planet3_png, assets_planet4_png,
        assets_planet5_png, assets_planet6_png, assets_planet7_png, assets_planet8_png
    };
    
    const unsigned int planetLens[] = {
        assets_planet1_png_len, assets_planet2_png_len, assets_planet3_png_len, assets_planet4_png_len,
        assets_planet5_png_len, assets_planet6_png_len, assets_planet7_png_len, assets_planet8_png_len
    };

    for(int i = 0; i < 8; i++) {
        celestialTex[i] = LoadTextureFromEmbedded(planetData[i], planetLens[i]);
    }

	game.camera.offset = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    game.camera.target = { SCREEN_WIDTH * 10 / 2.0f, SCREEN_HEIGHT * 10 / 2.0f };

    game.camera.zoom = 1.0f;

    while (!WindowShouldClose()) {

        float dt = GetFrameTime() * game.timeScale;

        BeginDrawing();

        ClearBackground(BLACK);

		if (game.currentState == MENU) {
			game.drawStartScreen();
		} else if (game.currentState == PLAYING) {
			BeginMode2D(game.camera);
				game.drawBackground();
				game.spawnParticle(particles);
				game.spawnCelestialBody(celestialBodies);
				update(dt);
			EndMode2D();
			game.drawSideBar(particles, celestialBodies);
		}

        EndDrawing();
    }
    
    UnloadTexture(projectileTex);
    for(int i = 0; i < 8; i++) {
        UnloadTexture(celestialTex[i]);
    }
	CloseWindow();
    return 0;
}
