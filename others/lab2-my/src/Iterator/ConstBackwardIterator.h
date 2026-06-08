#ifndef CONSTBACKWARDITERATOR_H
#define CONSTBACKWARDITERATOR_H

#include <concepts>
#include <memory>
#include <iterator>

#include "BaseIterator.h"

template<typename T>
class ConstBackwardIterator final : public BaseIterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using iterator_concept = std::random_access_iterator_tag;
    using difference_type = BaseIterator::difference_type;
    using size_type = BaseIterator::size_type;
    using value_type = const T;
    using pointer = const T*;
    using reference = const T&;


    ConstBackwardIterator() = default;

    template<std::integral IntType>
    ConstBackwardIterator(const std::shared_ptr<T[]>& start, size_type limit, IntType i);

    ConstBackwardIterator(const ConstBackwardIterator<T>& other) noexcept;

    ~ConstBackwardIterator() override = default;


    ConstBackwardIterator<T>& operator=(const ConstBackwardIterator<T>& other) noexcept;

    [[nodiscard]] explicit operator bool() const noexcept;

    [[nodiscard]] reference operator*() const;

    [[nodiscard]] pointer operator->() const;

    [[nodiscard]] reference operator[](difference_type n) const;

    [[nodiscard]] bool operator==(const ConstBackwardIterator<T>& other) const;
    [[nodiscard]] auto operator<=>(const ConstBackwardIterator<T>& other) const;

    ConstBackwardIterator<T>& operator++() noexcept;
    ConstBackwardIterator<T> operator++(int) noexcept;

    ConstBackwardIterator<T>& operator--() noexcept;
    ConstBackwardIterator<T> operator--(int) noexcept;

    ConstBackwardIterator<T>& operator+=(difference_type n) noexcept;
    ConstBackwardIterator<T>& operator-=(difference_type n) noexcept;

    [[nodiscard]] ConstBackwardIterator<T> operator+(difference_type n) const noexcept;
    [[nodiscard]] ConstBackwardIterator<T> operator-(difference_type n) const noexcept;

    [[nodiscard]] difference_type operator-(const ConstBackwardIterator<T>& other) const;
    friend ConstBackwardIterator<T> operator+(difference_type n, const ConstBackwardIterator<T>& it) {
        return it + n;
    }


private:
    std::weak_ptr<T[]> ptr;

    void checkExpired() const;

    void checkValidity() const;

    void checkOverlap(const ConstBackwardIterator<T>& other) const;
};

#include "ConstBackwardIterator.hpp"

static_assert(std::random_access_iterator<ConstBackwardIterator<int> >);

#endif // CONSTBACKWARDITERATOR_H
