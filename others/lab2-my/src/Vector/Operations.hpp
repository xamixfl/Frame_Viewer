#ifndef OPERATIONS_HPP
#define OPERATIONS_HPP

#include "Vector.h"
#include "Concepts.h"

template<VectorElement T>
template<SupportsSummationFor<T> U>
Vector<decltype(std::declval<T>() + std::declval<U>())> Vector<T>::add(const Vector<U>& other) const {
    checkEqualSize(other.size());

    Vector<decltype(this->get(0) + other.get(0))> result(_size);
    std::ranges::transform(*this, other, result.begin(),
                           [](const_reference x, const U& y) { return x + y; });

    return result;
}

template<VectorElement T>
template<ScalarSummable<T> U>
Vector<decltype(std::declval<T>() + std::declval<U>())> Vector<T>::add(const U& other) const {
    Vector<decltype(this->get(0) + other)> result(_size);
    std::ranges::transform(*this, result.begin(),
                           [&other](const_reference x) { return x + other; });

    return result;
}

template<VectorElement T>
template<SupportsSummationFor<T> U>
Vector<T>& Vector<T>::addSelf(const Vector<U>& other) {
    checkEqualSize(other.size());
    std::ranges::transform(*this, other, this->begin(),
                           [](const_reference x, const U& y) { return x + y; });
    return *this;
}

template<VectorElement T>
template<ScalarSummable<T> U>
Vector<T>& Vector<T>::addSelf(const U& other) {
    std::ranges::transform(*this, this->begin(),
                           [&other](const_reference x) { return x + other; });
    return *this;
}

template<VectorElement T>
template<SupportsSummationFor<T> U>
Vector<decltype(std::declval<T>() + std::declval<U>())> Vector<T>::operator+(const Vector<U>& other) const {
    return add(other);
}

template<VectorElement T>
template<ScalarSummable<T> U>
Vector<decltype(std::declval<T>() + std::declval<U>())> Vector<T>::operator+(const U& other) const {
    return add(other);
}

template<VectorElement T>
template<SupportsSummationFor<T> U>
Vector<T>& Vector<T>::operator+=(const Vector<U>& other) {
    return addSelf(other);
}

template<VectorElement T>
template<ScalarSummable<T> U>
Vector<T>& Vector<T>::operator+=(const U& other) {
    return addSelf(other);
}

template<VectorElement T, ScalarSummable<T> U>
auto operator+(const U& l, const Vector<T>& r) {
    return r.add(l);
}

template<VectorElement T>
template<SupportsSubtractionFor<T> U>
Vector<decltype(std::declval<T>() - std::declval<U>())> Vector<T>::sub(const Vector<U>& other) const {
    checkEqualSize(other.size());

    Vector<decltype(this->get(0) - other.get(0))> result(_size);
    std::ranges::transform(*this, other, result.begin(),
                           [](const_reference x, const U& y) { return x - y; });

    return result;
}

template<VectorElement T>
template<ScalarSubtractable<T> U>
Vector<decltype(std::declval<T>() - std::declval<U>())> Vector<T>::sub(const U& other) const {
    Vector<decltype(this->get(0) - other)> result(_size);
    std::ranges::transform(*this, result.begin(),
                           [&other](const_reference x) { return x - other; });

    return result;
}

template<VectorElement T>
template<SupportsSubtractionFor<T> U>
Vector<T>& Vector<T>::subSelf(const Vector<U>& other) {
    checkEqualSize(other.size());
    std::ranges::transform(*this, other, this->begin(),
                           [](const_reference x, const U& y) { return x - y; });
    return *this;
}

template<VectorElement T>
template<ScalarSubtractable<T> U>
Vector<T>& Vector<T>::subSelf(const U& other) {
    std::ranges::transform(*this, this->begin(),
                           [&other](const_reference x) { return x - other; });
    return *this;
}

template<VectorElement T>
template<SupportsSubtractionFor<T> U>
Vector<decltype(std::declval<T>() - std::declval<U>())> Vector<T>::operator-(const Vector<U>& other) const {
    return sub(other);
}

template<VectorElement T>
template<ScalarSubtractable<T> U>
Vector<decltype(std::declval<T>() - std::declval<U>())> Vector<T>::operator-(const U& other) const {
    return sub(other);
}

template<VectorElement T>
template<SupportsSubtractionFor<T> U>
Vector<T>& Vector<T>::operator-=(const Vector<U>& other) {
    return subSelf(other);
}

template<VectorElement T>
template<ScalarSubtractable<T> U>
Vector<T>& Vector<T>::operator-=(const U& other) {
    return subSelf(other);
}

