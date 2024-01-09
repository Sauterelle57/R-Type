/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Collisions.cpp
*/

#include "Collisions.hpp"

namespace tls {

    BoundingBox calculateBoundingBoxForAllMeshes(const aiScene *scene) {
        if (!scene || scene->mNumMeshes == 0) {
            return {};
        }

        BoundingBox bbox;
        bbox.min = bbox.max = {scene->mMeshes[0]->mVertices[0].x, scene->mMeshes[0]->mVertices[0].y, scene->mMeshes[0]->mVertices[0].z};

        for (unsigned int m = 0; m < scene->mNumMeshes; ++m) {
            const aiMesh* mesh = scene->mMeshes[m];
            for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
                auto vertex = tls::Vec3{mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z};
                bbox.min._x = std::min(bbox.min._x, vertex._x);
                bbox.min._y = std::min(bbox.min._y, vertex._y);
                bbox.min._z = std::min(bbox.min._z, vertex._z);
                bbox.max._x = std::max(bbox.max._x, vertex._x);
                bbox.max._y = std::max(bbox.max._y, vertex._y);
                bbox.max._z = std::max(bbox.max._z, vertex._z);
            }
        }

        return bbox;
    }

    BoundingBox loadModelAndGetBoundingBox(const std::string& path) {
        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cerr << "Error loading model: " << importer.GetErrorString() << std::endl;
            return {};
        }

        return calculateBoundingBoxForAllMeshes(scene);
    }
}
