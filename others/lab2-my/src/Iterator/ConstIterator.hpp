#ifndef CONSTITERATOR_HPP
#define CONSTITERATOR_HPP

#include "ConstIterator.h"
#include "Exceptions.h"
#include "IteratorException.h"

template<typename T>
void ConstIterator<T>::checkExpired() const {
    if (ptr.expired())
        throw ExpiredDataError(__FILE__, typeid(*this).name(), __func__);
}

template<typename T>
void ConstIterator<T>::checkValidity() const {
    checkExpired();
    if (index < 0 || static_cast<size_type>(index) >= size)
        throw InvalidIteratorError(index, size, __FILE__, typeid(*this).name(), __func__);
}

template<typename T>
void ConstIterator<T>::checkOverlap(const ConstIterator<T>& other) const {
    if (ptr.lock().get() != other.ptr.lock().get())
        throw IncompatibleIteratorsError(__FILE__, typeid(*this).name(), __func__);
}

template<typename T>
template<std::integral IntType>
ConstIterator<T>::ConstIterator(const std::shared_ptr<T[]>& start, size_type limit, IntType i)
    : ptr(start) {
    index = static_cast<difference_type>(i);
    size = limit;
}

template<typename T>
ConstIterator<T>::ConstIterator(const ConstIterator<T>& other) noexcept {
    ptr = other.ptr;
    index = other.index;
    size = other.size;
}

template<typename T>
ConstIterator<T>& ConstIterator<T>::operator=(const ConstIterator<T>& other) noexcept {
    ptr = other.ptr;
    index = other.index;
    size = other.size;
    return *this;
}

template<typename T>
ConstIterator<T>::operator bool() const noexcept {
    return !ptr.expired() && index >= 0 && static_cast<size_type>(index) < size;
}

template<typename T>
typename ConstIterator<T>::reference ConstIterator<T>::operator*() const {
    checkValidity();
    return ptr.lock().get()[index];
}

template<typename T>
typename ConstIterator<T>::pointer ConstIterator<T>::operator->() const {
    checkValidity();
    return ptr.lock().get() + index;
}

template<typename T>
typename ConstIterator<T>::reference ConstIterator<T>::operator[](difference_type n) const {
    ConstIterator<T> tmp = *this + n;
    return *tmp;
}

template<typename T>
bool ConstIterator<T>::operator==(const ConstIterator<T>& other) const {
    checkOverlap(other);
    return index == other.index;
}

template<typename T>
auto ConstIterator<T>::operator<=>(const ConstIterator<T>& other) const {
    checkOverlap(other);
    return index <=> other.index;
}

template<typename T>
ConstIterator<T>& ConstIterator<T>::operator++() noexcept {
    ++index;
    return *this;
}

template<typename T>
ConstIterator<T> ConstIterator<T>::operator++(int) noexcept {
    ConstIterator<T> old = *this;
    ++index;
    return old;
}

template<typename T>
ConstIterator<T>& ConstIterator<T>::operator--() noexcept {
    --index;
    return *this;
}

template<typename T>
ConstIterator<T> ConstIterator<T>::operator--(int) noexcept {
    ConstIterator<T> old = *this;
    --index;
    return old;
}

template<typename T>
ConstIterator<T>& ConstIterator<T>::operator+=(difference_type n) noexcept {
    index += n;
    return *this;
}

template<typename T>
ConstIterator<T>& ConstIterator<T>::operator-=(difference_type n) noexcept {
    index -= n;
    return *this;
}

template<typename T>
ConstIterator<T> ConstIterator<T>::operator+(difference_type n) const noexcept {
    ConstIterator<T> tmp(*this);
    tmp += n;
    return tmp;
}

template<typename T>
ConstIterator<T> ConstIterator<T>::operator-(difference_type n) const noexcept {
    ConstIterator<T> tmp(*this);
    tmp -= n;
    return tmp;
}

template<typename T>
typename ConstIterator<T>::difference_type ConstIterator<T>::operator-(const ConstIterator<T>& other) const {
    checkOverlap(other);
    return index - other.index;
}

#endif // CONSTITERATOR_HPP
