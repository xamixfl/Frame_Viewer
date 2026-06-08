#include "bridge/CarcasModel.h"

#include "memento/Memento.h"

namespace {

Point sub(const Point& a, const Point& b) noexcept {
    return { a.getX() - b.getX(), a.getY() - b.getY(), a.getZ() - b.getZ() };
}

Point crossProduct(const Point& a, const Point& b) noexcept {
    return {
        a.getY() * b.getZ() - a.getZ() * b.getY(),
        a.getZ() * b.getX() - a.getX() * b.getZ(),
        a.getX() * b.getY() - a.getY() * b.getX()
    };
}

double dot(const Point& a, const Point& b) noexcept {
    return a.getX() * b.getX() + a.getY() * b.getY() + a.getZ() * b.getZ();
}

bool faceVisible(const std::vector<Point>& points, const Face& face, const Point& camPos) noexcept {
    if (face.size() < 3) {
        return true;
    }
    const Point& a = points[face[0]];
    const Point& b = points[face[1]];
    const Point& c = points[face[2]];
    const Point normal = crossProduct(sub(b, a), sub(c, a));
    const Point toCam  = sub(camPos, a);
    return dot(normal, toCam) > 0.0;
}

bool edgeInFace(const Edge& edge, const Face& face) noexcept {
    const int ea = edge.first();
    const int eb = edge.second();
    const int n  = static_cast<int>(face.size());
    for (int k = 0; k < n; ++k) {
        const int fa = face[k];
        const int fb = face[(k + 1) % n];
        if ((fa == ea && fb == eb) || (fa == eb && fb == ea)) {
            return true;
        }
    }
    return false;
}

} // namespace

std::vector<Edge> CarcasModel::getVisibleEdges(const Point& cameraPos) const {
    if (_faces.empty()) {
        return _edges;
    }

    std::vector<bool> faceVis(_faces.size());
    for (size_t f = 0; f < _faces.size(); ++f) {
        faceVis[f] = faceVisible(_points, _faces[f], cameraPos);
    }

    std::vector<Edge> visible;
    visible.reserve(_edges.size());
    for (const auto& edge : _edges) {
        bool hasAnyFace = false;
        bool hasVisibleFace = false;
        for (size_t f = 0; f < _faces.size(); ++f) {
            if (!edgeInFace(edge, _faces[f])) {
                continue;
            }
            hasAnyFace = true;
            if (faceVis[f]) {
                hasVisibleFace = true;
                break;
            }
        }
        if (!hasAnyFace || hasVisibleFace) {
            visible.push_back(edge);
        }
    }
    return visible;
}

std::shared_ptr<Memento> CarcasModel::createSnapshot() {
    return std::shared_ptr<ModelMemento>(new ModelMemento(_points));
}

void CarcasModel::restoreSnapshot(const std::shared_ptr<Memento>& snapshot) {
    auto m = std::dynamic_pointer_cast<ModelMemento>(snapshot);
    if (m) {
        _points = m->points;
    }
}
