//
// Created by nuelex on 21/05/25.
//

#include "Vec.hpp"

#include "../Exceptions/transform/VecException.hpp"

Vec& Vec::vecMul(const Vec& other)
{
    const double new_x = _y * other._z - _z * other._y;
    const double new_y = _z * other._x - _x * other._z;
    const double new_z = _x * other._y - _y * other._x;

    _x = new_x;
    _y = new_y;
    _z = new_z;

    return *this;
}

Vec Vec::vecMulConst(const Vec& other) const
{
    Vec new_vec{*this};

    new_vec.vecMul(other);

    return new_vec;
}

void Vec::normalize()
{
    if (fabs(this->value()) < EPS)
    {
        const time_t cur_time = time(nullptr);
        throw ErrorVec_invalid_vec(__FILE__, typeid(*this).name(), __LINE__, ctime(&cur_time));
    }

    *this /= this->value();
}



