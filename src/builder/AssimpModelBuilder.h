#ifndef ASSIMPMODELBUILDER_H
#define ASSIMPMODELBUILDER_H

#include "builder/BaseBuilder.h"
#include "data/Point.h"
#include "data/Face.h"
#include "data/Material.h"
#include "composite/BaseObject.h"

class AssimpModelImpl;

class AssimpModelBuilder : public BaseBuilder {
public:
    explicit AssimpModelBuilder(std::unique_ptr<BaseReader> reader = nullptr); 
    ~AssimpModelBuilder() override;

    void build() override;
    
    void addPoint(const Point& p);
    void addFace(const Face& f);
    void setMaterial(const Material& m);

    std::shared_ptr<BaseObject> getResult();
    
private:
    std::unique_ptr<AssimpModelImpl> _model;
    void _initModel() noexcept;
};

#endif
