#ifndef CONSTBACKWARDITERATOR_HPP
#define CONSTBACKWARDITERATOR_HPP

#include "ConstBackwardIterator.h"
#include "Exceptions.h"
#include "IteratorException.h"

template<typename T>
void ConstBackwardIterator<T>::checkExpired() const {
    if (ptr.expired())
        throw ExpiredDataError(__FILE__, typeid(*this).name(), __func__);
}

template<typename T>
void ConstBackwardIterator<T>::checkValidity() const {
    checkExpired();
    if (index < 0 || static_cast<size_type>(index) >= size)
        throw InvalidIteratorError(index, size, __FILE__, typeid(*this).name(), __func__);
}

template<typename T>
void ConstBackwardIterator<T>::checkOverlap(const ConstBackwardIterator<T>& other) const {
    if (ptr.lock().get() != other.ptr.lock().get())
        throw IncompatibleIteratorsError(__FILE__, typeid(*this).name(), __func__);
}

template<typename T>
template<std::integral IntType>
ConstBackwardIterator<T>::ConstBackwardIterator(const std::shared_ptr<T[]>& start, size_type limit, IntType i)
    : ptr(start) {
    index = static_cast<difference_type>(i);
    size = limit;
}

template<typename T>
ConstBackwardIterator<T>::ConstBackwardIterator(const ConstBackwardIterator<T>& other) noexcept {
    ptr = other.ptr;
    index = other.index;
    size = other.size;
}

template<typename T>
ConstBackwardIterator<T>& ConstBackwardIterator<T>::operator=(const ConstBackwardIterator<T>& other) noexcept {
    ptr = other.ptr;
    index = other.index;
    size = other.size;
    return *this;
}

template<typename T>
ConstBackwardIterator<T>::operator bool() const noexcept {
    return !ptr.expired() && index >= 0 && static_cast<size_type>(index) < size;
}

template<typename T>
typename ConstBackwardIterator<T>::reference ConstBackwardIterator<T>::operator*() const {
    checkValidity();
    return ptr.lock().get()[index];
}

template<typename T>
typename ConstBackwardIterator<T>::pointer ConstBackwardIterator<T>::operator->() const {
    checkValidity();
    return ptr.lock().get() + index;
}

template<typename T>
typename ConstBackwardIterator<T>::reference ConstBackwardIterator<T>::operator[](difference_type n) const {
    ConstBackwardIterator<T> tmp = *this + n;
    return *tmp;
}

template<typename T>
bool ConstBackwardIterator<T>::operator==(const ConstBackwardIterator<T>& other) const {
    checkOverlap(other);
    return index == other.index;
}

template<typename T>
auto ConstBackwardIterator<T>::operator<=>(const ConstBackwardIterator<T>& other) const {
    checkOverlap(other);
    return other.index <=> index;
}

template<typename T>
ConstBackwardIterator<T>& ConstBackwardIterator<T>::operator++() noexcept {
    --index;
    return *this;
}

template<typename T>
ConstBackwardIterator<T> ConstBackwardIterator<T>::operator++(int) noexcept {
    ConstBackwardIterator<T> old = *this;
    --index;
    return old;
}

template<typename T>
ConstBackwardIterator<T>& ConstBackwardIterator<T>::operator--() noexcept {
    ++index;
    return *this;
}

template<typename T>
ConstBackwardIterator<T> ConstBackwardIterator<T>::operator--(int) noexcept {
    ConstBackwardIterator<T> old = *this;
    ++index;
    return old;
}

template<typename T>
ConstBackwardIterator<T>& ConstBackwardIterator<T>::operator+=(difference_type n) noexcept {
    index -= n;
    return *this;
}

template<typename T>
ConstBackwardIterator<T>& ConstBackwardIterator<T>::operator-=(difference_type n) noexcept {
    index += n;
    return *this;
}

template<typename T>
ConstBackwardIterator<T> ConstBackwardIterator<T>::operator+(difference_type n) const noexcept {
    ConstBackwardIterator<T> tmp(*this);
    tmp += n;
    return tmp;
}

template<typename T>
ConstBackwardIterator<T> ConstBackwardIterator<T>::operator-(difference_type n) const noexcept {
    ConstBackwardIterator<T> tmp(*this);
    tmp -= n;
    return tmp;
}

template<typename T>
typename ConstBackwardIterator<T>::difference_type ConstBackwardIterator<T>::operator-(
    const ConstBackwardIterator<T>& other) const {
    checkOverlap(other);
    return other.index - index;
}

#endif // CONSTBACKWARDITERATOR_HPP
