#ifndef LIST_CARCASS_MODEL_DIRECTOR_H
#define LIST_CARCASS_MODEL_DIRECTOR_H

#include "carcass_model_director.h"

class ListCarcassModelDirector: public CarcassModelDirector
{
public:
	explicit ListCarcassModelDirector(std::shared_ptr<ModelDataSource> dataSource);
};


#endif //LIST_CARCASS_MODEL_DIRECTOR_H
