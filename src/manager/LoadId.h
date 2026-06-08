#ifndef LOADID_H
#define LOADID_H

#include <cstddef>

enum class LoadId : std::size_t {
    Model = 1,
    Camera = 2,
    Scene = 3,
    ModelMatrix = 4, 
    AssimpModel = 5,
};

#endif // LOADID_H
