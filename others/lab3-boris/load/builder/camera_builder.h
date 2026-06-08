#ifndef CAMERA_BUILDER_H__
#define CAMERA_BUILDER_H__

#include "builder.h"
#include "point.h"


class CameraBuilder : public Builder
{
public:
    CameraBuilder() = default;
    explicit CameraBuilder(std::shared_ptr<Loader> _loader);
    ~CameraBuilder() override;

    void create_position();
    void create_target();
    void create_up();

    void build() override;

    std::shared_ptr<Object> get_result() override;

private:
    Point position;
    Point target;
    Point up;
};

#endif
