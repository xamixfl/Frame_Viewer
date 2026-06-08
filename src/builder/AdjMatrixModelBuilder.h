#ifndef ADJMATRIXMODELBUILDER_H
#define ADJMATRIXMODELBUILDER_H

#include "builder/CarcasModelBuilder.h"

class AdjMatrixModelBuilder final : public CarcasModelBuilder {
public:
    explicit AdjMatrixModelBuilder(std::unique_ptr<BaseReader> reader) noexcept;
    ~AdjMatrixModelBuilder() override;

protected:
    void _initModel() noexcept override;
};

#endif // ADJMATRIXMODELBUILDER_H
