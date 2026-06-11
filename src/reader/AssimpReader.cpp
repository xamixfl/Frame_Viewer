#include <stdexcept>
#include "reader/AssimpReader.h"
#include "data/Point.h"
#include "data/Face.h"

void AssimpReader::readModel(const std::string& filename, AssimpModelBuilder& builder) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
    if (!scene || !scene->mRootNode) throw std::runtime_error("Ошибка загрузки");

    processNode(*(scene->mRootNode), *scene, builder);
}

void AssimpReader::processNode(aiNode& node, const aiScene& scene, AssimpModelBuilder& builder) {
    for (unsigned int i = 0; i < node.mNumMeshes; i++) {
        // scene.mMeshes - это массив указателей (aiMesh**), потому что библиотека на Си, поэтому берется элемент и разыменовывается
        processMesh(*(scene.mMeshes[node.mMeshes[i]]), scene, builder);
    }
    for (unsigned int i = 0; i < node.mNumChildren; i++) {
        processNode(*(node.mChildren[i]), scene, builder);
    }
}

void AssimpReader::processMesh(aiMesh& mesh, const aiScene& scene, AssimpModelBuilder& builder) {
    for (unsigned int v = 0; v < mesh.mNumVertices; v++) {
        aiVector3D pos = mesh.mVertices[v];

        Point p(pos.x, pos.y, pos.z);
        if (mesh.HasNormals()) {
            aiVector3D normal = mesh.mNormals[v];
            p.setNormal(normal.x, normal.y, normal.z);
        } else {
            p.setNormal(0.0, 1.0, 0.0);
        }
        
        builder.addPoint(p);
    }
    for (unsigned int f = 0; f < mesh.mNumFaces; f++) {
        aiFace face = mesh.mFaces[f];
        Face newFace;
        for (unsigned int idx = 0; idx < face.mNumIndices; idx++) newFace.push_back(face.mIndices[idx]);
        builder.addFace(newFace);
    }
    
    aiMaterial* mtl = scene.mMaterials[mesh.mMaterialIndex];
    aiColor4D diffuse(1.0f, 1.0f, 1.0f, 1.0f);
    if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse)) {
        Material mat;
        mat.diffuse = {diffuse.r, diffuse.g, diffuse.b};
        builder.setMaterial(mat);
    }
}
