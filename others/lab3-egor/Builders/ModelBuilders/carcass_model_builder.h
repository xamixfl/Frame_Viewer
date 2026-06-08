#ifndef CARCASS_MODEL_BUILDER_H
#define CARCASS_MODEL_BUILDER_H

#include "carcass_model.h"
#include "model_data_source.h"

class CarcassModelBuilder
{
public:
	~CarcassModelBuilder() = default;
	CarcassModelBuilder() = default;
	explicit CarcassModelBuilder(std::shared_ptr<ModelDataSource> dataSource);

	virtual void buildPoints();
	virtual void buildEdges();
	virtual void buildFaces();
	virtual void buildCenter();
	virtual void buildLinkages();

	virtual std::shared_ptr<CarcassModel> getModel();

protected:
	std::shared_ptr<ModelDataSource> m_dataSource;
	std::shared_ptr<CarcassModelImplementor> m_model;
};


#endif //CARCASS_MODEL_BUILDER_H
