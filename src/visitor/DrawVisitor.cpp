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
#include <cstdio>
#include <algorithm>

namespace {

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

struct RenderablePolygon {
    std::vector<Point> projectedPoints;
    Material material;
    double depthZ; // Глубина (расстояние до камеры)

    // Сортировка по убыванию глубины (от дальних к ближним - алгоритм живописца)
    bool operator<(const RenderablePolygon& other) const noexcept {
        return depthZ > other.depthZ;
    }
};

} // namespace

DrawVisitor::DrawVisitor(AbstractDrawerFactory& factory, std::shared_ptr<Camera> camera) noexcept
    : _factory(factory), _camera(std::move(camera)) {}

void DrawVisitor::visit(BaseModelImpl& impl) noexcept {
    auto drawer = _factory.createDrawer();
    drawer->clear();
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

    std::vector<RenderablePolygon> renderQueue;

    for (size_t i = 0; i < faces.size(); ++i) {
        const auto& face = faces[i];
        if (!impl.isFaceVisible(i, _camera->_impl->getPosition())) continue;

        const Point& p1 = points[face[0]];
        const Point& p2 = points[face[1]];
        const Point& p3 = points[face[2]];

        Point normal = normalize(cross(sub(p3, p1), sub(p2, p1)));

        float r = 0.2f, g = 0.2f, b = 0.2f; // Ambient
        for (const auto& light : _lights) {
            float lr, lg, lb;
            light->getIntensityAt(p1, normal, lr, lg, lb);
            r += lr; g += lg; b += lb;
        }

        Material lightedMat = impl.getMaterial();

        std::vector<Point> projectedPoints;
        bool visible = true;
        double totalZ = 0.0;
        
        for (int index : face) {
            ViewPoint vp = toView(points[index], vb);
            if (vp.z <= 0) { visible = false; break; }
            projectedPoints.push_back(project(vp));
            totalZ += vp.z;
        }

        if (visible && projectedPoints.size() >= 3) {
            auto clamp = [](float val) { return std::max(0.0f, std::min(1.0f, val)); };
            
            lightedMat.diffuse[0] = clamp(lightedMat.diffuse[0] * r);
            lightedMat.diffuse[1] = clamp(lightedMat.diffuse[1] * g);
            lightedMat.diffuse[2] = clamp(lightedMat.diffuse[2] * b);
            
            double avgZ = totalZ / face.size();
            renderQueue.push_back({std::move(projectedPoints), lightedMat, avgZ});
        }
    }

    // Сортируем полигоны от дальних к ближним
    std::sort(renderQueue.begin(), renderQueue.end());

    // Отрисовываем по порядку
    for (const auto& poly : renderQueue) {
        drawer->drawPolygon(poly.projectedPoints, poly.material);
    }
}

void DrawVisitor::visit(BaseCameraImpl&) noexcept {}

void DrawVisitor::visit(BaseLightImpl& impl) noexcept {
    _lights.push_back(&impl);
}
