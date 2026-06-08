#ifndef MATERIAL_H
#define MATERIAL_H
#include <array>

struct Material {
    std::array<float, 3> ambient = {0.1f, 0.1f, 0.1f};
    std::array<float, 3> diffuse = {0.8f, 0.8f, 0.8f};
    std::array<float, 3> specular = {1.0f, 1.0f, 1.0f};
    float shininess = 32.0f;
    
    Material() = default;
};

#endif // MATERIAL_H
