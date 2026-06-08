#ifndef CARCASS_MODEL_H
#define CARCASS_MODEL_H

#include "base_model.h"
#include "carcass_model_implementor.h"

class BaseVisitor;

class CarcassModel: public BaseModel
{
	friend class DrawVisitor;
	friend class TransformVisitor;
public:

	explicit CarcassModel(std::shared_ptr<CarcassModelImplementor> impl);
	virtual void accept(std::shared_ptr<BaseVisitor> visitor);

protected:
	std::shared_ptr<CarcassModelImplementor> implementor;
};


#endif //CARCASS_MODEL_H
