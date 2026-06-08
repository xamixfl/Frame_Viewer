#ifndef MODEL_DIRECTOR_H__
#define MODEL_DIRECTOR_H__

#include "director.h"


class ModelDirector : public Director
{
public:
    ModelDirector() = default;
    ModelDirector(std::shared_ptr<Builder> _builder);
    ~ModelDirector() override = default;

    std::shared_ptr<Object> create() override;
};

#endif
