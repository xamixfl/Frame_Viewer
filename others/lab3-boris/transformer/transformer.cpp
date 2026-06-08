#include "transformer.h"

#include <iostream>


Transformer::Transformer(double _x, double _y, double _z)
    : x(std::move(_x)), y(std::move(_y)), z(std::move(_z))
{}

double Transformer::get_x() const { return x; }

double Transformer::get_y() const { return y; }

double Transformer::get_z() const { return z; }
