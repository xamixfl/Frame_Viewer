#ifndef MEMENTO_H
#define MEMENTO_H

#include <memory>
#include <vector>

#include "data/Point.h"
#include "bridge/BaseModelImpl.h"

class CameraImpl;
class CompositeObject;
class AssimpModelImpl;

class Memento {
public:
    virtual ~Memento() = 0;

protected:
    Memento() noexcept = default;
};

class ModelMemento final : public Memento {
    friend class AssimpModelImpl;
private:
    explicit ModelMemento(std::vector<Point> pts, Material mat) noexcept;

    std::vector<Point> _points;
    Material _material;
};

class CameraMemento final : public Memento {
public:
    ~CameraMemento() override = default;

private:
    friend class CameraImpl;

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

class LightMemento final : public Memento {
public:
    ~LightMemento() override = default;
private:
    friend class Light; 

    LightMemento(Point pos, float intensity) noexcept;

    Point position;
    float intensity;
};

#endif
