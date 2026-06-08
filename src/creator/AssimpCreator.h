#include "creator/BaseCreator.h"
#include "bridge/AssimpModelImpl.h"
#include "director/AssimpDirector.h" 

class AssimpCreator : public BaseCreator {
public:
    std::unique_ptr<BaseDirector> createDirector() override {
        auto builder = std::make_unique<AssimpModelBuilder>(nullptr);
        return std::make_unique<AssimpDirector>(std::move(builder));
    }
};
