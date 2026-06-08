#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <algorithm>
#include <cfloat>
#include <cmath>
#include <numeric>
#include <ranges>

#include "Vector.h"
#include "Concepts.h"

template<VectorElement T>
Iterator<T> Vector<T>::begin() noexcept {
    return Iterator<T>(vals, _size, 0);
}

template<VectorElement T>
Iterator<T> Vector<T>::end() noexcept {
    return Iterator<T>(vals, _size, _size);
}

template<VectorElement T>
ConstIterator<T> Vector<T>::begin() const noexcept {
    return ConstIterator<T>(vals, _size, 0);
}

template<VectorElement T>
ConstIterator<T> Vector<T>::end() const noexcept {
    return ConstIterator<T>(vals, _size, _size);
}

template<VectorElement T>
ConstIterator<T> Vector<T>::cbegin() const noexcept {
    return ConstIterator<T>(vals, _size, 0);
}

template<VectorElement T>
ConstIterator<T> Vector<T>::cend() const noexcept {
    return ConstIterator<T>(vals, _size, _size);
}

template<VectorElement T>
BackwardIterator<T> Vector<T>::rbegin() noexcept {
    return BackwardIterator<T>(vals, _size, _size - 1);
}

template<VectorElement T>
BackwardIterator<T> Vector<T>::rend() noexcept {
    return BackwardIterator<T>(vals, _size, -1);
}

template<VectorElement T>
ConstBackwardIterator<T> Vector<T>::rbegin() const noexcept {
    return ConstBackwardIterator<T>(vals, _size, _size - 1);
}

template<VectorElement T>
ConstBackwardIterator<T> Vector<T>::rend() const noexcept {
    return ConstBackwardIterator<T>(vals, _size, -1);
}

template<VectorElement T>
ConstBackwardIterator<T> Vector<T>::crbegin() const noexcept {
    return ConstBackwardIterator<T>(vals, _size, _size - 1);
}

template<VectorElement T>
ConstBackwardIterator<T> Vector<T>::crend() const noexcept {
    return ConstBackwardIterator<T>(vals, _size, -1);
}

template<VectorElement T>
typename Vector<T>::value_type Vector<T>::get(index_type i) const {
    checkIndex(i);
    return vals[i];
}

template<VectorElement T>
void Vector<T>::set(index_type i, const_reference val) {
    checkIndex(i);
    vals[i] = val;
}

template<VectorElement T>
void Vector<T>::set(index_type i, value_type&& val) {
    checkIndex(i);
    vals[i] = std::move(val);
}

template<VectorElement T>
typename Vector<T>::reference Vector<T>::at(index_type i) {
    checkIndex(i);
    return vals[i];
}

template<VectorElement T>
typename Vector<T>::const_reference Vector<T>::at(index_type i) const {
    checkIndex(i);
    return vals[i];
}

template<VectorElement T>
typename Vector<T>::reference Vector<T>::operator[](index_type i) {
    checkIndex(i);
    return vals[i];
}

template<VectorElement T>
typename Vector<T>::const_reference Vector<T>::operator[](index_type i) const {
    checkIndex(i);
    return vals[i];
}

template<VectorElement T>
template<typename U>
bool Vector<T>::isEqualTo(const Vector<U>& other) const {
    if (_size != other._size)
        return false;
    return std::ranges::equal(*this, other);
}

template<VectorElement T>
template<ConvertibleInputRange<T> R>
bool Vector<T>::isEqualTo(R&& r) const {
    if constexpr (std::ranges::sized_range<R>)
        if (_size != std::ranges::size(r))
            return false;
    return std::ranges::equal(*this, r);
}

template<VectorElement T>
template<typename U>
bool Vector<T>::operator==(const Vector<U>& other) const {
    return isEqualTo(other);
}

template<VectorElement T>
template<ConvertibleInputRange<T> R>
bool Vector<T>::operator==(R&& r) const {
    return isEqualTo(r);
}

template<VectorElement T>
template<typename U>
bool Vector<T>::operator!=(const Vector<U>& other) const {
    return !isEqualTo(other);
}

template<VectorElement T>
template<ConvertibleInputRange<T> R>
bool Vector<T>::operator!=(R&& r) const {
    return !isEqualTo(r);
}

template<VectorElement T>
template<ConvertibleTo<double> U>
bool Vector<T>::isZero() const {
    return magnitude() < DBL_EPSILON;
}

template<VectorElement T>
template<ConvertibleTo<double> U>
bool Vector<T>::isUnit() const {
    return std::abs(magnitude() - 1.0) < DBL_EPSILON;
}

template<VectorElement T>
Vector<T> Vector<T>::operator-() const {
    Vector<T> result(_size);
    std::ranges::transform(*this, result.begin(), [](const_reference x) { return -x; });
    return result;
}

template<VectorElement T>
Vector<T> Vector<T>::negate() const {
    return operator-();
}

template<VectorElement T>
template<typename U>
double Vector<T>::angleWith(const Vector<U>& other) const {
    checkEqualSize(other.size());

    auto dotVal = dotProduct(other);
    auto magThis = magnitude();
    auto magOther = other.magnitude();

    if (magThis < DBL_EPSILON || magOther < DBL_EPSILON)
        throw ZeroVectorError(__FILE__, typeid(*this).name(), __func__);

    double cosTheta = std::clamp(dotVal / (magThis * magOther), -1.0, 1.0);
    return std::acos(cosTheta);
}

