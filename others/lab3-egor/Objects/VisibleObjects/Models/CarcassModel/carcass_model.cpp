#include "carcass_model.h"

#include <utility>
#include "base_visitor.h"

void CarcassModel::accept(std::shared_ptr<BaseVisitor> visitor)
{
	visitor->visit(*this);
}

CarcassModel::CarcassModel(std::shared_ptr<CarcassModelImplementor> impl)
{
	implementor = std::move(impl);
}




