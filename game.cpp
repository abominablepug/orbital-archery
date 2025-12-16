#include "game.h"
#include "particle.h"
#include "celestialBody.h"
#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <cmath>
#include <string>

const float mult = 2.0f;

void Game::initBackground() {
    int numStars = 50000;
    for (int i = 0; i < numStars; i++) {
        Star s;
        s.position = { (float)GetRandomValue(-20000, 20000), (float)GetRandomValue(-20000, 20000) };

        s.size = GetRandomValue(1, 3);

        int brightness = GetRandomValue(100, 255);
        s.color = { (unsigned char)brightness, (unsigned char)brightness, (unsigned char)(brightness + GetRandomValue(0, 20)), 255 };

        stars.push_back(s);
    }
}

Game::Game(Vector2 dragStartPos) {
	this->dragStartPos = dragStartPos;
	this->currentState = MENU;

	// Initialize camera
	camera = { 0 };
	camera.target = { 0, 0 };
	camera.offset = { 0, 0 };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

	// Default settings
	isSideBarOpen = false;
	sideBarRect = { 0, 0, 250, (float)GetScreenHeight() };
	sideBarToggleRect = { 10, 10, 30, 30 };

	enableWallCollision = false;
	particleMass = 50.0f;
	zoomLevel = 1.0f;
	timeScale = 1.0f;
	isDebug = false;

	initBackground();
}

Vector2 Game::getWorldMousePosition() {
	return GetScreenToWorld2D(GetMousePosition(), camera);
}

void Game::spawnParticle(std::vector<Particle>& particles) {
	if (isSideBarOpen && CheckCollisionPointRec(GetMousePosition(), sideBarRect)) return;

	Vector2 currentPos = getWorldMousePosition();
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		dragStartPos = currentPos;
	}
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
		float angle = atan2f(dragStartPos.y - currentPos.y, dragStartPos.x - currentPos.x);
		float arrowSize = 20.0f;
		float arrowAngle = 30.0f * DEG2RAD;

		float triangleHeight = arrowSize * cosf(arrowAngle);
		Vector2 shaftEnd = {
			dragStartPos.x - triangleHeight * cosf(angle),
			dragStartPos.y - triangleHeight * sinf(angle)
		};

		Vector2 rightWing = {
			dragStartPos.x - arrowSize * cosf(angle - arrowAngle),
			dragStartPos.y - arrowSize * sinf(angle - arrowAngle)
		};
		Vector2 leftWing = {
			dragStartPos.x - arrowSize * cosf(angle + arrowAngle),
			dragStartPos.y - arrowSize * sinf(angle + arrowAngle)
		};

		if (currentPos.x != dragStartPos.x || currentPos.y != dragStartPos.y) {
			DrawLineEx(shaftEnd, currentPos, 10.0f, RED);
			DrawTriangle(dragStartPos, leftWing, rightWing, RED);
		}
	}
	if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
		Vector2 velocity = { (dragStartPos.x - currentPos.x) * mult, (dragStartPos.y - currentPos.y) * mult };
		Color color = BLUE;
		int radius = (int)(sqrt(particleMass));
		if (radius < 2) radius = 2;

		Particle newParticle(currentPos, velocity, color, radius);
		particles.push_back(newParticle);
	}
}

void Game::spawnCelestialBody(std::vector<CelestialBody>& celestialBodies) {
	if (isSideBarOpen && CheckCollisionPointRec(GetMousePosition(), sideBarRect)) return;

	Vector2 currentPos = getWorldMousePosition();
	if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
		dragStartPos = currentPos;
	}
	if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
		float radius = Vector2Distance(dragStartPos, currentPos);
		DrawCircleV(dragStartPos, radius, GREEN);
	}
	if (IsMouseButtonReleased(MOUSE_RIGHT_BUTTON)) {
		float radius = Vector2Distance(dragStartPos, currentPos);
		CelestialBody newBody(dragStartPos, radius, GetRandomValue(0, 7));
		celestialBodies.push_back(newBody);
	}
}

void Game::drawBackground() {
	for (const auto& star : stars) {
		float margin = 100.0f / camera.zoom;

		Vector2 screenPos = GetWorldToScreen2D(star.position, camera);
        if (screenPos.x > -margin && screenPos.x < GetScreenWidth() + margin &&
            screenPos.y > -margin && screenPos.y < GetScreenHeight() + margin) {
             DrawRectangleV(star.position, {(float)star.size, (float)star.size}, star.color);
        }
	}
}

