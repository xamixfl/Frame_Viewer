#ifndef MATERIALPRESETS_H
#define MATERIALPRESETS_H

#include "Material.h"

namespace MaterialPresets {
    // Перечисление доступных пресетов для удобства
    enum class Type {
        Steel,
        Plastic,
        Gold,
        Glass,
        Matte
    };

    // Получение материала по индексу из комбо-бокса
    Material getPreset(int index) noexcept;
    
    // Получение материала по перечислению
    Material getPreset(Type type) noexcept;
}

#endif // MATERIALPRESETS_H
