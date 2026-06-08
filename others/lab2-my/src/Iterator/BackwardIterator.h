#ifndef BACKWARDITERATOR_H
#define BACKWARDITERATOR_H

#include <concepts>
#include <memory>
#include <iterator>

#include "BaseIterator.h"

template<typename T>
class BackwardIterator final : public BaseIterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using iterator_concept = std::random_access_iterator_tag;
    using difference_type = BaseIterator::difference_type;
    using size_type = BaseIterator::size_type;
    using value_type = T;
    using pointer = T*;
    using reference = T&;


    BackwardIterator() = default;

    template<std::integral IntType>
    BackwardIterator(const std::shared_ptr<T[]>& start, size_type limit, IntType i);

    BackwardIterator(const BackwardIterator<T>& other) noexcept;

    ~BackwardIterator() override = default;


    BackwardIterator<T>& operator=(const BackwardIterator<T>& other) noexcept;

    [[nodiscard]] explicit operator bool() const noexcept;

    [[nodiscard]] reference operator*();
    [[nodiscard]] const reference operator*() const;

    [[nodiscard]] pointer operator->();
    [[nodiscard]] const pointer operator->() const;

    [[nodiscard]] reference operator[](difference_type n);
    [[nodiscard]] const reference operator[](difference_type n) const;

    [[nodiscard]] bool operator==(const BackwardIterator<T>& other) const;
    [[nodiscard]] auto operator<=>(const BackwardIterator<T>& other) const;

    BackwardIterator<T>& operator++() noexcept;
    BackwardIterator<T> operator++(int) noexcept;

    BackwardIterator<T>& operator--() noexcept;
    BackwardIterator<T> operator--(int) noexcept;

    BackwardIterator<T>& operator+=(difference_type n) noexcept;
    BackwardIterator<T>& operator-=(difference_type n) noexcept;

    [[nodiscard]] BackwardIterator<T> operator+(difference_type n) const noexcept;
    [[nodiscard]] BackwardIterator<T> operator-(difference_type n) const noexcept;

    [[nodiscard]] difference_type operator-(const BackwardIterator<T>& other) const;
    friend BackwardIterator<T> operator+(difference_type n, const BackwardIterator<T>& it) {
        return it + n;
    }


private:
    std::weak_ptr<T[]> ptr;

    void checkExpired() const;

    void checkValidity() const;

    void checkOverlap(const BackwardIterator<T>& other) const;
};

#include "BackwardIterator.hpp"

static_assert(std::random_access_iterator<BackwardIterator<int> >);

#endif // BACKWARDITERATOR_H
