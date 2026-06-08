#ifndef CARCASMODELDIRECTOR_H
#define CARCASMODELDIRECTOR_H

#include <memory>
#include "director/BaseDirector.h"

class CarcasModelBuilder;

class CarcasModelDirector final : public BaseDirector {
public:
    explicit CarcasModelDirector(std::unique_ptr<CarcasModelBuilder> builder) noexcept;
    ~CarcasModelDirector() override;

    [[nodiscard]] ObjectPtr construct(const std::string& filename) override;

private:
    std::unique_ptr<CarcasModelBuilder> _builder;
};

#endif // CARCASMODELDIRECTOR_H
