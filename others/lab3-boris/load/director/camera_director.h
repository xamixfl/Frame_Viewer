#ifndef CAMERA_DIRECTOR_H__
#define CAMERA_DIRECTOR_H__

#include "director.h"


class CameraDirector : public Director
{
public:
    CameraDirector() = default;
    CameraDirector(std::shared_ptr<Builder> _builder);
    ~CameraDirector() override = default;

    std::shared_ptr<Object> create() override;
};

#endif
