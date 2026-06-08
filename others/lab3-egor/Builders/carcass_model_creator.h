#ifndef CARCASS_MODEL_CREATOR_H
#define CARCASS_MODEL_CREATOR_H

#include <memory>
#include "carcass_model.h"

class CarcassModelCreator
{
public:
	virtual ~CarcassModelCreator() = default;
	virtual std::shared_ptr<CarcassModel> create() = 0;
};


#endif //CARCASS_MODEL_CREATOR_H
