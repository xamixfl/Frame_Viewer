#ifndef MEMENTO_H__
#define MEMENTO_H__

#include <vector>
#include <memory>
#include "point.h"


class WireframeModelImpl;
class AdjMatrixModelImpl;
class CameraImpl;


class Memento
{
public:
    virtual ~Memento() = 0;

protected:
    Memento() = default;
};


class ModelMemento : public Memento
{
public:
    ~ModelMemento() override = default;

private:
    friend class WireframeModelImpl;
    friend class AdjMatrixModelImpl;

    explicit ModelMemento(std::vector<Point> _points);

    std::vector<Point> points;
};


class CameraMemento : public Memento
{
public:
    ~CameraMemento() override = default;

private:
    friend class CameraImpl;

    CameraMemento(Point _pos, Point _tar, Point _up);

    Point pos, tar, up;
};


class CompositeMemento : public Memento
{
public:
    ~CompositeMemento() override = default;

private:
    friend class Composite;

    explicit CompositeMemento(std::vector<std::shared_ptr<Memento>> _states);

    std::vector<std::shared_ptr<Memento>> states;
};

#endif
