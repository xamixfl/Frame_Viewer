#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include "composite/VisibleObject.h"

class BaseModelImpl;
class BaseVisitor;
class Memento;

class Model final : public VisibleObject {
public:
    explicit Model(std::unique_ptr<BaseModelImpl> impl);
    ~Model() override;

    void accept(const std::shared_ptr<BaseVisitor>& visitor) override;

    [[nodiscard]] std::shared_ptr<Memento> createSnapshot() override;
    void restoreSnapshot(const std::shared_ptr<Memento>& snapshot) override;

private:
    std::unique_ptr<BaseModelImpl> _impl;
};

#endif // MODEL_H
