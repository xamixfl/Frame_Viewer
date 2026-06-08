#include "memento/Memento.h"

#include <utility>

Memento::~Memento() = default;

#include "memento/Memento.h"

ModelMemento::ModelMemento(std::vector<Point> pts, Material mat) noexcept
    : _points(std::move(pts)), _material(std::move(mat)) {}

CameraMemento::CameraMemento(Point pos, Point dir, Point u) noexcept
    : position(pos), direction(dir), up(u) {}

CompositeMemento::CompositeMemento(std::vector<std::shared_ptr<Memento>> _states) noexcept
    : states(std::move(_states)) {}

LightMemento::LightMemento(Point pos, float intensity) noexcept
    : position(pos), intensity(intensity) {}
