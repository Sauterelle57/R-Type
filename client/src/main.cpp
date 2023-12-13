#include "raylib.h"
#include "renderer/Window.hpp"
#include "renderer/ICamera.hpp"
#include "renderer/Camera.hpp"
#include "renderer/renderer.hpp"
#include "Coordinator.hpp"

#include "raymath.h"
#include <cstdlib>
#include <random>

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"
#include "Move.hpp"
#include "DrawModel.hpp"
#include <memory>

int main(void)
{
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    RL::Utils::setConfigFlags(FLAG_MSAA_4X_HINT);
    std::shared_ptr<RL::IWindow> window = std::make_shared<RL::ZWindow>(screenWidth, screenHeight, "R TYPE test light");

    std::shared_ptr<RL::ICamera> camera = std::make_shared<RL::ZCamera>();
    camera->setPosition((Vector3){ 25.0f, 20.0f, 6.0f });
    camera->setTarget((Vector3){ 0.0f, 8.0f, 0.0f });
    camera->setUp((Vector3){ 0.0f, 1.0f, 0.0f });
    camera->setFovy(45.0f);
    camera->setProjection(CAMERA_PERSPECTIVE);

    std::shared_ptr<RL::ZMesh> planMesh = std::make_shared<RL::ZMesh>();
    planMesh->genPlane(10.0f, 10.0f, 3, 3);
    planMesh->setCanUnload(false);
    std::shared_ptr<RL::ZMesh> cubeMesh = std::make_shared<RL::ZMesh>();
    cubeMesh->genCube(2.0f, 2.0f, 2.0f);
    cubeMesh->setCanUnload(false);
    std::shared_ptr<RL::ZModel> planModel = std::make_shared<RL::ZModel>(planMesh->getMesh());
    std::shared_ptr<RL::ZModel> cubeModel = std::make_shared<RL::ZModel>(cubeMesh->getMesh());
    std::shared_ptr<RL::ZShader> shader = std::make_shared<RL::ZShader>("./client/resources/shaders/lighting.vs", "./client/resources/shaders/lighting.fs");

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

    std::shared_ptr<RL::ICursor> cursor = std::make_shared<RL::ZCursor>();
    cursor->disable();

    std::shared_ptr<ECS::Coordinator> coordinator = std::make_shared<ECS::Coordinator>();
    coordinator->init();

    coordinator->registerComponent<ECS::Transform>();
    coordinator->registerComponent<ECS::Model>();

    auto cubeSystemTest = coordinator->registerSystem<ECS::Move>();
    auto playerSystemTest = coordinator->registerSystem<ECS::DrawModel>();

    ECS::Signature signature;
    signature.set(coordinator->getComponentType<ECS::Transform>());
    coordinator->setSystemSignature<ECS::Move>(signature);

    ECS::Signature signature2;
    signature2.set(coordinator->getComponentType<ECS::Transform>());
    signature2.set(coordinator->getComponentType<ECS::DrawModel>());
    coordinator->setSystemSignature<ECS::DrawModel>(signature2);

    std::vector<Entity> entities(ECS::MAX_ENTITIES);

    std::default_random_engine generator;
    std::uniform_real_distribution<float> randPosition((ECS::MAX_ENTITIES / 10.0) * -1.0, (ECS::MAX_ENTITIES / 10.0) * 1.0);

    std::shared_ptr<RL::IEvent> event = std::make_shared<RL::ZEvent>();
    event->setExitKey(KEY_F4);

//    for (auto& entity : entities) {
        entities[0] = coordinator->createEntity();
        coordinator->addComponent(
            entities[0],
            ECS::Transform{
                .position = {100, 0, 100},
                .rotation = {0, 0, 0, 0},
                .scale = {0, 0, 0}
            }
        );
//    }

    entities[1] = coordinator->createEntity();
    coordinator->addComponent(
            entities[1],
            ECS::Transform{
                    .position = {0, 0, 0},
                    .rotation = {0, 0, 0, 0},
                    .scale = {0, 0, 0}
            }
    );
    coordinator->addComponent(
            entities[1],
            ECS::Model{
                .model = std::make_shared<RL::ZModel>("./client/resources/models/ship.glb")
            }
    );

    while (!window->shouldClose()) {
        if (cursor->isHidden())
            camera->update(CAMERA_CUSTOM);

        float cameraPos[3] = { camera->getPosition().x, camera->getPosition().y, camera->getPosition().z };
        SetShaderValue(*shader->getShader(), shader->getShader()->locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);

        if (IsKeyPressed(KEY_Y)) { lights[0].enabled = !lights[0].enabled; }
        if (IsKeyPressed(KEY_R)) { lights[1].enabled = !lights[1].enabled; }
        if (IsKeyPressed(KEY_G)) { lights[2].enabled = !lights[2].enabled; }
        if (IsKeyPressed(KEY_B)) { lights[3].enabled = !lights[3].enabled; }
        if (IsKeyPressed(KEY_ESCAPE)) { cursor->isHidden() ? cursor->enable() : cursor->disable(); }
        if (IsKeyDown(KEY_LEFT_SHIFT)) { camera->setPosition((Vector3) { camera->getPosition().x, static_cast<float>(camera->getPosition().y - 1), camera->getPosition().z }); }
        if (IsKeyDown(KEY_SPACE)) { camera->setPosition((Vector3) { camera->getPosition().x, static_cast<float>(camera->getPosition().y + 1), camera->getPosition().z }); }

        for (int i = 0; i < MAX_LIGHTS; i++) UpdateLightValues(*shader->getShader(), lights[i]);
        window->beginDrawing();
        window->clearBackground(RAYWHITE);
        camera->beginMode();

        planModel->draw(Vector3Zero(), 1.0f, WHITE);

        int32_t entityCount = coordinator->getLivingEntityCount();
        int32_t count = 0;
//        for (auto& entity : entities) {
//            if (count++ >= entityCount)
//                break;
//            cubeModel->draw(coordinator->getComponent<ECS::Transform>(entity).position, 1.0f, WHITE);
//        }

        playerSystemTest->update();


        for (auto & light : lights) {
            if (light.enabled) DrawSphereEx(light.position, 0.2f, 8, 8, light.color);
            else DrawSphereWires(light.position, 0.2f, 8, 8, ColorAlpha(light.color, 0.3f));
        }

        window->drawGrid(10, 1.0f);
        camera->endMode();
        window->drawFPS(10, 10);
        window->drawText("Use keys [Y][R][G][B] to toggle lights", 10, 40, 20, DARKGRAY);
        window->endDrawing();
        cubeSystemTest->update();

    }
    return 0;
}
