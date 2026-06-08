#include "builder/AdjMatrixModelBuilder.h"
#include "bridge/AdjMatrixModel.h"

AdjMatrixModelBuilder::AdjMatrixModelBuilder(std::unique_ptr<BaseReader> reader) noexcept
    : CarcasModelBuilder(std::move(reader)) {}

AdjMatrixModelBuilder::~AdjMatrixModelBuilder() = default;

void AdjMatrixModelBuilder::_initModel() noexcept {
    _model = std::make_unique<AdjMatrixModel>();
}
