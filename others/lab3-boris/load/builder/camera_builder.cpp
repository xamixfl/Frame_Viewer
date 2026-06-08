#include "camera_builder.h"
#include "camera.h"


CameraBuilder::CameraBuilder(std::shared_ptr<Loader> _loader)
{
    loader = std::move(_loader);
    loader->open();
}

CameraBuilder::~CameraBuilder()
{
    if (loader)
    {
        if (loader->is_open())
        {
            loader->close();
        }
    }
}

void CameraBuilder::create_position()
{
    double x, y, z;
    x = loader->read();
    y = loader->read();
    z = loader->read();

    position = Point(x, y, z);
}

void CameraBuilder::create_target()
{
    double x, y, z;
    x = loader->read();
    y = loader->read();
    z = loader->read();

    target = Point(x, y, z);
}

void CameraBuilder::create_up()
{
    double x, y, z;
    x = loader->read();
    y = loader->read();
    z = loader->read();

    up = Point(x, y, z);
}

void CameraBuilder::build()
{
    if (!loader->is_open())
        loader->open();

    create_position();
    create_target();
    create_up();

    obj = std::make_shared<Camera>(position, target, up);

    loader->close();
}

std::shared_ptr<Object> CameraBuilder::get_result()
{
    return obj;
}
