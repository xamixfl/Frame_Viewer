#ifndef MATERIALPRESETS_H
#define MATERIALPRESETS_H

#include "Material.h"

namespace MaterialPresets {
    enum class Type {
        Steel,
        Plastic,
        Gold,
        Glass,
        Matte
    };

    Material getPreset(int index) noexcept;

    Material getPreset(Type type) noexcept;
}

#endif 
