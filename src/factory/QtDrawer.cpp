#include "factory/QtDrawer.h"
#include "data/Point.h"
#include "composite/Light.h"

#include <QGraphicsScene>
#include <QPainterPath>
#include <QPen>
#include <QBrush>
#include <QColor>

QtDrawer::QtDrawer(QGraphicsScene& scene, double scale) noexcept 
    : _scene(scene), 
      _scaleFactor(scale),
      _currentColor(Qt::white) {}

void QtDrawer::drawLine(const Point& p1, const Point& p2) {
    const qreal x1 = p1.getX() * _scaleFactor;
    const qreal y1 = -p1.getY() * _scaleFactor;
    const qreal x2 = p2.getX() * _scaleFactor;
    const qreal y2 = -p2.getY() * _scaleFactor;

    QPen pen(_currentColor); 
    pen.setWidth(1);
    _scene.addLine(x1, y1, x2, y2, pen);
}

void QtDrawer::setColor(float r, float g, float b) {
    _currentColor = QColor::fromRgbF(r, g, b);
}

struct Vec3 {
    float x, y, z;

    Vec3 operator+(const Vec3& v) const {
        return {x + v.x, y + v.y, z + v.z};
    }

    Vec3 cross(const Vec3& v) const {
        return {y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
    }

    float dot(const Vec3& v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    Vec3 normalized() const {
        float len = std::sqrt(x * x + y * y + z * z);
        if (len == 0.0f) return {0.0f, 0.0f, 0.0f};
        return {x / len, y / len, z / len};
    }
};

void QtDrawer::drawPolygon(const std::vector<Point>& vertices, const Material& mat) {
    if (vertices.size() < 3) return;

    // 1. Вычисление нормали полигона
    Vec3 p0{static_cast<float>(vertices[0].getX()), static_cast<float>(vertices[0].getY()), static_cast<float>(vertices[0].getZ())};
    Vec3 p1{static_cast<float>(vertices[1].getX()), static_cast<float>(vertices[1].getY()), static_cast<float>(vertices[1].getZ())};
    Vec3 p2{static_cast<float>(vertices[2].getX()), static_cast<float>(vertices[2].getY()), static_cast<float>(vertices[2].getZ())};

    Vec3 v1{p1.x - p0.x, p1.y - p0.y, p1.z - p0.z};
    Vec3 v2{p2.x - p0.x, p2.y - p0.y, p2.z - p0.z};
    Vec3 normal = v1.cross(v2).normalized();

    Vec3 center{(p0.x + p1.x + p2.x) / 3.0f, (p0.y + p1.y + p2.y) / 3.0f, (p0.z + p1.z + p2.z) / 3.0f};

    // Базовая подсветка (если свет не подключен)
    float finalR = mat.ambient[0] + mat.diffuse[0] * 0.5f; 
    float finalG = mat.ambient[1] + mat.diffuse[1] * 0.5f;
    float finalB = mat.ambient[2] + mat.diffuse[2] * 0.5f;

    Vec3 viewDir{0.0f, 0.0f, -1.0f}; 

    // Если источники света добавлены на сцену
    if (!_lights.empty()) {
        finalR = mat.ambient[0] * 0.2f; // Уменьшаем фоновый свет, чтобы блики контрастировали
        finalG = mat.ambient[1] * 0.2f;
        finalB = mat.ambient[2] * 0.2f;

        for (const auto& light : _lights) {
            Point pos = light->getPosition(); 
            float intensity = light->getIntensity();

            Vec3 lightPos{static_cast<float>(pos.getX()), static_cast<float>(pos.getY()), static_cast<float>(pos.getZ())};

            Vec3 lightDir{lightPos.x - center.x, lightPos.y - center.y, lightPos.z - center.z};
            lightDir = lightDir.normalized();

            // Диффузная составляющая (зависит от угла падения света)
            float diff = std::max(0.0f, normal.dot(lightDir));
            finalR += mat.diffuse[0] * diff * intensity;
            finalG += mat.diffuse[1] * diff * intensity;
            finalB += mat.diffuse[2] * diff * intensity;

            // Зеркальная составляющая (блики: зависит от резкости shininess и интенсивности specular)
            Vec3 halfwayDir = (lightDir + viewDir).normalized();
            float spec = std::pow(std::max(0.0f, normal.dot(halfwayDir)), mat.shininess);
            
            // Золото и металлы имеют высокий спекуляр, а матовые - нулевой
            finalR += mat.specular[0] * spec * intensity * 1.5f;
            finalG += mat.specular[1] * spec * intensity * 1.5f;
            finalB += mat.specular[2] * spec * intensity * 1.5f;
        }
    }

    QColor color = QColor::fromRgbF(
        std::clamp(finalR, 0.0f, 1.0f), 
        std::clamp(finalG, 0.0f, 1.0f), 
        std::clamp(finalB, 0.0f, 1.0f),
        std::clamp(mat.alpha, 0.0f, 1.0f)
    );

    QPainterPath path;
    path.moveTo(vertices[0].getX() * _scaleFactor, -vertices[0].getY() * _scaleFactor);
    for (size_t i = 1; i < vertices.size(); ++i) {
        path.lineTo(vertices[i].getX() * _scaleFactor, -vertices[i].getY() * _scaleFactor);
    }
    path.closeSubpath();

    QBrush brush(color);
    QPen pen(color);
    pen.setWidth(1);

    _scene.addPath(path, pen, brush);
}

void QtDrawer::setLights(const std::vector<std::shared_ptr<Light>>& lights) {
    _lights = lights;
}

void QtDrawer::clear() {
    _scene.clear();
}
