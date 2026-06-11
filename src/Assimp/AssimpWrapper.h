#ifndef ASSIMP_WRAPPER_H
#define ASSIMP_WRAPPER_H

#include <string>
#include <vector>
#include "data/Point.h"
#include "data/Face.h"
#include "data/Material.h"

struct MeshData {
    std::vector<Point> points;
    std::vector<Face> faces;
    Material material;
    bool hasMaterial = false;
};

class AssimpWrapper {
public:
    std::vector<MeshData> load(const std::string& filename);
private:
    void processNode(void* node, const void* scene, std::vector<MeshData>& meshes);
    void processMesh(void* mesh, const void* scene, std::vector<MeshData>& meshes);
};

#endif
