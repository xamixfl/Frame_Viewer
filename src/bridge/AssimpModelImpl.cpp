#include "bridge/AssimpModelImpl.h"
#include "memento/Memento.h"

namespace {
    Point sub(const Point& a, const Point& b) { return { a.getX() - b.getX(), a.getY() - b.getY(), a.getZ() - b.getZ() }; }
    Point cross(const Point& a, const Point& b) {
        return { a.getY()*b.getZ() - a.getZ()*b.getY(), a.getZ()*b.getX() - a.getX()*b.getZ(), a.getX()*b.getY() - a.getY()*b.getX() };
    }
    double dot(const Point& a, const Point& b) { return a.getX()*b.getX() + a.getY()*b.getY() + a.getZ()*b.getZ(); }
}

AssimpModelImpl::AssimpModelImpl() = default;
AssimpModelImpl::~AssimpModelImpl() = default;

bool AssimpModelImpl::faceVisible(const std::vector<Point>& points, const Face& face, const Point& camPos) const {
    if (face.size() < 3) return true;
    const Point& a = points[face[0]];
    const Point& b = points[face[1]];
    const Point& c = points[face[2]];
    return dot(cross(sub(b, a), sub(c, a)), sub(camPos, a)) > 0.0;
}

bool AssimpModelImpl::isFaceVisible(size_t faceIndex, const Point& cameraPos) const {
    if (faceIndex >= _faces.size()) return false;
    return faceVisible(_points, _faces[faceIndex], cameraPos);
}

bool AssimpModelImpl::edgeInFace(const Edge& edge, const Face& face) const {
    for (size_t i = 0; i < face.size(); ++i) {
        int a = face[i], b = face[(i + 1) % face.size()];
        if ((a == edge.first() && b == edge.second()) || (a == edge.second() && b == edge.first())) return true;
    }
    return false;
}

std::vector<Edge> AssimpModelImpl::getVisibleEdges(const Point& cam) const {
    std::vector<bool> fVis(_faces.size());
    for (size_t i = 0; i < _faces.size(); ++i) fVis[i] = faceVisible(_points, _faces[i], cam);

    std::vector<Edge> visible;
    for (const auto& e : _edges) {
        bool any = false, vis = false;
        for (size_t i = 0; i < _faces.size(); ++i) {
            if (!edgeInFace(e, _faces[i])) continue;
            any = true;
            if (fVis[i]) { vis = true; break; }
        }
        if (!any || vis) visible.push_back(e);
    }
    return visible;
}

std::shared_ptr<Memento> AssimpModelImpl::createSnapshot() {
    return std::shared_ptr<ModelMemento>(new ModelMemento(_points, _material));
}

void AssimpModelImpl::restoreSnapshot(const std::shared_ptr<Memento>& snapshot) {
    auto m = std::dynamic_pointer_cast<ModelMemento>(snapshot);
    if (m) {
        _points = m->_points;
        _material = m->_material;
    }
}
