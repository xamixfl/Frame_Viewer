#include "MaterialPresets.h"

namespace MaterialPresets {

    Material getPreset(int index) noexcept {
        switch (index) {
            case 0: return getPreset(Type::Steel);
            case 1: return getPreset(Type::Plastic);
            case 2: return getPreset(Type::Gold);
            case 3: return getPreset(Type::Glass);
            default: return getPreset(Type::Matte);
        }
    }

    Material getPreset(Type type) noexcept {
        Material mat;
        switch (type) {
            case Type::Steel:
                mat.ambient = {0.15f, 0.15f, 0.15f};
                mat.diffuse = {0.55f, 0.55f, 0.55f};
                mat.specular = {0.8f, 0.8f, 0.8f};
                mat.shininess = 45.0f;
                mat.alpha = 1.0f;
                break;
            case Type::Plastic:
                mat.ambient = {0.2f, 0.2f, 0.2f};
                mat.diffuse = {0.7f, 0.7f, 0.7f};
                mat.specular = {0.2f, 0.2f, 0.2f};
                mat.shininess = 8.0f; // Широкий, мягкий (пластиковый) блик
                mat.alpha = 1.0f;
                break;
            case Type::Gold: // Максимально выраженный металл с резким зеркальным блеском
                mat.ambient = {0.25f, 0.20f, 0.08f};
                mat.diffuse = {0.75f, 0.60f, 0.23f};
                mat.specular = {1.0f, 0.9f, 0.7f}; // ОЧЕНЬ высокий уровень зеркальности
                mat.shininess = 128.0f; // Очень узкий, сфокусированный и яркий блик
                mat.alpha = 1.0f;
                break;
            case Type::Glass: // Прозрачный/стеклянный материал
                mat.ambient = {0.1f, 0.2f, 0.3f};
                mat.diffuse = {0.1f, 0.2f, 0.3f}; 
                mat.specular = {0.95f, 0.95f, 0.95f};
                mat.shininess = 128.0f;
                mat.alpha = 0.3f; // Сильная прозрачность (30% видимости)
                break;
            case Type::Matte:
            default: // Полностью матовая поверхность (никаких бликов и отражений)
                mat.ambient = {0.1f, 0.1f, 0.1f};
                mat.diffuse = {0.9f, 0.9f, 0.9f};
                mat.specular = {0.0f, 0.0f, 0.0f}; // Блики полностью отсутствуют
                mat.shininess = 1.0f;
                mat.alpha = 1.0f;
                break;
        }
        return mat;
    }
}
