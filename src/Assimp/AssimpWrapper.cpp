#include "AssimpWrapper.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stdexcept>

std::vector<MeshData> AssimpWrapper::load(const std::string& filename) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
    if (!scene || !scene->mRootNode) {
        throw std::runtime_error("Ошибка загрузки модели");
    }
    std::vector<MeshData> meshes;
    processNode(scene->mRootNode, scene, meshes);
    return meshes;
}

void AssimpWrapper::processNode(void* pNode, const void* pScene, std::vector<MeshData>& meshes) {
    auto* node = static_cast<const aiNode*>(pNode);
    auto* scene = static_cast<const aiScene*>(pScene);
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        processMesh(scene->mMeshes[node->mMeshes[i]], scene, meshes);
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene, meshes);
    }
}

void AssimpWrapper::processMesh(void* pMesh, const void* pScene, std::vector<MeshData>& meshes) {
    auto* mesh = static_cast<const aiMesh*>(pMesh);
    auto* scene = static_cast<const aiScene*>(pScene);
    MeshData data;

    data.points.reserve(mesh->mNumVertices);
    for (unsigned int v = 0; v < mesh->mNumVertices; v++) {
        auto pos = mesh->mVertices[v];
        Point p(pos.x, pos.y, pos.z);
        if (mesh->HasNormals()) {
            auto normal = mesh->mNormals[v];
            p.setNormal(normal.x, normal.y, normal.z);
        } else {
            p.setNormal(0.0, 1.0, 0.0);
        }
        data.points.push_back(p);
    }

    data.faces.reserve(mesh->mNumFaces);
    for (unsigned int f = 0; f < mesh->mNumFaces; f++) {
        auto face = mesh->mFaces[f];
        Face newFace;
        for (unsigned int idx = 0; idx < face.mNumIndices; idx++) {
            newFace.push_back(face.mIndices[idx]);
        }
        data.faces.push_back(newFace);
    }

    if (mesh->mMaterialIndex < scene->mNumMaterials && scene->mMaterials) {
        auto mtl = scene->mMaterials[mesh->mMaterialIndex];
        aiColor4D diffuse(1.0f, 1.0f, 1.0f, 1.0f);
        if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse)) {
            data.material.diffuse = {diffuse.r, diffuse.g, diffuse.b};
            data.hasMaterial = true;
        }
    }
    meshes.push_back(data);
}
