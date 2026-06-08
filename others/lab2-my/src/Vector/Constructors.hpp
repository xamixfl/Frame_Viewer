#ifndef CONSTRUCTORS_HPP
#define CONSTRUCTORS_HPP

#include <algorithm>
#include <ranges>
#include <cstring>

#include "Vector.h"
#include "Concepts.h"

template<VectorElement T>
template<AssignableFromInt U>
Vector<U> Vector<T>::zeros(const size_type s) {
    checkSize(s);

    Vector<U> result(s);
    std::ranges::fill(result, static_cast<typename Vector<U>::value_type>(0));

    return result;
}

template<VectorElement T>
Vector<T>::Vector(const size_type s) {
    checkSize(s);

    _size = s;
    vals = _allocate(_size);
}

template<VectorElement T>
Vector<T>::Vector(const Vector<T>& other) {
    _size = other._size;
    vals = _allocate(_size);
    std::ranges::copy(other, begin());
}

template<VectorElement T>
Vector<T>::Vector(Vector<T>&& other) noexcept {
    _size = other._size;
    vals = other.vals;
    other.vals.reset();
    other._size = 0;
}

template<VectorElement T>
template<ConvertibleVectorElement<T> U>
Vector<T>::Vector(const Vector<U>& other) {
    _size = other.size();
    vals = _allocate(_size);
    std::ranges::copy(other, begin());
}

template<VectorElement T>
template<ConvertibleVectorElement<T> U>
Vector<T>::Vector(std::initializer_list<U> lst) {
    checkSize(lst.size());

    _size = lst.size();
    vals = _allocate(_size);
    std::ranges::copy(lst, begin());
}

template<VectorElement T>
template<ConvertibleForwardIterator<T> Iter, std::sentinel_for<Iter> Sent>
Vector<T>::Vector(const Iter& start, const Sent& end) {
    const size_t sz = std::distance(start, end);
    checkSize(sz);

    _size = sz;
    vals = _allocate(_size);
    std::ranges::copy(start, end, begin());
}

template<VectorElement T>
template<ConvertibleForwardRange<T> R>
Vector<T>::Vector(R&& r) {
    const size_t sz = std::ranges::distance(r);
    checkSize(sz);

    _size = sz;
    vals = _allocate(_size);
    std::ranges::copy(std::forward<R>(r), begin());
}

template<VectorElement T>
Vector<T>::Vector(const_reference val, const size_type s) {
    checkSize(s);

    _size = s;
    vals = _allocate(_size);
    std::ranges::fill(*this, val);
}

template<VectorElement T>
template<ConvertibleVectorElement<T> U>
Vector<T>::Vector(const U* data, size_type sz) {
    if (data == nullptr)
        throw ArgValueError("Data pointer is NULL", __FILE__, typeid(*this).name(), __func__);
    checkSize(sz);

    _size = sz;
    vals = _allocate(_size);
    std::ranges::copy(data, data + _size, begin());
}

template<VectorElement T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
    if (this == &other)
        return *this;

    _size = other._size;
    vals = _allocate(_size);
    std::ranges::copy(other, begin());
    return *this;
}

template<VectorElement T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) noexcept {
    if (this == &other)
        return *this;

    _size = other._size;
    vals = other.vals;
    other.vals.reset();
    other._size = 0;
    return *this;
}

template<VectorElement T>
template<ConvertibleVectorElement<T> U>
Vector<T>& Vector<T>::operator=(const Vector<U>& other) {
    checkSize(other.size());

    _size = other.size();
    vals = _allocate(_size);
    std::ranges::copy(other, begin());
    return *this;
}

template<VectorElement T>
template<ConvertibleVectorElement<T> U>
Vector<T>& Vector<T>::operator=(std::initializer_list<U> lst) {
    checkSize(lst.size());

    _size = lst.size();
    vals = _allocate(_size);
    std::ranges::copy(lst, begin());
    return *this;
}

template<VectorElement T>
template<ConvertibleForwardRange<T> R>
Vector<T>& Vector<T>::operator=(R&& r) {
    const size_t sz = std::ranges::distance(r);
    checkSize(sz);

    _size = sz;
    vals = _allocate(_size);
    std::ranges::copy(std::forward<R>(r), begin());
    return *this;
}

template<VectorElement T>
Vector<T>::~Vector() {
    vals.reset();
}

template<VectorElement T>
void Vector<T>::checkIndex(index_type i) const {
    if (i >= _size)
        throw IndexError(i, _size, __FILE__, typeid(*this).name(), __func__);
}

template<VectorElement T>
void Vector<T>::checkEqualSize(size_type s) const {
    if (_size != s)
        throw VectorDiffDimsError(__FILE__, typeid(*this).name(), __func__);
}

template<VectorElement T>
std::shared_ptr<typename Vector<T>::value_type[]> Vector<T>::_allocate(const size_type s) {
    try {
        return std::make_shared<value_type[]>(s);
    } catch (const std::bad_alloc&) {
        throw MemoryError(__FILE__, typeid(Vector<T>).name(), __func__);
    }
}

template<VectorElement T>
void Vector<T>::checkSize(size_type s) {
    if (s == 0)
        throw ZeroVectorSizeError(__FILE__, typeid(Vector<T>).name(), __func__);
}

#endif // CONSTRUCTORS_HPP
