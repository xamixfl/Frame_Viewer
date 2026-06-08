#include "carcass_model_director.h"

std::shared_ptr<CarcassModel> CarcassModelDirector::create()
{
	builder->buildPoints();
	builder->buildEdges();
	builder->buildFaces();
	builder->buildCenter();
	builder->buildLinkages();

	return builder->getModel();
}
