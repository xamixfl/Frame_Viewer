#include "list_carcass_model_builder.h"
#include "carcass_list_implementor.h"

ListCarcassModelBuilder::ListCarcassModelBuilder(std::shared_ptr<ModelDataSource> dataSource)
	: CarcassModelBuilder(dataSource)
{
	m_model = std::make_shared<CarcassListImplementor>();
}
