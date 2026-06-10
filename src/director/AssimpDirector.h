#ifndef ASSIMPDIRECTOR_H
#define ASSIMPDIRECTOR_H

#include "director/BaseDirector.h"
#include <memory>

class AssimpModelBuilder;

class AssimpDirector : public BaseDirector {
public:
    explicit AssimpDirector(std::unique_ptr<AssimpModelBuilder> builder) noexcept;
    ~AssimpDirector() override = default;

    std::shared_ptr<BaseObject> construct(const std::string& filename) override;

private:
    std::unique_ptr<AssimpModelBuilder> _builder;
};

#endif
