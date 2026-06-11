#include "bridge/AssimpModelImpl.h"
#include "data/Point.h"
#include "memento/Memento.h"
#include <cstdio>

namespace {}

AssimpModelImpl::AssimpModelImpl() = default;
AssimpModelImpl::~AssimpModelImpl() = default;

bool AssimpModelImpl::faceVisible(const std::vector<Point>& points, const Face& face, const Point& camPos) const {
    if (face.size() < 3) return true;
    const Point& a = points[face[0]];
    const Point& b = points[face[1]];
    const Point& c = points[face[2]];
    
    double result = dot(cross(sub(b, a), sub(c, a)), sub(camPos, a));
    printf("Face visible result: %f\n", result);
    
    return result > 0.0;
}

bool AssimpModelImpl::isFaceVisible(size_t faceIndex, const Point& cameraPos) const {
    if (faceIndex >= _faces.size()) return false;
    return faceVisible(_points, _faces[faceIndex], cameraPos);
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
