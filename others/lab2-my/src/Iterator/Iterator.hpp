#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "Iterator.h"
#include "Exceptions.h"
#include "IteratorException.h"

template<typename T>
void Iterator<T>::checkExpired() const {
    if (ptr.expired())
        throw ExpiredDataError(__FILE__, typeid(*this).name(), __func__);
}

template<typename T>
void Iterator<T>::checkValidity() const {
    checkExpired();
    if (index < 0 || static_cast<size_type>(index) >= size)
        throw InvalidIteratorError(index, size, __FILE__, typeid(*this).name(), __func__);
}

template<typename T>
void Iterator<T>::checkOverlap(const Iterator<T>& other) const {
    if (ptr.lock().get() != other.ptr.lock().get())
        throw IncompatibleIteratorsError(__FILE__, typeid(*this).name(), __func__);
}

template<typename T>
template<std::integral IntType>
Iterator<T>::Iterator(const std::shared_ptr<T[]>& start, size_type limit, IntType i)
    : ptr(start) {
    index = static_cast<difference_type>(i);
    size = limit;
}

template<typename T>
Iterator<T>::Iterator(const Iterator<T>& other) noexcept {
    ptr = other.ptr;
    index = other.index;
    size = other.size;
}

template<typename T>
Iterator<T>& Iterator<T>::operator=(const Iterator<T>& other) noexcept {
    ptr = other.ptr;
    index = other.index;
    size = other.size;
    return *this;
}

template<typename T>
Iterator<T>::operator bool() const noexcept {
    return !ptr.expired() && index >= 0 && static_cast<size_type>(index) < size;
}

template<typename T>
typename Iterator<T>::reference Iterator<T>::operator*() {
    checkValidity();
    return ptr.lock().get()[index];
}

template<typename T>
const typename Iterator<T>::reference Iterator<T>::operator*() const {
    checkValidity();
    return ptr.lock().get()[index];
}

template<typename T>
typename Iterator<T>::pointer Iterator<T>::operator->() {
    checkValidity();
    return ptr.lock().get() + index;
}

template<typename T>
const typename Iterator<T>::pointer Iterator<T>::operator->() const {
    checkValidity();
    return ptr.lock().get() + index;
}

template<typename T>
typename Iterator<T>::reference Iterator<T>::operator[](difference_type n) {
    Iterator<T> tmp = *this + n;
    return *tmp;
}

template<typename T>
const typename Iterator<T>::reference Iterator<T>::operator[](difference_type n) const {
    Iterator<T> tmp = *this + n;
    return *tmp;
}

template<typename T>
bool Iterator<T>::operator==(const Iterator<T>& other) const {
    checkOverlap(other);
    return index == other.index;
}

template<typename T>
auto Iterator<T>::operator<=>(const Iterator<T>& other) const {
    checkOverlap(other);
    return index <=> other.index;
}

template<typename T>
Iterator<T>& Iterator<T>::operator++() noexcept {
    ++index;
    return *this;
}

template<typename T>
Iterator<T> Iterator<T>::operator++(int) noexcept {
    Iterator<T> old = *this;
    ++index;
    return old;
}

template<typename T>
Iterator<T>& Iterator<T>::operator--() noexcept {
    --index;
    return *this;
}

template<typename T>
Iterator<T> Iterator<T>::operator--(int) noexcept {
    Iterator<T> old = *this;
    --index;
    return old;
}

template<typename T>
Iterator<T>& Iterator<T>::operator+=(difference_type n) noexcept {
    index += n;
    return *this;
}

template<typename T>
Iterator<T>& Iterator<T>::operator-=(difference_type n) noexcept {
    index -= n;
    return *this;
}

template<typename T>
Iterator<T> Iterator<T>::operator+(difference_type n) const noexcept {
    Iterator<T> tmp(*this);
    tmp += n;
    return tmp;
}

template<typename T>
Iterator<T> Iterator<T>::operator-(difference_type n) const noexcept {
    Iterator<T> tmp(*this);
    tmp -= n;
    return tmp;
}

template<typename T>
typename Iterator<T>::difference_type Iterator<T>::operator-(const Iterator<T>& other) const {
    checkOverlap(other);
    return index - other.index;
}

#endif // ITERATOR_HPP
