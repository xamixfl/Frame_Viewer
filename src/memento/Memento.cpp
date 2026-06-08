#include "memento/Memento.h"

#include <utility>

Memento::~Memento() = default;

ModelMemento::ModelMemento(std::vector<Point> pts) noexcept
    : points(std::move(pts)) {}

CameraMemento::CameraMemento(Point pos, Point dir, Point u) noexcept
    : position(pos), direction(dir), up(u) {}

CompositeMemento::CompositeMemento(std::vector<std::shared_ptr<Memento>> _states) noexcept
    : states(std::move(_states)) {}
