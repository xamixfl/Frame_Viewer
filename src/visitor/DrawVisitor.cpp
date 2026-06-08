#include "visitor/DrawVisitor.h"
#include "composite/Camera.h"
#include "bridge/BaseModelImpl.h"
#include "bridge/BaseCameraImpl.h"
#include "bridge/BaseLightImpl.h"
#include "factory/AbstractDrawerFactory.h"
#include "factory/BaseDrawer.h"
#include "data/Point.h"
#include "data/Edge.h"

#include <cmath>
#include <vector>

namespace {

double dot(const Point& a, const Point& b) noexcept {
    return a.getX() * b.getX() + a.getY() * b.getY() + a.getZ() * b.getZ();
}

Point cross(const Point& a, const Point& b) noexcept {
    return {
        a.getY() * b.getZ() - a.getZ() * b.getY(),
        a.getZ() * b.getX() - a.getX() * b.getZ(),
        a.getX() * b.getY() - a.getY() * b.getX()
    };
}

Point sub(const Point& a, const Point& b) noexcept {
    return { a.getX() - b.getX(), a.getY() - b.getY(), a.getZ() - b.getZ() };
}

Point normalize(const Point& a) noexcept {
    const double l = std::sqrt(dot(a, a));
    if (l < 1e-9) {
        return { 0.0, 0.0, 1.0 };
    }
    return { a.getX() / l, a.getY() / l, a.getZ() / l };
}

constexpr double FOCAL = 8.0;
constexpr double NEAR_Z = 0.05;

struct ViewBasis {
    Point pos;
    Point right;
    Point up;
    Point fwd;
    bool valid = false;
};

ViewBasis buildBasis(const BaseCameraImpl& cam) noexcept {
    ViewBasis vb;
    vb.pos = cam.getPosition();
    vb.fwd = normalize(cam.getDirection());
    const Point r = cross(vb.fwd, cam.getUp());
    if (std::sqrt(dot(r, r)) < 1e-9) {
        return vb;
    }
    vb.right = normalize(r);
    vb.up = cross(vb.right, vb.fwd);
    vb.valid = true;
    return vb;
}

struct ViewPoint {
    double x;
    double y;
    double z;
};

ViewPoint toView(const Point& p, const ViewBasis& vb) noexcept {
    const Point v = sub(p, vb.pos);
    return { dot(v, vb.right), dot(v, vb.up), dot(v, vb.fwd) };
}

Point project(const ViewPoint& vp) noexcept {
    return { vp.x / vp.z * FOCAL, vp.y / vp.z * FOCAL, 0.0 };
}

bool clipNear(ViewPoint& a, ViewPoint& b) noexcept {
    const bool aIn = a.z >= NEAR_Z;
    const bool bIn = b.z >= NEAR_Z;
    if (aIn && bIn) {
        return true;
    }
    if (!aIn && !bIn) {
        return false;
    }
    const double t = (NEAR_Z - a.z) / (b.z - a.z);
    const ViewPoint i {
        a.x + t * (b.x - a.x),
        a.y + t * (b.y - a.y),
        NEAR_Z
    };
    if (!aIn) {
        a = i;
    } else {
        b = i;
    }
    return true;
}

} // namespace

DrawVisitor::DrawVisitor(AbstractDrawerFactory& factory, std::shared_ptr<Camera> camera) noexcept
    : _factory(factory), _camera(std::move(camera)) {}

void DrawVisitor::visit(BaseModelImpl& impl) noexcept {
    auto drawer = _factory.createDrawer();
    const std::vector<Face>& faces = impl.getFaces();
    const std::vector<Point>& points = impl.getPoints();

    if (!_camera) {
        const std::vector<Edge> edges = impl.getEdges();
        for (const Edge& e : edges) {
            const int a = e.first();
            const int b = e.second();
            if (a < 0 || b < 0 || static_cast<size_t>(a) >= points.size() || static_cast<size_t>(b) >= points.size()) {
                continue;
            }
            drawer->drawLine(points[a], points[b]);
        }
        return;
    }

    const ViewBasis vb = buildBasis(*_camera->_impl);
    if (!vb.valid) {
        return;
    }

    for (size_t i = 0; i < faces.size(); ++i) {
        const auto& face = faces[i];

        if (!impl.isFaceVisible(i, _camera->_impl->getPosition())) {
            continue;
        }

        const Point& p1 = points[face[0]];
        const Point& p2 = points[face[1]];
        const Point& p3 = points[face[2]];
        Point normal = normalize(cross(sub(p2, p1), sub(p3, p1)));

        float r = 0.0f, g = 0.0f, b = 0.0f;
        for (const auto& light : _lights) {
            float lr, lg, lb;
            light->getIntensityAt(p1, normal, lr, lg, lb);
            r += lr; g += lg; b += lb;
        }

        Material lightedMat = impl.getMaterial();
        for (int j = 0; j < 3; ++j) {
            lightedMat.diffuse[j] *= r; 
        }

        std::vector<Point> projectedPoints;
        bool visible = true;
        for (int index : face) {
            ViewPoint vp = toView(points[index], vb);
            if (vp.z <= 0) { 
                visible = false; 
                break; 
            }
            projectedPoints.push_back(project(vp));
        }

        if (visible && projectedPoints.size() >= 3) {
            drawer->drawPolygon(projectedPoints, lightedMat);
        }
    }
}

void DrawVisitor::visit(BaseCameraImpl& /*impl*/) noexcept {}

void DrawVisitor::visit(BaseLightImpl& impl) noexcept {
    _lights.push_back(std::shared_ptr<BaseLightImpl>(&impl, [](BaseLightImpl*){}));
}

