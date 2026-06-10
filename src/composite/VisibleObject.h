#ifndef VISIBLEOBJECT_H
#define VISIBLEOBJECT_H

#include "composite/BaseObject.h"

class VisibleObject : public BaseObject {
public:
    ~VisibleObject() override = default;

    [[nodiscard]] bool isVisible() const noexcept override { return true; }
};

#endif 
