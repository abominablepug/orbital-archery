#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H

#include "raylib.h"

class CelestialBody {
private:
	float radius;
	Vector2 position;

public:
	CelestialBody(Vector2 position, float radius);

	Vector2 resultantAcceleration(Vector2& otherPosition);

	void draw();

};

#endif
