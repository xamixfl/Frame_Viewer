#ifndef ITERATOR_H
#define ITERATOR_H

#include <concepts>
#include <memory>
#include <iterator>

#include "BaseIterator.h"

template<typename T>
class Iterator final : public BaseIterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using iterator_concept = std::random_access_iterator_tag;
    using difference_type = BaseIterator::difference_type;
    using size_type = BaseIterator::size_type;
    using value_type = T;
    using pointer = T*;
    using reference = T&;


    Iterator() = default;

    template<std::integral IntType>
    Iterator(const std::shared_ptr<T[]>& start, size_type limit, IntType i);

    Iterator(const Iterator<T>& other) noexcept;

    ~Iterator() override = default;


    Iterator<T>& operator=(const Iterator<T>& other) noexcept;

    [[nodiscard]] explicit operator bool() const noexcept;

    [[nodiscard]] reference operator*();
    [[nodiscard]] const reference operator*() const;

    [[nodiscard]] pointer operator->();
    [[nodiscard]] const pointer operator->() const;

    [[nodiscard]] reference operator[](difference_type n);
    [[nodiscard]] const reference operator[](difference_type n) const;

    [[nodiscard]] bool operator==(const Iterator<T>& other) const;
    [[nodiscard]] auto operator<=>(const Iterator<T>& other) const;

    Iterator<T>& operator++() noexcept;
    Iterator<T> operator++(int) noexcept;

    Iterator<T>& operator--() noexcept;
    Iterator<T> operator--(int) noexcept;

    Iterator<T>& operator+=(difference_type n) noexcept;
    Iterator<T>& operator-=(difference_type n) noexcept;

    [[nodiscard]] Iterator<T> operator+(difference_type n) const noexcept;
    [[nodiscard]] Iterator<T> operator-(difference_type n) const noexcept;

    [[nodiscard]] difference_type operator-(const Iterator<T>& other) const;
    friend Iterator<T> operator+(difference_type n, const Iterator<T>& it) {
        return it + n;
    }


private:
    std::weak_ptr<T[]> ptr;

    void checkExpired() const;

    void checkValidity() const;

    void checkOverlap(const Iterator<T>& other) const;
};

#include "Iterator.hpp"

static_assert(std::random_access_iterator<Iterator<int> >);

#endif // ITERATOR_H