void Game::drawStartScreen() {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int centerX = screenWidth / 2;
    int centerY = screenHeight / 2;

    DrawRectangle(0, 0, screenWidth, screenHeight, BLACK);
    
    const char* title = "Orbital Archery";
    const char* subtitle = "An out of this world projectile motion simulation";
    const char* credits = "Made By: Abominablepug";
    
    const char* instruction1 = "Left Click and Drag: Shoot Particle";
    const char* instruction2 = "Right Click and Drag: Create Celestial Body";
    const char* instruction3 = "Scroll Wheel: Zoom In/Out";
    const char* instruction4 = "Spacebar: Toggle Side Bar";
    
    const char* cta = "Click anywhere to Start";

    int titleFontSize = 80;
    int subFontSize = 30;
    int instructionFontSize = 20; // Reduced slightly for cleaner list look
    int ctaFontSize = 20;

    int titleWidth = MeasureText(title, titleFontSize);
    int subWidth = MeasureText(subtitle, subFontSize);
	int credWidth = MeasureText(credits, subFontSize);
    
    int instruction1Width = MeasureText(instruction1, instructionFontSize);
    int instruction2Width = MeasureText(instruction2, instructionFontSize);
    int instruction3Width = MeasureText(instruction3, instructionFontSize);
    int instruction4Width = MeasureText(instruction4, instructionFontSize);
    
    int ctaWidth = MeasureText(cta, ctaFontSize);

    DrawText(title, centerX - titleWidth/2, centerY - 250, titleFontSize, PURPLE);
    DrawText(subtitle, centerX - subWidth/2, centerY - 160, subFontSize, WHITE);
    DrawText(credits, centerX - credWidth/2, centerY - 120, subFontSize, WHITE);

    DrawText(instruction1, (screenWidth - instruction1Width) / 2, centerY - 40, instructionFontSize, LIGHTGRAY);
    DrawText(instruction2, (screenWidth - instruction2Width) / 2, centerY, instructionFontSize, LIGHTGRAY);
    DrawText(instruction3, (screenWidth - instruction3Width) / 2, centerY + 40, instructionFontSize, LIGHTGRAY);
    DrawText(instruction4, (screenWidth - instruction4Width) / 2, centerY + 80, instructionFontSize, LIGHTGRAY);
    
    if ((int)(GetTime() * 2) % 2 == 0) {
        DrawText(cta, centerX - ctaWidth/2, centerY + 170, ctaFontSize, GRAY);
    }

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        currentState = PLAYING;
    }
}

float GuiSlider(Rectangle bounds, const char* text, float value, float min, float max) {
	DrawText(text, bounds.x, bounds.y - 20, 20, WHITE);
    DrawRectangleRec(bounds, DARKGRAY);
    
    float ratio = (value - min) / (max - min);
    float knobPos = bounds.x + (ratio * bounds.width);
    
    DrawRectangle(bounds.x, bounds.y, (int)(ratio * bounds.width), bounds.height, PURPLE);
    DrawCircle((int)knobPos, (int)(bounds.y + bounds.height/2), 10, RAYWHITE);

    Vector2 mouse = GetMousePosition();
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(mouse, {bounds.x - 10, bounds.y - 10, bounds.width + 20, bounds.height + 20})) {
            float newRatio = (mouse.x - bounds.x) / bounds.width;
            if (newRatio < 0) newRatio = 0;
            if (newRatio > 1) newRatio = 1;
            return min + newRatio * (max - min);
        }
    }
    return value;
}

void Game::drawSideBar(std::vector<Particle>& particles, std::vector<CelestialBody>& celestialBodies) {
    if (!isSideBarOpen) {
        DrawRectangleRec(sideBarToggleRect, DARKGRAY);
        DrawText(">", sideBarToggleRect.x + 8, sideBarToggleRect.y + 5, 20, WHITE);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), sideBarToggleRect)) {
            isSideBarOpen = true;
        }
        return;
    }

    sideBarRect.height = (float)GetScreenHeight();
    DrawRectangleRec(sideBarRect, Fade(BLACK, 0.9f));
    DrawRectangleLinesEx(sideBarRect, 2, PURPLE);

    Rectangle closeBtn = { sideBarRect.width - 40, 10, 30, 30 };
    DrawText("X", closeBtn.x + 8, closeBtn.y + 5, 20, RED);
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), closeBtn)) {
        isSideBarOpen = false;
    }

    float startX = 20;
    float startY = 60;
    float gap = 70;

    // 1. Clear Screen Button
    Rectangle clearBtn = { startX, startY, 210, 40 };
    DrawRectangleRec(clearBtn, RED);
    DrawText("CLEAR ALL", clearBtn.x + 55, clearBtn.y + 10, 20, WHITE);
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), clearBtn)) {
        particles.clear();
        celestialBodies.clear();
    }
    
    startY += gap;

    // 2. Toggle Boundaries
    Rectangle boundBtn = { startX, startY, 210, 40 };
    DrawRectangleRec(boundBtn, enableWallCollision? DARKGREEN : DARKGRAY);
    DrawText(enableWallCollision ? "WALLS: ON" : "WALLS: OFF", boundBtn.x + 50, boundBtn.y + 10, 20, WHITE);
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), boundBtn)) {
        enableWallCollision = !enableWallCollision;
    }

    startY += gap;

    // 3. Toggle Boundaries
    Rectangle debugBtn = { startX, startY, 210, 40 };
    DrawRectangleRec(debugBtn, isDebug? DARKGREEN : DARKGRAY);
    DrawText(isDebug ? "DEBUG: ON" : "DEBUG: OFF", debugBtn.x + 50, debugBtn.y + 10, 20, WHITE);
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), debugBtn)) {
        isDebug = !isDebug;
    }

    startY += gap;

    // 4. Zoom Slider/Dial
    char zoomText[32];
    sprintf(zoomText, "Camera Zoom: %.2fx", zoomLevel);
    zoomLevel = GuiSlider({startX, startY + 20, 210, 10}, zoomText, zoomLevel, 0.1f, 3.0f);
    camera.zoom = zoomLevel;

    startY += gap;

    // 5. Mass Slider
    char massText[32];
    sprintf(massText, "Proj. Mass: %.0fkg", particleMass);
    particleMass = GuiSlider({startX, startY + 20, 210, 10}, massText, particleMass, 1.0f, 2000.0f);

    startY += gap;

    // 6. Time Scale
    char timeText[32];
    sprintf(timeText, "Time Speed: %.2fx", timeScale);
    timeScale = GuiSlider({startX, startY + 20, 210, 10}, timeText, timeScale, 0.0f, 5.0f);
}
