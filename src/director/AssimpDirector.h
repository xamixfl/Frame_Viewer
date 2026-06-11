#ifndef ASSIMPDIRECTOR_H
#define ASSIMPDIRECTOR_H

#include "director/BaseDirector.h"
#include <memory>

class AssimpDirector : public BaseDirector {
public:
    AssimpDirector() noexcept = default;
    ~AssimpDirector() override = default;

    ObjectPtr construct(const std::string& filename) override;
};

#endif // ASSIMPDIRECTOR_H
