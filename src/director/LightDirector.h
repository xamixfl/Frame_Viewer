#ifndef LIGHTDIRECTOR_H
#define LIGHTDIRECTOR_H

#include "director/BaseDirector.h"
#include <memory>

class BaseBuilder;

class LightDirector : public BaseDirector {
public:
    explicit LightDirector(std::unique_ptr<BaseBuilder> builder) noexcept;
    ~LightDirector() override = default;

    ObjectPtr construct(const std::string& filename) override;

private:
    std::unique_ptr<BaseBuilder> _builder;
};

#endif // LIGHTDIRECTOR_H
