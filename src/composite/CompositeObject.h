#ifndef COMPOSITEOBJECT_H
#define COMPOSITEOBJECT_H

#include <memory>
#include "composite/BaseObject.h"

class BaseCompositeImpl;
class BaseVisitor;
class Memento;

class CompositeObject : public BaseObject {
public:
    CompositeObject();
    explicit CompositeObject(std::unique_ptr<BaseCompositeImpl> impl) noexcept;
    ~CompositeObject() override;

    [[nodiscard]] bool isVisible() const noexcept override { return false; }
    [[nodiscard]] bool isComposite() const noexcept override { return true; }

    bool add(const ObjectPtr& obj);
    bool remove(Iterator it);

    void accept(const std::shared_ptr<BaseVisitor>& visitor) override;

    [[nodiscard]] std::shared_ptr<Memento> createSnapshot() override;
    void restoreSnapshot(const std::shared_ptr<Memento>& snapshot) override;

    Iterator begin();
    Iterator end();

private:
    std::unique_ptr<BaseCompositeImpl> _impl;
};

#endif // COMPOSITEOBJECT_H
