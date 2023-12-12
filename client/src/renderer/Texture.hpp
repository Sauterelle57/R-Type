/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** Cursor.hpp
*/

#ifndef raylib_TEXTURE_HPP
#define raylib_TEXTURE_HPP

#include <raylib.h>
#include <iostream>
#include <memory>

#include "rlgl.h"
#include "raymath.h"

#include "ITexture.hpp"

namespace RL {

    class ZTexture : public ITexture {
        public:
            ZTexture(const std::string &fileName) {
                _texture = std::make_shared<Texture>(LoadTexture(fileName.c_str()));
            };

            ZTexture(Image image) {
                _texture = std::make_shared<Texture>(LoadTextureFromImage(image));
            };

            ZTexture(Image image, int layout) {
                _texture = std::make_shared<Texture>(LoadTextureCubemap(image, layout));
            };

            ~ZTexture() {
                UnloadTexture(*_texture);
            };

            static Texture loadCubemap(Image image, int layout) {
                return LoadTextureCubemap(image, layout);
            };

            static Texture load(std::string fileName) {
                return LoadTexture(fileName.c_str());
            };

            void setShapes(Rectangle source) {
                return SetShapesTexture(*_texture, source);
            };

            bool isReady() {
                return IsTextureReady(*_texture);
            };

            void update(const void *pixels) {
                return UpdateTexture(*_texture, pixels);
            };

            void updateRec(Rectangle rec, const void *pixels) {
                return UpdateTextureRec(*_texture, rec, pixels);
            };

            void genMipmaps() {
                return GenTextureMipmaps(_texture.get());
            };

            void setFilter(int filter) {
                return SetTextureFilter(*_texture, filter);
            };

            void setWrap(int wrap) {
                return SetTextureWrap(*_texture, wrap);
            };

            void draw(int posX, int posY, Color tint) {
                return DrawTexture(*_texture, posX, posY, tint);
            };

            void drawV(Vector2 position, Color tint) {
                return DrawTextureV(*_texture, position, tint);
            };

            void drawEx(Vector2 position, float rotation, float scale, Color tint) {
                return DrawTextureEx(*_texture, position, rotation, scale, tint);
            };

            void drawRec(Rectangle source, Vector2 position, Color tint) {
                return DrawTextureRec(*_texture, source, position, tint);
            };

            void drawPro(Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint) {
                return DrawTexturePro(*_texture, source, dest, origin, rotation, tint);
            };

            void drawNPatch(NPatchInfo nPatchInfo, Rectangle dest, Vector2 origin, float rotation, Color tint) {
                return DrawTextureNPatch(*_texture, nPatchInfo, dest, origin, rotation, tint);
            };

            std::shared_ptr<Texture> getTexture() {
                return _texture;
            }

            static TextureCubemap genCubemap(Shader shader, Texture2D panorama, int size, int format)
            {
                TextureCubemap cubemap = { 0 };

                rlDisableBackfaceCulling();     // Disable backface culling to render inside the cube
                unsigned int rbo = rlLoadTextureDepth(size, size, true);
                cubemap.id = rlLoadTextureCubemap(0, size, format);

                unsigned int fbo = rlLoadFramebuffer(size, size);
                rlFramebufferAttach(fbo, rbo, RL_ATTACHMENT_DEPTH, RL_ATTACHMENT_RENDERBUFFER, 0);
                rlFramebufferAttach(fbo, cubemap.id, RL_ATTACHMENT_COLOR_CHANNEL0, RL_ATTACHMENT_CUBEMAP_POSITIVE_X, 0);

                if (rlFramebufferComplete(fbo)) TraceLog(LOG_INFO, "FBO: [ID %i] Framebuffer object created successfully", fbo);
                rlEnableShader(shader.id);

                Matrix matFboProjection = MatrixPerspective(90.0*DEG2RAD, 1.0, RL_CULL_DISTANCE_NEAR, RL_CULL_DISTANCE_FAR);
                rlSetUniformMatrix(shader.locs[SHADER_LOC_MATRIX_PROJECTION], matFboProjection);

                Matrix fboViews[6] = {
                        MatrixLookAt((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){  1.0f,  0.0f,  0.0f }, (Vector3){ 0.0f, -1.0f,  0.0f }),
                        MatrixLookAt((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){ -1.0f,  0.0f,  0.0f }, (Vector3){ 0.0f, -1.0f,  0.0f }),
                        MatrixLookAt((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){  0.0f,  1.0f,  0.0f }, (Vector3){ 0.0f,  0.0f,  1.0f }),
                        MatrixLookAt((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){  0.0f, -1.0f,  0.0f }, (Vector3){ 0.0f,  0.0f, -1.0f }),
                        MatrixLookAt((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){  0.0f,  0.0f,  1.0f }, (Vector3){ 0.0f, -1.0f,  0.0f }),
                        MatrixLookAt((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){  0.0f,  0.0f, -1.0f }, (Vector3){ 0.0f, -1.0f,  0.0f })
                };

                rlViewport(0, 0, size, size);   // Set viewport to current fbo dimensions

                rlActiveTextureSlot(0);
                rlEnableTexture(panorama.id);

                for (int i = 0; i < 6; i++)
                {
                    rlSetUniformMatrix(shader.locs[SHADER_LOC_MATRIX_VIEW], fboViews[i]);

                    rlFramebufferAttach(fbo, cubemap.id, RL_ATTACHMENT_COLOR_CHANNEL0, RL_ATTACHMENT_CUBEMAP_POSITIVE_X + i, 0);
                    rlEnableFramebuffer(fbo);

                    rlClearScreenBuffers();
                    rlLoadDrawCube();
                }
                rlDisableShader();          // Unbind shader
                rlDisableTexture();         // Unbind texture
                rlDisableFramebuffer();     // Unbind framebuffer
                rlUnloadFramebuffer(fbo);   // Unload framebuffer (and automatically attached depth texture/renderbuffer)

                rlViewport(0, 0, rlGetFramebufferWidth(), rlGetFramebufferHeight());
                rlEnableBackfaceCulling();
                //------------------------------------------------------------------------------------------

                cubemap.width = size;
                cubemap.height = size;
                cubemap.mipmaps = 1;
                cubemap.format = format;

                return cubemap;
            }

            std::shared_ptr<Texture> _texture;
    };
} // RL

#endif //raylib_TEXTURE_HPP