template<VectorElement T, ScalarSubtractable<T> U>
auto operator-(const U& l, const Vector<T>& r) {
    auto buff = Vector<U>(l, r.size());
    return buff.sub(r);
}

template<VectorElement T>
template<SupportsMultiplicationFor<T> U>
Vector<decltype(std::declval<T>() * std::declval<U>())> Vector<T>::mul(const Vector<U>& other) const {
    checkEqualSize(other.size());

    Vector<decltype(this->get(0) * other.get(0))> result(_size);
    std::ranges::transform(*this, other, result.begin(),
                           [](const_reference x, const U& y) { return x * y; });

    return result;
}

template<VectorElement T>
template<ScalarMultipliable<T> U>
Vector<decltype(std::declval<T>() * std::declval<U>())> Vector<T>::mul(const U& other) const {
    Vector<decltype(this->get(0) * other)> result(_size);
    std::ranges::transform(*this, result.begin(),
                           [&other](const_reference x) { return x * other; });

    return result;
}

template<VectorElement T>
template<SupportsMultiplicationFor<T> U>
Vector<T>& Vector<T>::mulSelf(const Vector<U>& other) {
    checkEqualSize(other.size());
    std::ranges::transform(*this, other, this->begin(),
                           [](const_reference x, const U& y) { return x * y; });
    return *this;
}

template<VectorElement T>
template<ScalarMultipliable<T> U>
Vector<T>& Vector<T>::mulSelf(const U& other) {
    std::ranges::transform(*this, this->begin(),
                           [&other](const_reference x) { return x * other; });
    return *this;
}

template<VectorElement T>
template<SupportsMultiplicationFor<T> U>
Vector<decltype(std::declval<T>() * std::declval<U>())> Vector<T>::operator*(const Vector<U>& other) const {
    return mul(other);
}

template<VectorElement T>
template<ScalarMultipliable<T> U>
Vector<decltype(std::declval<T>() * std::declval<U>())> Vector<T>::operator*(const U& other) const {
    return mul(other);
}

template<VectorElement T>
template<SupportsMultiplicationFor<T> U>
Vector<T>& Vector<T>::operator*=(const Vector<U>& other) {
    return mulSelf(other);
}

template<VectorElement T>
template<ScalarMultipliable<T> U>
Vector<T>& Vector<T>::operator*=(const U& other) {
    return mulSelf(other);
}

template<VectorElement T, ScalarMultipliable<T> U>
auto operator*(const U& l, const Vector<T>& r) {
    return r.mul(l);
}

template<VectorElement T>
template<SupportsDivisionFor<T> U>
Vector<decltype(std::declval<T>() / std::declval<U>())> Vector<T>::div(const Vector<U>& other) const {
    checkEqualSize(other.size());

    Vector<decltype(this->get(0) / other.get(0))> result(_size);
    std::ranges::transform(*this, other, result.begin(),
                           [](const_reference x, const U& y) { return x / y; });

    return result;
}

template<VectorElement T>
template<ScalarDivisible<T> U>
Vector<decltype(std::declval<T>() / std::declval<U>())> Vector<T>::div(const U& other) const {
    Vector<decltype(this->get(0) / other)> result(_size);
    std::ranges::transform(*this, result.begin(),
                           [&other](const_reference x) { return x / other; });

    return result;
}

template<VectorElement T>
template<SupportsDivisionFor<T> U>
Vector<T>& Vector<T>::divSelf(const Vector<U>& other) {
    checkEqualSize(other.size());
    std::ranges::transform(*this, other, this->begin(),
                           [](const_reference x, const U& y) { return x / y; });
    return *this;
}

template<VectorElement T>
template<ScalarDivisible<T> U>
Vector<T>& Vector<T>::divSelf(const U& other) {
    std::ranges::transform(*this, this->begin(),
                           [&other](const_reference x) { return x / other; });
    return *this;
}

template<VectorElement T>
template<SupportsDivisionFor<T> U>
Vector<decltype(std::declval<T>() / std::declval<U>())> Vector<T>::operator/(const Vector<U>& other) const {
    return div(other);
}

template<VectorElement T>
template<ScalarDivisible<T> U>
Vector<decltype(std::declval<T>() / std::declval<U>())> Vector<T>::operator/(const U& other) const {
    return div(other);
}

template<VectorElement T>
template<SupportsDivisionFor<T> U>
Vector<T>& Vector<T>::operator/=(const Vector<U>& other) {
    return divSelf(other);
}

template<VectorElement T>
template<ScalarDivisible<T> U>
Vector<T>& Vector<T>::operator/=(const U& other) {
    return divSelf(other);
}

#endif // OPERATIONS_HPP
