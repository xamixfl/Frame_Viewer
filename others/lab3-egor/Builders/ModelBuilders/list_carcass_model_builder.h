#ifndef LIST_CARCASS_MODEL_BUILDER_H
#define LIST_CARCASS_MODEL_BUILDER_H

#include "carcass_model_builder.h"

class ListCarcassModelBuilder: public CarcassModelBuilder
{
public:
	explicit ListCarcassModelBuilder(std::shared_ptr<ModelDataSource> dataSource);
};


#endif //LIST_CARCASS_MODEL_BUILDER_H
