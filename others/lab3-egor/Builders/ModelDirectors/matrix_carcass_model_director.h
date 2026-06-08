#ifndef MATRIX_CARCASS_MODEL_DIRECTOR_H
#define MATRIX_CARCASS_MODEL_DIRECTOR_H

#include "carcass_model_director.h"

class MatrixCarcassModelDirector: public CarcassModelDirector
{
public:
	explicit MatrixCarcassModelDirector(std::shared_ptr<ModelDataSource> dataSource);
};


#endif //MATRIX_CARCASS_MODEL_DIRECTOR_H
