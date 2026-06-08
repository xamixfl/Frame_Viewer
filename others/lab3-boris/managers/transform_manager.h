#ifndef TRANSFORM_MANAGER_H__
#define TRANSFORM_MANAGER_H__

#include <memory>
#include "base_manager.h"
#include "transform_visitor.h"
#include "concepts.h"
#include "object.h"

template<typename T>
concept ValidVisitor = ValidClass<T, TransformVisitor>;

template<typename T>
concept ConstructibleTransformer = ConstructibleFrom<T, Transformer>;

template<typename T>
concept ValidTransformVisitor = ValidVisitor<T> && ConstructibleTransformer<T>;


class TransformManager : public BaseManager
{
public:
    TransformManager() = default;
    explicit TransformManager(std::shared_ptr<TransformVisitor> v) noexcept;
    ~TransformManager() override = default;

    template<ValidTransformVisitor TVisitor>
    void set_visitor(Transformer _transform)
    {
        visitor = std::make_shared<TVisitor>(_transform);
    }

    void transform(std::shared_ptr<Object> &obj);

private:
    std::shared_ptr<TransformVisitor> visitor;
};

#endif
