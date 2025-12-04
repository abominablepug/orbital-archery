#include <raylib.h>

class Particle {
    private:
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    int radius;
    Color color;

    public:
    Particle(Vector2 pos, Vector2 vel, Color col, Vector2 acc = {0, 9.81f}, int rad = 5) {
        position = pos;
        velocity = vel;
        color = col;
        acceleration = acc;
        radius = rad;
    }

    void update(float dt) {
        position.x += velocity.x * dt;
        position.y += velocity.y * dt;
        velocity.x += acceleration.x * dt;
        velocity.y += acceleration.y * dt;
    }

    void draw() {
        DrawCircle(position.x, position.y, radius, color);
    }
};

int main() {
    
    const int SCREEN_WIDTH = 1920;
    const int SCREEN_HEIGHT = 1080;
    const int TARGET_FPS = 180;

    Particle particle1 = Particle({0, SCREEN_HEIGHT/2}, {100, -100}, BLUE);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Projectile Motion Simulation");
    SetTargetFPS(TARGET_FPS);

    while (!WindowShouldClose()) {

        float dt = GetFrameTime();

        BeginDrawing();

        ClearBackground(BLACK);
        particle1.update(dt);
        particle1.draw();

        EndDrawing();
    }
    
    return 0;
}
