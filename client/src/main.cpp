#include "raylib.h"

#define MAX_PARTICLES 10000

typedef struct Particle {
    Vector3 position;
    Vector3 speed;
    float alpha;
    bool active;
} Particle;

Particle particles[MAX_PARTICLES];
Texture2D particleTexture;
Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

void InitParticle(int index, Vector3 position) {
    particles[index].position = position;
    particles[index].speed = (Vector3){ GetRandomValue(-10, 10)/300.0f, GetRandomValue(100, 200)/2000.0f, GetRandomValue(-10, 10)/300.0f };
    particles[index].alpha = 1.0f;
    particles[index].active = true;
}


void UpdateParticles() {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (particles[i].active) {
            particles[i].position.x += particles[i].speed.x;
            particles[i].position.y += particles[i].speed.y;
            particles[i].position.z += particles[i].speed.z;
            particles[i].alpha -= 0.02f;

            if (particles[i].alpha <= 0.0f) particles[i].active = false;
        }
    }
}

void EmitParticlesFromCube() {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (!particles[i].active) {
            Vector3 emitPosition = (Vector3){ GetRandomValue(-10, 10)/30.0f , cubePosition.y + 1.0f, GetRandomValue(-10, 10)/30.0f };
            InitParticle(i, emitPosition);
            break;
        }
    }
}


void DrawParticles(Camera3D camera, Shader shader) {
    BeginShaderMode(shader);
    BeginBlendMode(BLEND_ADDITIVE);
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (particles[i].active) {
            DrawBillboard(camera, particleTexture, particles[i].position, 0.1f, Fade(WHITE, particles[i].alpha));
        }
    }
    EndBlendMode();
    EndShaderMode();
}


int main(void) {
    InitWindow(1920, 1080, "rtype");

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    particleTexture = LoadTexture("./client/resources/particle.png");

    Shader shader = LoadShader("./client/resources/shaders/particle.vs", "./client/resources/shaders/particle.fs");
    int glowIntensityLoc = GetShaderLocation(shader, "glowIntensity");
    float glowIntensity = 3.0f;
    SetShaderValue(shader, glowIntensityLoc, &glowIntensity, SHADER_UNIFORM_FLOAT);

    SetTargetFPS(60);

    DisableCursor();
    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_FIRST_PERSON);
        if (IsKeyDown(KEY_SPACE)) camera.position.y += 0.05f;
        if (IsKeyDown(KEY_LEFT_SHIFT)) camera.position.y -= 0.05f;
        UpdateParticles();
        EmitParticlesFromCube();
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode3D(camera);
        DrawGrid(10, 1.0f);
        DrawCylinder(cubePosition, 0.4f, 0.4f, 1.0f, 50, {200, 200, 200, 255});
        DrawParticles(camera, shader);
        EndMode3D();
        EndDrawing();
    }
    UnloadTexture(particleTexture);
    CloseWindow();

    return 0;
}
