#ifndef INVISIBLEOBJECT_H
#define INVISIBLEOBJECT_H

#include "composite/BaseObject.h"

class InvisibleObject : public BaseObject {
public:
    ~InvisibleObject() override = default;

    [[nodiscard]] bool isVisible() const noexcept override { return false; }
};

#endif
