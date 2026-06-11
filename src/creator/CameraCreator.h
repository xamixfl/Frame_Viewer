#ifndef CAMERACREATOR_H
#define CAMERACREATOR_H

#include "creator/BaseCreator.h"
#include "builder/CameraBuilder.h"
#include "director/CameraDirector.h"

#include <memory>

class CameraCreator : public BaseCreator {
public:
    ~CameraCreator() override = default;

    std::unique_ptr<BaseDirector> createDirector() override {
        auto builder = std::make_unique<CameraBuiler>(nullptr);
        return std::make_unique<CameraDirector>(std::move(builder));
    }
};

#endif // CAMERACREATOR_H
