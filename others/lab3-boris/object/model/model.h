#ifndef MODEL_H__
#define MODEL_H__

#include <vector>
#include <memory>

#include "object.h"
#include "model_impl.h"


class Model : public DrawableObject
{
public:
    Model() = default;
    explicit Model(const Model &other);
    explicit Model(std::shared_ptr<ModelImpl> impl);
    ~Model() override = default;

    void accept(const std::shared_ptr<BaseVisitor> &visitor) override;

    std::shared_ptr<Memento> create_snapshot() override;
    void restore_snapshot(std::shared_ptr<Memento> snapshot) override;

private:
    std::shared_ptr<ModelImpl> model;
};

#endif
