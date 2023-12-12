
#include "raylib.h"
#include "renderer/Window.hpp"
#include "renderer/ICamera.hpp"
#include "renderer/Camera.hpp"
#include "renderer/renderer.hpp"

#include "raymath.h"

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"
#include <memory>

int main(void)
{
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    ZappyGui::Utils::setConfigFlags(FLAG_MSAA_4X_HINT);
    std::shared_ptr<ZappyGui::IWindow> window = std::make_shared<ZappyGui::ZWindow>(screenWidth, screenHeight, "R TYPE test light");

    std::shared_ptr<ZappyGui::ICamera> camera = std::make_shared<ZappyGui::ZCamera>();
    camera->setPosition((Vector3){ 25.0f, 10.0f, 6.0f });
    camera->setTarget((Vector3){ 0.0f, 8.0f, 0.0f });
    camera->setUp((Vector3){ 0.0f, 1.0f, 0.0f });
    camera->setFovy(45.0f);
    camera->setProjection(CAMERA_PERSPECTIVE);

    std::shared_ptr<ZappyGui::ZMesh> planMesh = std::make_shared<ZappyGui::ZMesh>();
    planMesh->genPlane(10.0f, 10.0f, 3, 3);
    planMesh->setCanUnload(false);
    std::shared_ptr<ZappyGui::ZMesh> cubeMesh = std::make_shared<ZappyGui::ZMesh>();
    cubeMesh->genCube(2.0f, 2.0f, 2.0f);
    cubeMesh->setCanUnload(false);
    std::shared_ptr<ZappyGui::ZModel> planModel = std::make_shared<ZappyGui::ZModel>(planMesh->getMesh());
    std::shared_ptr<ZappyGui::ZModel> cubeModel = std::make_shared<ZappyGui::ZModel>(cubeMesh->getMesh());
    std::shared_ptr<ZappyGui::ZShader> shader = std::make_shared<ZappyGui::ZShader>("./client/resources/shaders/lighting.vs", "./client/resources/shaders/lighting.fs");

    shader->getShader()->locs[SHADER_LOC_VECTOR_VIEW] = shader->getLocation("viewPos");

    int ambientLoc = shader->getLocation("ambient");
    float test[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
    shader->setValue(ambientLoc, test, SHADER_UNIFORM_VEC4);

    planModel->getModel()->materials[0].shader = *shader->getShader();
    cubeModel->getModel()->materials[0].shader = *shader->getShader();

    Light lights[MAX_LIGHTS] = { 0 };
    lights[0] = CreateLight(LIGHT_POINT, (Vector3){ -2, 1, -2 }, Vector3Zero(), YELLOW, *shader->getShader());
    lights[1] = CreateLight(LIGHT_POINT, (Vector3){ 2, 1, 2 }, Vector3Zero(), RED, *shader->getShader());
    lights[2] = CreateLight(LIGHT_POINT, (Vector3){ -2, 1, 2 }, Vector3Zero(), GREEN, *shader->getShader());
    lights[3] = CreateLight(LIGHT_POINT, (Vector3){ 2, 1, -2 }, Vector3Zero(), BLUE, *shader->getShader());

    SetTargetFPS(60);

    Vector3 cubePos = { 0.0f, 20.0f, 0.0f };

    std::shared_ptr<ZappyGui::ICursor> cursor = std::make_shared<ZappyGui::ZCursor>();
    cursor->disable();

    while (!WindowShouldClose())
    {
        camera->update(CAMERA_FIRST_PERSON);

        float cameraPos[3] = { camera->getPosition().x, camera->getPosition().y, camera->getPosition().z };
        SetShaderValue(*shader->getShader(), shader->getShader()->locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);

        if (IsKeyPressed(KEY_Y)) { lights[0].enabled = !lights[0].enabled; }
        if (IsKeyPressed(KEY_R)) { lights[1].enabled = !lights[1].enabled; }
        if (IsKeyPressed(KEY_G)) { lights[2].enabled = !lights[2].enabled; }
        if (IsKeyPressed(KEY_B)) { lights[3].enabled = !lights[3].enabled; }

        for (int i = 0; i < MAX_LIGHTS; i++) UpdateLightValues(*shader->getShader(), lights[i]);
        window->beginDrawing();
        window->clearBackground(RAYWHITE);
        camera->beginMode();

        planModel->draw(Vector3Zero(), 1.0f, WHITE);
        cubeModel->draw(cubePos, 1.0f, WHITE);

        for (int i = 0; i < MAX_LIGHTS; i++) {
            if (lights[i].enabled) DrawSphereEx(lights[i].position, 0.2f, 8, 8, lights[i].color);
            else DrawSphereWires(lights[i].position, 0.2f, 8, 8, ColorAlpha(lights[i].color, 0.3f));
        }

        window->drawGrid(10, 1.0f);
        camera->endMode();
        window->drawFPS(10, 10);
        window->drawText("Use keys [Y][R][G][B] to toggle lights", 10, 40, 20, DARKGRAY);
        window->endDrawing();
        if (cubePos.y > 0.0f) cubePos.y -= 0.1f;
        else cubePos.y = 20.0f;
    }
    return 0;
}