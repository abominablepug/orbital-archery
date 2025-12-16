#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H

#include "raylib.h"

extern Texture2D celestialTex[8];

class CelestialBody {
private:
	float radius;
	Vector2 position;
	int texIndex;

public:
	CelestialBody(Vector2 position, float radius, int texIndex);

	Vector2 resultantAcceleration(Vector2& otherPosition);

	void draw();

	Vector2 getPosition() { return position; }

	float getRadius() { return radius; }

};

#endif