template<VectorElement T>
template<typename U>
bool Vector<T>::isCollinearWith(const Vector<U>& other) const {
    checkEqualSize(other.size());

    auto dotVal = dotProduct(other);
    auto magThis = magnitude();
    auto magOther = other.magnitude();

    if (magThis < DBL_EPSILON || magOther < DBL_EPSILON)
        throw ZeroVectorError(__FILE__, typeid(*this).name(), __func__);

    return std::abs(std::abs(dotVal) - magThis * magOther) < DBL_EPSILON;
}

template<VectorElement T>
template<typename U>
bool Vector<T>::isOrthogonalWith(const Vector<U>& other) const {
    checkEqualSize(other.size());
    return std::abs(dotProduct(other)) < DBL_EPSILON;
}

template<VectorElement T>
template<ConvertibleTo<double> U>
double Vector<T>::magnitude() const noexcept {
    double sum = 0.0;
    std::ranges::for_each(*this, [&sum](const_reference val) {
        sum += static_cast<double>(val) * static_cast<double>(val);
    });
    return std::sqrt(sum);
}

template<VectorElement T>
template<ConvertibleTo<double> U>
Vector<T>& Vector<T>::normalize() {
    double mag = magnitude();

    if (mag < DBL_EPSILON)
        throw ZeroVectorError(__FILE__, typeid(*this).name(), __func__);

    std::ranges::transform(*this, this->begin(), [mag](const_reference x) {
        return static_cast<value_type>(x / mag);
    });

    return *this;
}

template<VectorElement T>
template<ConvertibleTo<double> U>
Vector<T> Vector<T>::normalized() const{
    double mag = magnitude();

    if (mag < DBL_EPSILON)
        throw ZeroVectorError(__FILE__, typeid(*this).name(), __func__);

    Vector<T> result(_size);
    std::ranges::transform(*this, result.begin(), [&mag](const_reference x) {
        return static_cast<value_type>(x / mag);
    });

    return result;
}

template<VectorElement T>
template<typename U>
decltype(auto) Vector<T>::dotProduct(const Vector<U>& other) const {
    checkEqualSize(other.size());

    decltype(auto) result = get(0) * other.get(0);
    auto indices = std::views::iota(static_cast<size_type>(1), _size);
    std::ranges::for_each(indices, [this, &other, &result](size_type i) {
        result += get(i) * other.get(i);
    });

    return result;
}

template<VectorElement T>
template<typename U>
decltype(auto) Vector<T>::operator&(const Vector<U>& other) const {
    return dotProduct(other);
}

template<VectorElement T>
template<typename U>
decltype(auto) Vector<T>::crossProduct(const Vector<U>& other) const {
    checkEqualSize(other.size());

    if (_size != 3 && _size != 7)
        throw InvalidDimForCrossProductError(__FILE__, typeid(*this).name(), __func__);

    Vector<decltype(at(0) * other.at(0))> result(_size);

    if (_size == 3)
        result = calculate3DCrossProduct(other);
    else
        result = calculate7DCrossProduct(other);

    return result;
}

template<VectorElement T>
template<typename U>
Vector<decltype(std::declval<T>() * std::declval<U>())> Vector<T>::calculate3DCrossProduct(const Vector<U>& other) const {
    return {
        at(1) * other.at(2) - at(2) * other.at(1),
        at(2) * other.at(0) - at(0) * other.at(2),
        at(0) * other.at(1) - at(1) * other.at(0)
    };
}

template<VectorElement T>
template<typename U>
Vector<decltype(std::declval<T>() * std::declval<U>())> Vector<T>::calculate7DCrossProduct(const Vector<U>& other) const {
    return {
        at(1) * other.at(2) - at(2) * other.at(1) + at(3) * other.at(4) - at(4) * other.at(3) + at(5)
        * other.at(6) - at(6) * other.at(5),
        at(2) * other.at(0) - at(0) * other.at(2) + at(4) * other.at(5) - at(5) * other.at(4) + at(6)
        * other.at(3) - at(3) * other.at(6),
        at(0) * other.at(1) - at(1) * other.at(0) + at(4) * other.at(6) - at(6) * other.at(4) + at(5)
        * other.at(3) - at(3) * other.at(5),
        at(1) * other.at(4) - at(4) * other.at(1) + at(2) * other.at(5) - at(5) * other.at(2) + at(6)
        * other.at(0) - at(0) * other.at(6),
        at(0) * other.at(3) - at(3) * other.at(0) + at(2) * other.at(6) - at(6) * other.at(2) + at(1)
        * other.at(5) - at(5) * other.at(1),
        at(1) * other.at(6) - at(6) * other.at(1) + at(3) * other.at(0) - at(0) * other.at(3) + at(4)
        * other.at(2) - at(2) * other.at(4),
        at(0) * other.at(5) - at(5) * other.at(0) + at(3) * other.at(2) - at(2) * other.at(3) + at(6)
        * other.at(4) - at(4) * other.at(6)
    };
}

template<VectorElement T>
template<typename U>
decltype(auto) Vector<T>::operator^(const Vector<U>& other) const {
    return crossProduct(other);
}

template<ConsoleVectorElement T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
    os << '(';
    if (vec.size() > 0) {
        os << vec[0];
        auto indices = std::views::iota(static_cast<size_t>(1), vec.size());
        std::ranges::for_each(indices, [&os, &vec](size_t i) {
            os << ", " << vec[i];
        });
    }
    os << ')';
    return os;
}

#endif // VECTOR_HPP
