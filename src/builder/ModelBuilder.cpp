#include "builder/ModelBuilder.h"
#include "composite/Model.h"
#include "AssimpReader.h" // Ваш ридер, наследуемый от BaseReader
#include "bridge/ModelImpl.h" // Примерный путь к вашей реализации BaseModelImpl
#include "exception/Exceptions.h"

#include <utility>

ModelBuilder::ModelBuilder(std::unique_ptr<BaseReader> reader) noexcept
    : BaseBuilder(std::move(reader)) {}

ModelBuilder::~ModelBuilder() = default;

void ModelBuilder::build() {
    _checkReader();
    _loadData();
    _assembleResult();
}

std::unique_ptr<Model> ModelBuilder::getResult() noexcept {
    return std::move(_impl);
}

void ModelBuilder::_checkReader() const {
    // Убедимся, что ридер существует, открыт и не находится в состоянии eof
    if (!_reader || !_reader->isOpen() || _reader->eof()) {
        throw BuilderNotReadyError(__FILE__, "ModelBuilder", __FUNCTION__);
    }
}

void ModelBuilder::_loadData() {
    // Приводим базовый указатель к нашему AssimpReader для доступа к специфичным методам
    auto* assimpReader = dynamic_cast<AssimpReader*>(_reader.get());
    if (!assimpReader) {
        throw std::runtime_error("Invalid reader type provided to ModelBuilder");
    }
    
    // Вызов read() в вашем ридере открывает/парсит меши, либо можно вызвать метод получения данных напрямую
    // (в зависимости от того, как именно вы настроили read в AssimpReader)
    double resultCount = assimpReader->read();
    if (resultCount <= 0) {
        throw std::runtime_error("Failed to load any meshes or empty model file");
    }
}

void ModelBuilder::_assembleResult() {
    auto* assimpReader = dynamic_cast<AssimpReader*>(_reader.get());
    const auto& meshes = assimpReader->getMeshes();

    // Создаем имплементацию для моста (Bridge), передавая туда считанные меши
    auto modelImpl = std::make_unique<ModelImpl>(meshes);
    
    // Инициализируем конечный объект Model
    _impl = std::make_unique<Model>(std::move(modelImpl));
}
