/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** Camera.hpp
*/

#ifndef raylib_CAMERA_HPP
#define raylib_CAMERA_HPP

#include <raylib.h>
#include "ICamera.hpp"

namespace RL {

    class ZCamera : public ICamera {
        public:
            ZCamera() {
                _camera = std::make_unique<Camera>();
            };

            ~ZCamera() = default;

            Ray getMouseRay(Vector2 mousePosition) {
                return GetMouseRay(mousePosition, *_camera);
            };

            Matrix getMatrix() {
                return GetCameraMatrix(*_camera);
            };

            void update(int mode) {
                return UpdateCamera(_camera.get(), mode);
            };

            void updatePro(Vector3 movement, Vector3 rotation, float zoom) {
                return UpdateCameraPro(_camera.get(), movement, rotation, zoom);
            };

            void beginMode() {
                return BeginMode3D(*_camera);
            };

            void endMode() {
                return EndMode3D();
            };

            void drawBillboard(Texture2D texture, Vector3 position, float size, Color tint) {
                return DrawBillboard(*_camera, texture, position, size, tint);
            };

            void drawBillboardRec(Texture2D texture, Rectangle source, Vector3 position, Vector2 size, Color tint) {
                return DrawBillboardRec(*_camera, texture, source, position, size, tint);
            };

            void drawBillboardPro(Texture2D texture, Rectangle source, Vector3 position, Vector3 up, Vector2 size, Vector2 origin, float rotation, Color tint) {
                return DrawBillboardPro(*_camera, texture, source, position, up, size, origin, rotation, tint);
            };

            tls::Vec3 getPosition() {
                return {_camera->position.x, _camera->position.y, _camera->position.z};
            };

            void setPosition(Vector3 position) {
                _camera->position = position;
            };


            Vector3 getTarget() {
                return _camera->target;
            };

            void setTarget(Vector3 target) {
                _camera->target = target;
            };


            Vector3 getUp() {
                return _camera->up;
            };

            void setUp(Vector3 up) {
                _camera->up = up;
            };


            float getFovy() {
                return _camera->fovy;
            };

            void setFovy(float fovy) {
                _camera->fovy = fovy;
            };


            int getProjection() {
                return _camera->projection;
            };

            void setProjection(int projection) {
                _camera->projection = projection;
            };

            std::unique_ptr<Camera> _camera;
    };

} // RL

#endif //raylib_CAMERA_HPP
