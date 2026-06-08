#ifndef BASEMODELIMPL_H
#define BASEMODELIMPL_H

#include <memory>
#include <vector>

#include "data/Point.h"
#include "data/Edge.h"
#include "data/Face.h"

class Memento;

class BaseModelImpl {
public:
    virtual ~BaseModelImpl() = default;

    [[nodiscard]] virtual std::vector<Point>& getPoints() noexcept = 0;
    [[nodiscard]] virtual const std::vector<Point>& getPoints() const noexcept = 0;
    [[nodiscard]] virtual std::vector<Edge> getEdges() const = 0;
    [[nodiscard]] virtual const std::vector<Face>& getFaces() const noexcept = 0;

    virtual void addPoint(const Point& p) = 0;
    virtual void addEdge(const Edge& e) = 0;
    virtual void addFace(const Face& f) = 0;

    [[nodiscard]] virtual std::vector<Edge> getVisibleEdges(const Point& cameraPos) const = 0;

    [[nodiscard]] virtual std::shared_ptr<Memento> createSnapshot() = 0;
    virtual void restoreSnapshot(const std::shared_ptr<Memento>& snapshot) = 0;
};

#endif // BASEMODELIMPL_H
