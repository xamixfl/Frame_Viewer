#ifndef CONSTITERATOR_H
#define CONSTITERATOR_H

#include <concepts>
#include <memory>
#include <iterator>

#include "BaseIterator.h"

template<typename T>
class ConstIterator final : public BaseIterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using iterator_concept = std::random_access_iterator_tag;
    using difference_type = BaseIterator::difference_type;
    using size_type = BaseIterator::size_type;
    using value_type = const T;
    using pointer = const T*;
    using reference = const T&;


    ConstIterator() = default;

    template<std::integral IntType>
    ConstIterator(const std::shared_ptr<T[]>& start, size_type limit, IntType i);

    ConstIterator(const ConstIterator<T>& other) noexcept;

    ~ConstIterator() override = default;


    ConstIterator<T>& operator=(const ConstIterator<T>& other) noexcept;

    [[nodiscard]] explicit operator bool() const noexcept;

    [[nodiscard]] reference operator*() const;

    [[nodiscard]] pointer operator->() const;

    [[nodiscard]] reference operator[](difference_type n) const;

    [[nodiscard]] bool operator==(const ConstIterator<T>& other) const;
    [[nodiscard]] auto operator<=>(const ConstIterator<T>& other) const;

    ConstIterator<T>& operator++() noexcept;
    ConstIterator<T> operator++(int) noexcept;

    ConstIterator<T>& operator--() noexcept;
    ConstIterator<T> operator--(int) noexcept;

    ConstIterator<T>& operator+=(difference_type n) noexcept;
    ConstIterator<T>& operator-=(difference_type n) noexcept;

    [[nodiscard]] ConstIterator<T> operator+(difference_type n) const noexcept;
    [[nodiscard]] ConstIterator<T> operator-(difference_type n) const noexcept;

    [[nodiscard]] difference_type operator-(const ConstIterator<T>& other) const;
    friend ConstIterator<T> operator+(difference_type n, const ConstIterator<T>& it) {
        return it + n;
    }


private:
    std::weak_ptr<T[]> ptr;

    void checkExpired() const;

    void checkValidity() const;

    void checkOverlap(const ConstIterator<T>& other) const;
};

#include "ConstIterator.hpp"

static_assert(std::random_access_iterator<ConstIterator<int> >);

#endif // CONSTITERATOR_H
