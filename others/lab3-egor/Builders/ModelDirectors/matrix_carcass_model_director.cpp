#include "matrix_carcass_model_director.h"
#include "matrix_carcass_model_builder.h"

MatrixCarcassModelDirector::MatrixCarcassModelDirector(std::shared_ptr<ModelDataSource> dataSource)
{
	builder = std::make_shared<MatrixCarcassModelBuilder>(dataSource);
}
