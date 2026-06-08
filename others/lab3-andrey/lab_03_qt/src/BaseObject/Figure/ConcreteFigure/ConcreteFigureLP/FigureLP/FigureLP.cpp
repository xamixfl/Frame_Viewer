//
// Created by nuelex on 08/05/25.
//

#include "FigureLP.hpp"

#include <math.h>

FigureLP::FigureLP(const FigureLP &figure)
{
    links_data  = figure.links_data;
    points_data = figure.points_data;
    faces_data  = figure.faces_data;          // ← БЫЛО ПРОПУЩЕНО
}

FigureLP::FigureLP(FigureLP &&figure) noexcept
{
    links_data  = std::move(figure.links_data);
    points_data = std::move(figure.points_data);
    faces_data  = std::move(figure.faces_data); // ← БЫЛО ПРОПУЩЕНО
}

FigureLP::FigureLP(const Links &links, const Points &points)
{
    this->links_data = links;
    this->points_data = points;
}

FigureLP::FigureLP(Links &&links, Points &&points) noexcept
{
    this->links_data = std::move(links);
    this->points_data = std::move(points);
}

void FigureLP::rotate_function(const Rotater &rotater)
{
    PointsIterator<Point, Points> iterator(points_data);

    for (iterator.First(); ! iterator.IsDone(); iterator.Next())
        iterator.Current()->rotate(rotater.getOx(), rotater.getOy(), rotater.getOz());
}

void FigureLP::scale_function(const Scaler &scaler)
{
    PointsIterator<Point, Points> iterator(points_data);

    for (iterator.First(); ! iterator.IsDone(); iterator.Next())
        iterator.Current()->scale(scaler.getKx(), scaler.getKy(), scaler.getKz());
}

void FigureLP::transform(const Mover &mover)
{
    PointsIterator<Point, Points> iterator(points_data);

    for (iterator.First(); ! iterator.IsDone(); iterator.Next())
        iterator.Current()->move(mover.getDx(), mover.getDy(), mover.getDz());
}

void FigureLP::transform(const Rotater &rotater)
{
    const Mover backMover = -rotater.centerToMover();
    auto radRotater = radFromDegree(rotater);
    const Mover fwdMover = rotater.centerToMover();

    this->transform(backMover);
    this->rotate_function(radRotater);
    this->transform(fwdMover);
}

void FigureLP::transform(const Scaler &scaler)
{
    const Mover backMover = -scaler.centerToMover();
    const Mover fwdMover = scaler.centerToMover();

    this->transform(backMover);
    this->scale_function(scaler);
    this->transform(fwdMover);
}

Rotater FigureLP::radFromDegree(const Rotater &rotater)
{
    return {rotater.getOx() * M_PI / 180,
            rotater.getOy() * M_PI / 180,
            rotater.getOz() * M_PI / 180,
            rotater.getCenter()};
}
