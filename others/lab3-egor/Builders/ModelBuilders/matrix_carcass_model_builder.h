#ifndef MATRIX_CARCASS_MODEL_BUILDER_H
#define MATRIX_CARCASS_MODEL_BUILDER_H

#include "carcass_model_builder.h"

class MatrixCarcassModelBuilder: public CarcassModelBuilder
{
public:
	explicit MatrixCarcassModelBuilder(std::shared_ptr<ModelDataSource> dataSource);
};


#endif //MATRIX_CARCASS_MODEL_BUILDER_H
