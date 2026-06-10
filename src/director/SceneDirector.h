#ifndef SCENEDIRECTOR_H
#define SCENEDIRECTOR_H

#include <memory>
#include "director/BaseDirector.h"

class SceneBuilder;

class SceneDirector final : public BaseDirector {
public:
    explicit SceneDirector(std::unique_ptr<SceneBuilder> builder) noexcept;
    ~SceneDirector() override;

    [[nodiscard]] ObjectPtr construct(const std::string& filename) override;

private:
    std::unique_ptr<SceneBuilder> _builder;
};

#endif 
