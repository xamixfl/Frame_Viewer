#ifndef MEMENTO_H
#define MEMENTO_H

#include <memory>
#include <vector>

#include "data/Point.h"

class CarcasModel;
class AdjMatrixModel;
class CarcasCamera;
class CompositeObject;

class Memento {
public:
    virtual ~Memento() = 0;

protected:
    Memento() noexcept = default;
};

class ModelMemento final : public Memento {
public:
    ~ModelMemento() override = default;

private:
    friend class CarcasModel;
    friend class AdjMatrixModel;

    explicit ModelMemento(std::vector<Point> pts) noexcept;

    std::vector<Point> points;
};

class CameraMemento final : public Memento {
public:
    ~CameraMemento() override = default;

private:
    friend class CarcasCamera;

    CameraMemento(Point pos, Point dir, Point up) noexcept;

    Point position;
    Point direction;
    Point up;
};

class CompositeMemento final : public Memento {
public:
    ~CompositeMemento() override = default;

private:
    friend class CompositeObject;

    explicit CompositeMemento(std::vector<std::shared_ptr<Memento>> states) noexcept;

    std::vector<std::shared_ptr<Memento>> states;
};

#endif // MEMENTO_H
