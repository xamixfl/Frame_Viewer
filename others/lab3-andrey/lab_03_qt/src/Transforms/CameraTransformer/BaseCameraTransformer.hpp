//
// Created by nuelex on 21/05/25.
//

#ifndef BASECAMERATRANSFORMER_HPP
#define BASECAMERATRANSFORMER_HPP
#include <memory>

class Point;
class Camera;

class BaseCameraTransformer
{
public:
    BaseCameraTransformer() = delete;
    explicit BaseCameraTransformer(const std::shared_ptr<Camera> &camera) {}
    virtual ~BaseCameraTransformer() = default;

    [[nodiscard]] virtual Point transform(const Point &point) const = 0;
};



#endif //BASECAMERATRANSFORMER_HPP
