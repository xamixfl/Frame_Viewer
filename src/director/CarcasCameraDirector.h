#ifndef CARCASCAMERADIRECTOR_H
#define CARCASCAMERADIRECTOR_H

#include <memory>
#include "director/BaseDirector.h"

class CarcasCameraBuilder;

class CarcasCameraDirector final : public BaseDirector {
public:
    explicit CarcasCameraDirector(std::unique_ptr<CarcasCameraBuilder> builder) noexcept;
    ~CarcasCameraDirector() override;

    [[nodiscard]] ObjectPtr construct(const std::string& filename) override;

private:
    std::unique_ptr<CarcasCameraBuilder> _builder;
};

#endif // CARCASCAMERADIRECTOR_H
