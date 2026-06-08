#ifndef BACKFACECULLINGSTRATEGY_HPP
#define BACKFACECULLINGSTRATEGY_HPP

#include <cmath>
#include "BaseHLRStrategy.hpp"
#include "../BaseObject/Camera/CameraPTU.hpp"
#include "../Transforms/CameraTransformer/CameraPTU/CameraPTUTransformer.hpp"

class BackFaceCullingStrategy : public BaseHLRStrategy
{
public:
    BackFaceCullingStrategy() = default;
    ~BackFaceCullingStrategy() override = default;

    [[nodiscard]] std::vector<size_t> visibleEdges(
        const Links&  links,
        const Points& points,
        const Faces&  faces,
        const std::shared_ptr<BaseCameraTransformer>& transformer) const override
    {
        if (faces.empty())
        {
            std::vector<size_t> result;
            result.reserve(links.size());
            for (size_t i = 0; i < links.size(); ++i) result.push_back(i);
            return result;
        }

        // 1. Определяем видимость каждой грани
        const std::vector<bool> faceVisible = computeFaceVisibility(faces, points, transformer);

        // 2. Ребро видимо если:
        //    a) принадлежит хотя бы одной видимой грани, или
        //    b) не принадлежит ни одной грани (каркасное ребро)
        std::vector<size_t> result;
        auto linksIter = links.CreateConstIterator();
        size_t edgeIdx = 0;

        for (linksIter.First(); !linksIter.IsDone(); linksIter.Next(), ++edgeIdx)
        {
            const size_t a = linksIter.Current()->GetBeginID();
            const size_t b = linksIter.Current()->GetEndID();

            bool belongsToFace  = false;
            bool hasVisibleFace = false;

            for (size_t fi = 0; fi < faces.size(); ++fi)
            {
                if (faces[fi].containsEdge(a, b))
                {
                    belongsToFace = true;
                    if (faceVisible[fi]) { hasVisibleFace = true; break; }
                }
            }

            if (!belongsToFace || hasVisibleFace)
                result.push_back(edgeIdx);
        }

        return result;
    }

private:
    // Вычислить нормаль грани через первые три вершины
    static std::array<double,3> faceNormal(const Face& face, const Points& points)
    {
        const auto& idx = face.getIndices();
        const Point& p0 = points[idx[0]];
        const Point& p1 = points[idx[1]];
        const Point& p2 = points[idx[2]];

        // AB = p1 - p0,  AC = p2 - p0
        const double abx = p1.GetX() - p0.GetX();
        const double aby = p1.GetY() - p0.GetY();
        const double abz = p1.GetZ() - p0.GetZ();

        const double acx = p2.GetX() - p0.GetX();
        const double acy = p2.GetY() - p0.GetY();
        const double acz = p2.GetZ() - p0.GetZ();

        // cross(AB, AC)
        return {
            aby * acz - abz * acy,
            abz * acx - abx * acz,
            abx * acy - aby * acx
        };
    }

    std::vector<bool> computeFaceVisibility(
        const Faces& faces,
        const Points& points,
        const std::shared_ptr<BaseCameraTransformer>& transformer) const
    {
        // Получить позицию камеры через трансформер
        // CameraPTUTransformer хранит _camera — достаём через dynamic_cast
        const auto ptuTransformer =
            std::dynamic_pointer_cast<CameraPTUTransformer>(transformer);

        std::vector<bool> visible(faces.size(), true);

        if (!ptuTransformer) return visible; // без камеры — всё видимо

        const auto& camPos = ptuTransformer->getCameraPosition(); // см. ниже

        for (size_t fi = 0; fi < faces.size(); ++fi)
        {
            const auto& idx = faces[fi].getIndices();
            const Point& p0 = points[idx[0]];

            auto normal = faceNormal(faces[fi], points);

            // Вектор от грани к камере
            const double vx = camPos.GetX() - p0.GetX();
            const double vy = camPos.GetY() - p0.GetY();
            const double vz = camPos.GetZ() - p0.GetZ();

            // dot(normal, view)
            const double dot = normal[0]*vx + normal[1]*vy + normal[2]*vz;
            visible[fi] = (dot > 0.0);
        }

        return visible;
    }
};

#endif //BACKFACECULLINGSTATION_HPP
