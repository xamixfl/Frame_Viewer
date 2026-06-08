#ifndef CARCASDIRECTOR_H
#define CARCASDIRECTOR_H

#include "BaseDirector.h"
#include "../object/carcas/Carcas.h"

class CarcasDirector : public BaseDirector
{
public:
    CarcasDirector();
    CarcasDirector(std::shared_ptr<BaseCarcasBuilder> builder);

    std::shared_ptr<AbstractObject> create() override;
};

#endif // CARCASDIRECTOR_H
