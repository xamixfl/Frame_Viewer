#ifndef ASSIMPMODELIMPL_H
#define ASSIMPMODELIMPL_H

#include "bridge/BaseModelImpl.h"
#include <vector>

class AssimpModelImpl final : public BaseModelImpl {
public:
    AssimpModelImpl();
    ~AssimpModelImpl() override;

    std::vector<Point>& getPoints() noexcept override { return _points; }
    const std::vector<Point>& getPoints() const noexcept override { return _points; }
    const std::vector<Face>& getFaces() const noexcept override { return _faces; }

    void addPoint(const Point& p) override { _points.push_back(p); }
    void addFace(const Face& f) override { _faces.push_back(f); }

    bool isFaceVisible(size_t faceIndex, const Point& cameraPos) const override;

    std::shared_ptr<Memento> createSnapshot() override;
    void restoreSnapshot(const std::shared_ptr<Memento>& snapshot) override;

    void setMaterial(const Material& mat) noexcept override { _material = mat; }
    Material getMaterial() const noexcept override { return _material; }

private:
    bool faceVisible(const std::vector<Point>& points, const Face& face, const Point& camPos) const;

    std::vector<Point> _points;
    std::vector<Face> _faces;
    Material _material;
};

#endif
