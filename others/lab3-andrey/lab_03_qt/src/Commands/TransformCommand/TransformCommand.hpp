#ifndef TRANSFORMCOMMAND_HPP
#define TRANSFORMCOMMAND_HPP
#include <memory>
#include <type_traits>

#include "../BaseCommand.hpp"
#include "../../BaseObject/BaseObject.hpp"
#include "../../Transforms/Transforms.hpp"
#include "../../Visitors/Transform/BaseTransformVisitor.hpp"

template <typename TVisitor>
requires std::is_base_of_v<BaseTransformVisitor, TVisitor>
      && (!std::is_abstract_v<TVisitor>)
class TransformCommand : public BaseCommand
{
public:
    TransformCommand(std::shared_ptr<BaseObject>    object,
                     std::shared_ptr<BaseTransform> transform)
        : _object(std::move(object)), _transform(std::move(transform)) {}

    ~TransformCommand() override = default;

    void execute() override
    {
        if (!_object || !_transform) return;
        TVisitor visitor{_transform};
        _object->accept(visitor);
    }

private:
    std::shared_ptr<BaseObject>    _object;
    std::shared_ptr<BaseTransform> _transform;
};

#endif //TRANSFORMCOMMAND_HPP
