#ifndef CARCASS_MODEL_DIRECTOR_H
#define CARCASS_MODEL_DIRECTOR_H

#include "carcass_model_creator.h"
#include "carcass_model_builder.h"

class CarcassModelDirector: public CarcassModelCreator
{
public:
	CarcassModelDirector() = default;
	std::shared_ptr<CarcassModel> create() override;

protected:
	std::shared_ptr<CarcassModelBuilder> builder;
};


#endif //CARCASS_MODEL_DIRECTOR_H
