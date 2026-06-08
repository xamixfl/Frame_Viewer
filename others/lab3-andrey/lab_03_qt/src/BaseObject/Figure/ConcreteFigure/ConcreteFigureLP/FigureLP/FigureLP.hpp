#ifndef FIGURELP_HPP
#define FIGURELP_HPP

#include "AbstractFigureLP.hpp"
#include "../Links/Links.hpp"
#include "../Point/Points.hpp"
#include "../../../../../Transforms/Transforms.hpp"
#include "../../../../../HLR/Faces.hpp"

class FigureLP : public AbstractFigureLP
{
public:
    FigureLP() = default;
    explicit FigureLP(const FigureLP &);
    FigureLP(FigureLP &&) noexcept;
    FigureLP(const Links &, const Points &);
    FigureLP(Links &&links, Points &&points) noexcept;
    ~FigureLP() override = default;

    FigureLP &operator=(const FigureLP &other)
    {
        links_data  = other.links_data;
        points_data = other.points_data;
        faces_data  = other.faces_data;
        return *this;
    }
    FigureLP &operator=(FigureLP &&other) noexcept
    {
        links_data  = std::move(other.links_data);
        points_data = std::move(other.points_data);
        faces_data  = std::move(other.faces_data);
        return *this;
    }

    [[nodiscard]] const Links&  getLinks()  const noexcept override { return links_data; }
    [[nodiscard]] const Points& getPoints() const noexcept override { return points_data; }
    [[nodiscard]] const Faces&  getFaces()  const noexcept          { return faces_data; }

    void setLinks(const Links& links)    override { links_data = links; }
    void setLinks(Links&& links) noexcept override { links_data = std::move(links); }
    void setPoints(const Points& points) override { points_data = points; }
    void setPoints(Points&& points) noexcept override { points_data = std::move(points); }
    void setFaces(const Faces& faces)    { faces_data = faces; }
    void setFaces(Faces&& faces) noexcept { faces_data = std::move(faces); }

    void transform(const Mover &)   override;
    void transform(const Rotater &) override;
    void transform(const Scaler &)  override;

private:
    void rotate_function(const Rotater &);
    void scale_function(const Scaler &);

    Links  links_data;
    Points points_data;
    Faces  faces_data;

    static Rotater radFromDegree(const Rotater &rotater);
};

#endif //FIGURELP_HPP
