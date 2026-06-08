#ifndef LIGHT_H
#define LIGHT_H

#include <memory>
#include "composite/InvisibleObject.h"

class BaseLightImpl; 
class BaseVisitor;

class Light final : public InvisibleObject {
public:
    explicit Light(std::unique_ptr<BaseLightImpl> impl);
    ~Light() override;

    BaseLightImpl* getImpl() const noexcept { return _impl.get(); }

    void accept(const std::shared_ptr<BaseVisitor>& visitor) override;

    // Snapshot пока опционален, если нужно сохранять состояние света
    std::shared_ptr<Memento> createSnapshot() override;
    void restoreSnapshot(const std::shared_ptr<Memento>& snapshot) override;

private:
    std::unique_ptr<BaseLightImpl> _impl;
};

#endif
