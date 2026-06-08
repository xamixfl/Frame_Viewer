//
// Created by nuelex on 25/05/25.
//

#ifndef ABSTRACTFIGURELP_HPP
#define ABSTRACTFIGURELP_HPP
#include "../../../../../Transforms/Transforms.hpp"
#include "../Links/Links.hpp"
#include "../Point/Points.hpp"
#include "../../../../../HLR/Faces.hpp"

class AbstractFigureLP
{
public:
    AbstractFigureLP() = default;
    virtual ~AbstractFigureLP() = default;

    [[nodiscard]] virtual const Links& getLinks() const noexcept = 0;
    [[nodiscard]] virtual const Points& getPoints() const noexcept = 0;
    [[nodiscard]] virtual const Faces& getFaces() const noexcept = 0;

    virtual void setLinks(const Links& links) = 0;
    virtual void setLinks(Links&& links) noexcept = 0;
    virtual void setPoints(const Points& points) = 0;
    virtual void setPoints(Points&& points) noexcept = 0;

    virtual void transform(const Mover &) = 0;
    virtual void transform(const Rotater &) = 0;
    virtual void transform(const Scaler &) = 0;
};



#endif //ABSTRACTFIGURELP_HPP
