#ifndef CAMERADIRECTOR_H
#define CAMERADIRECTOR_H

#include "director/BaseDirector.h"
#include <memory>

class BaseBuilder;

class CameraDirector : public BaseDirector {
public:
    explicit CameraDirector(std::unique_ptr<BaseBuilder> builder) noexcept;
    ~CameraDirector() override = default;

    ObjectPtr construct(const std::string& filename) override;

private:
    std::unique_ptr<BaseBuilder> _builder;
};

#endif // CAMERADIRECTOR_H
