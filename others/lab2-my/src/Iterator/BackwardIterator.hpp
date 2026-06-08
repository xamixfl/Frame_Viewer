#ifndef BACKWARDITERATOR_HPP
#define BACKWARDITERATOR_HPP

#include "BackwardIterator.h"
#include "Exceptions.h"
#include "IteratorException.h"

template<typename T>
void BackwardIterator<T>::checkExpired() const {
    if (ptr.expired())
        throw ExpiredDataError(__FILE__, typeid(*this).name(), __func__);
}

template<typename T>
void BackwardIterator<T>::checkValidity() const {
    checkExpired();
    if (index < 0 || static_cast<size_type>(index) >= size)
        throw InvalidIteratorError(index, size, __FILE__, typeid(*this).name(), __func__);
}

template<typename T>
void BackwardIterator<T>::checkOverlap(const BackwardIterator<T>& other) const {
    if (ptr.lock().get() != other.ptr.lock().get())
        throw IncompatibleIteratorsError(__FILE__, typeid(*this).name(), __func__);
}

template<typename T>
template<std::integral IntType>
BackwardIterator<T>::BackwardIterator(const std::shared_ptr<T[]>& start, size_type limit, IntType i)
    : ptr(start) {
    index = static_cast<difference_type>(i);
    size = limit;
}

template<typename T>
BackwardIterator<T>::BackwardIterator(const BackwardIterator<T>& other) noexcept {
    ptr = other.ptr;
    index = other.index;
    size = other.size;
}

template<typename T>
BackwardIterator<T>& BackwardIterator<T>::operator=(const BackwardIterator<T>& other) noexcept {
    ptr = other.ptr;
    index = other.index;
    size = other.size;
    return *this;
}

template<typename T>
BackwardIterator<T>::operator bool() const noexcept {
    return !ptr.expired() && index >= 0 && static_cast<size_type>(index) < size;
}

template<typename T>
typename BackwardIterator<T>::reference BackwardIterator<T>::operator*() {
    checkValidity();
    return ptr.lock().get()[index];
}

template<typename T>
const typename BackwardIterator<T>::reference BackwardIterator<T>::operator*() const {
    checkValidity();
    return ptr.lock().get()[index];
}

template<typename T>
typename BackwardIterator<T>::pointer BackwardIterator<T>::operator->() {
    checkValidity();
    return ptr.lock().get() + index;
}

template<typename T>
const typename BackwardIterator<T>::pointer BackwardIterator<T>::operator->() const {
    checkValidity();
    return ptr.lock().get() + index;
}

template<typename T>
typename BackwardIterator<T>::reference BackwardIterator<T>::operator[](difference_type n) {
    BackwardIterator<T> tmp = *this + n;
    return *tmp;
}

template<typename T>
const typename BackwardIterator<T>::reference BackwardIterator<T>::operator[](difference_type n) const {
    BackwardIterator<T> tmp = *this + n;
    return *tmp;
}

template<typename T>
bool BackwardIterator<T>::operator==(const BackwardIterator<T>& other) const {
    checkOverlap(other);
    return index == other.index;
}

template<typename T>
auto BackwardIterator<T>::operator<=>(const BackwardIterator<T>& other) const {
    checkOverlap(other);
    return other.index <=> index;
}

template<typename T>
BackwardIterator<T>& BackwardIterator<T>::operator++() noexcept {
    --index;
    return *this;
}

template<typename T>
BackwardIterator<T> BackwardIterator<T>::operator++(int) noexcept {
    BackwardIterator<T> old = *this;
    --index;
    return old;
}

template<typename T>
BackwardIterator<T>& BackwardIterator<T>::operator--() noexcept {
    ++index;
    return *this;
}

template<typename T>
BackwardIterator<T> BackwardIterator<T>::operator--(int) noexcept {
    BackwardIterator<T> old = *this;
    ++index;
    return old;
}

template<typename T>
BackwardIterator<T>& BackwardIterator<T>::operator+=(difference_type n) noexcept {
    index -= n;
    return *this;
}

template<typename T>
BackwardIterator<T>& BackwardIterator<T>::operator-=(difference_type n) noexcept {
    index += n;
    return *this;
}

template<typename T>
BackwardIterator<T> BackwardIterator<T>::operator+(difference_type n) const noexcept {
    BackwardIterator<T> tmp(*this);
    tmp += n;
    return tmp;
}

template<typename T>
BackwardIterator<T> BackwardIterator<T>::operator-(difference_type n) const noexcept {
    BackwardIterator<T> tmp(*this);
    tmp -= n;
    return tmp;
}

template<typename T>
typename BackwardIterator<T>::difference_type BackwardIterator<T>::operator-(const BackwardIterator<T>& other) const {
    checkOverlap(other);
    return other.index - index;
}

#endif // BACKWARDITERATOR_HPP
