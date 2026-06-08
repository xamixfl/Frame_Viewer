#ifndef CARCASMODEL_H
#define CARCASMODEL_H

#include <memory>
#include <vector>

#include "bridge/BaseModelImpl.h"
#include "data/Edge.h"
#include "data/Face.h"
#include "data/Point.h"

class Memento;

class CarcasModel final : public BaseModelImpl {
public:
    CarcasModel() = default;
    ~CarcasModel() override = default;

    [[nodiscard]] std::vector<Point>& getPoints() noexcept override { return _points; }
    [[nodiscard]] const std::vector<Point>& getPoints() const noexcept override { return _points; }
    [[nodiscard]] std::vector<Edge> getEdges() const override { return _edges; }
    [[nodiscard]] const std::vector<Face>& getFaces() const noexcept override { return _faces; }

    void addPoint(const Point& p) override { _points.push_back(p); }
    void addEdge(const Edge& e) override { _edges.push_back(e); }
    void addFace(const Face& f) override { _faces.push_back(f); }

    [[nodiscard]] std::vector<Edge> getVisibleEdges(const Point& cameraPos) const override;

    [[nodiscard]] std::shared_ptr<Memento> createSnapshot() override;
    void restoreSnapshot(const std::shared_ptr<Memento>& snapshot) override;

private:
    std::vector<Point> _points;
    std::vector<Edge> _edges;
    std::vector<Face> _faces;
};

#endif // CARCASMODEL_H
