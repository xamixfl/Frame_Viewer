#include "memento.h"


Memento::~Memento() {}


ModelMemento::ModelMemento(std::vector<Point> _points)
    : points(std::move(_points))
{}


CameraMemento::CameraMemento(Point _pos, Point _tar, Point _up)
    : pos(std::move(_pos)), tar(std::move(_tar)), up(std::move(_up))
{}


CompositeMemento::CompositeMemento(std::vector<std::shared_ptr<Memento>> _states)
    : states(std::move(_states))
{}
