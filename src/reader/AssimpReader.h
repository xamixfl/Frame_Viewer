#ifndef ASSIMP_READER_H
#define ASSIMP_READER_H

#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "builder/AssimpModelBuilder.h"

class AssimpReader {
public:
    // Ридер отвечает за парсинг и наполнение билдера
    void read(const std::string& filename, AssimpModelBuilder& builder);

private:
    void processNode(aiNode* node, const aiScene* scene, AssimpModelBuilder& builder);
    void processMesh(aiMesh* mesh, const aiScene* scene, AssimpModelBuilder& builder);
};

#endif
