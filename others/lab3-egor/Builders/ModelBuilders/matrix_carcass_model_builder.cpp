#include "matrix_carcass_model_builder.h"
#include "carcass_matrix_implementor.h"

MatrixCarcassModelBuilder::MatrixCarcassModelBuilder(std::shared_ptr<ModelDataSource> dataSource)
	: CarcassModelBuilder(dataSource)
{
	m_model = std::make_shared<CarcassMatrixImplementor>();
}
