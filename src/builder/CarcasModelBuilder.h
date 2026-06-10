#ifndef CARCASMODELBUILDER_H
#define CARCASMODELBUILDER_H

#include <memory>
#include "builder/BaseBuilder.h"

class BaseModelImpl;

class CarcasModelBuilder : public BaseBuilder {
public:
    explicit CarcasModelBuilder(std::unique_ptr<BaseReader> reader) noexcept;
    ~CarcasModelBuilder() override;

    void build() override;

    [[nodiscard]] std::unique_ptr<BaseModelImpl> getResult() noexcept;

protected:
    std::unique_ptr<BaseModelImpl> _model;

    virtual void _initModel() noexcept;

private:
    void _checkReader() const;
    void _readPoints() const;
    void _readEdges() const;
    void _readFaces() const;
};

#endif 
