#ifndef VECTOR_H
#define VECTOR_H

#include <initializer_list>
#include <ranges>
#include <concepts>

#include "Iterator.h"
#include "ConstIterator.h"
#include "BackwardIterator.h"
#include "ConstBackwardIterator.h"
#include "Exceptions.h"
#include "Concepts.h"
#include "BaseVector.h"

template<VectorElement T>
class Vector final : public BaseVector {
public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = BaseVector::size_type;
    using index_type = size_type;
    using iterator = Iterator<T>;
    using const_iterator = ConstIterator<T>;
    using backward_iterator = BackwardIterator<T>;
    using const_backward_iterator = ConstBackwardIterator<T>;


    template<AssignableFromInt U = T>
    static Vector<U> zeros(size_type s);


    explicit Vector(size_type s);
    explicit Vector(const Vector<T>& other);
    Vector(Vector<T>&& other) noexcept;

    template<ConvertibleVectorElement<T> U>
    explicit Vector(const Vector<U>& other);

    template<ConvertibleVectorElement<T> U>
    Vector(std::initializer_list<U> lst);

    template<ConvertibleForwardIterator<T> Iter, std::sentinel_for<Iter> Sent>
    Vector(const Iter& start, const Sent& end);

    template<ConvertibleForwardRange<T> R>
    explicit Vector(R&& r);

    Vector(const_reference val, size_type s);

    template<ConvertibleVectorElement<T> U>
    explicit Vector(const U* data, size_type sz);


    Vector<T>& operator=(const Vector<T>& other);

    Vector<T>& operator=(Vector<T>&& other) noexcept;

    template<ConvertibleVectorElement<T> U>
    Vector<T>& operator=(const Vector<U>& other);

    template<ConvertibleVectorElement<T> U>
    Vector<T>& operator=(std::initializer_list<U> lst);

    template<ConvertibleForwardRange<T> R>
    Vector<T>& operator=(R&& r);


    ~Vector() override;


    [[nodiscard]] iterator begin() noexcept;
    [[nodiscard]] iterator end() noexcept;

    [[nodiscard]] const_iterator begin() const noexcept;
    [[nodiscard]] const_iterator end() const noexcept;

    [[nodiscard]] const_iterator cbegin() const noexcept;
    [[nodiscard]] const_iterator cend() const noexcept;

    [[nodiscard]] backward_iterator rbegin() noexcept;
    [[nodiscard]] backward_iterator rend() noexcept;

    [[nodiscard]] const_backward_iterator rbegin() const noexcept;
    [[nodiscard]] const_backward_iterator rend() const noexcept;

    [[nodiscard]] const_backward_iterator crbegin() const noexcept;
    [[nodiscard]] const_backward_iterator crend() const noexcept;

    [[nodiscard]] value_type get(index_type i) const;
    void set(index_type i, const_reference val);
    void set(index_type i, value_type&& val);

    [[nodiscard]] reference at(index_type i);
    [[nodiscard]] const_reference at(index_type i) const;
    [[nodiscard]] reference operator[](index_type i);
    [[nodiscard]] const_reference operator[](index_type i) const;

    template<typename U>
    [[nodiscard]] bool isEqualTo(const Vector<U>& other) const;

    template<ConvertibleInputRange<T> R>
    [[nodiscard]] bool isEqualTo(R&& r) const;

    template<typename U>
    [[nodiscard]] bool operator==(const Vector<U>& other) const;

    template<ConvertibleInputRange<T> R>
    [[nodiscard]] bool operator==(R&& r) const;

    template<typename U>
    [[nodiscard]] bool operator!=(const Vector<U>& other) const;

    template<ConvertibleInputRange<T> R>
    [[nodiscard]] bool operator!=(R&& r) const;

    template<typename U>
    [[nodiscard]] double angleWith(const Vector<U>& other) const;

    template<typename U>
    [[nodiscard]] bool isCollinearWith(const Vector<U>& other) const;

    template<typename U>
    [[nodiscard]] bool isOrthogonalWith(const Vector<U>& other) const;

    template<ConvertibleTo<double> U = T>
    [[nodiscard]] double magnitude() const noexcept;

    template<ConvertibleTo<double> U = T>
    [[nodiscard]] bool isZero() const;

    template<ConvertibleTo<double> U = T>
    [[nodiscard]] bool isUnit() const;

    template<ConvertibleTo<double> U = T>
    Vector<T>& normalize();

    template<ConvertibleTo<double> U = T>
    [[nodiscard]] Vector<T> normalized() const;

    [[nodiscard]] Vector<T> operator-() const;

    [[nodiscard]] Vector<T> negate() const;

    template<typename U>
    [[nodiscard]] decltype(auto) dotProduct(const Vector<U>& other) const;

    template<typename U>
    [[nodiscard]] decltype(auto) operator&(const Vector<U>& other) const;

    template<typename U>
    [[nodiscard]] decltype(auto) crossProduct(const Vector<U>& other) const;

    template<typename U>
    [[nodiscard]] decltype(auto) operator^(const Vector<U>& other) const;

    template<SupportsSummationFor<T> U>
    [[nodiscard]] Vector<decltype(std::declval<T>() + std::declval<U>())> add(const Vector<U>& other) const;

    template<ScalarSummable<T> U>
    [[nodiscard]] Vector<decltype(std::declval<T>() + std::declval<U>())> add(const U& other) const;

    template<SupportsSummationFor<T> U>
    Vector<T>& addSelf(const Vector<U>& other);

    template<ScalarSummable<T> U>
    Vector<T>& addSelf(const U& other);

    template<SupportsSummationFor<T> U>
    [[nodiscard]] Vector<decltype(std::declval<T>() + std::declval<U>())> operator+(const Vector<U>& other) const;

    template<ScalarSummable<T> U>
    [[nodiscard]] Vector<decltype(std::declval<T>() + std::declval<U>())> operator+(const U& other) const;

    template<SupportsSummationFor<T> U>
    Vector& operator+=(const Vector<U>& other);

    template<ScalarSummable<T> U>
    Vector& operator+=(const U& other);

    template<SupportsSubtractionFor<T> U>
    [[nodiscard]] Vector<decltype(std::declval<T>() - std::declval<U>())> sub(const Vector<U>& other) const;

    template<ScalarSubtractable<T> U>
    [[nodiscard]] Vector<decltype(std::declval<T>() - std::declval<U>())> sub(const U& other) const;

    template<SupportsSubtractionFor<T> U>
    Vector<T>& subSelf(const Vector<U>& other);

    template<ScalarSubtractable<T> U>
    Vector<T>& subSelf(const U& other);

    template<SupportsSubtractionFor<T> U>
    [[nodiscard]] Vector<decltype(std::declval<T>() - std::declval<U>())> operator-(const Vector<U>& other) const;

    template<ScalarSubtractable<T> U>
    [[nodiscard]] Vector<decltype(std::declval<T>() - std::declval<U>())> operator-(const U& other) const;

    template<SupportsSubtractionFor<T> U>
    Vector& operator-=(const Vector<U>& other);

    template<ScalarSubtractable<T> U>
    Vector& operator-=(const U& other);

    template<SupportsMultiplicationFor<T> U>
    [[nodiscard]] Vector<decltype(std::declval<T>() * std::declval<U>())> mul(const Vector<U>& other) const;

    template<ScalarMultipliable<T> U>
    [[nodiscard]] Vector<decltype(std::declval<T>() * std::declval<U>())> mul(const U& other) const;

    template<SupportsMultiplicationFor<T> U>
    Vector<T>& mulSelf(const Vector<U>& other);

    template<ScalarMultipliable<T> U>
    Vector<T>& mulSelf(const U& other);

    template<SupportsMultiplicationFor<T> U>
    [[nodiscard]] Vector<decltype(std::declval<T>() * std::declval<U>())> operator*(const Vector<U>& other) const;

    template<ScalarMultipliable<T> U>
    [[nodiscard]] Vector<decltype(std::declval<T>() * std::declval<U>())> operator*(const U& other) const;

    template<SupportsMultiplicationFor<T> U>
    Vector& operator*=(const Vector<U>& other);

    template<ScalarMultipliable<T> U>
    Vector& operator*=(const U& other);

    template<SupportsDivisionFor<T> U>
    [[nodiscard]] Vector<decltype(std::declval<T>() / std::declval<U>())> div(const Vector<U>& other) const;

    template<ScalarDivisible<T> U>
    [[nodiscard]] Vector<decltype(std::declval<T>() / std::declval<U>())> div(const U& other) const;

    template<SupportsDivisionFor<T> U>
    Vector<T>& divSelf(const Vector<U>& other);

    template<ScalarDivisible<T> U>
    Vector<T>& divSelf(const U& other);

    template<SupportsDivisionFor<T> U>
    [[nodiscard]] Vector<decltype(std::declval<T>() / std::declval<U>())> operator/(const Vector<U>& other) const;

    template<ScalarDivisible<T> U>
    [[nodiscard]] Vector<decltype(std::declval<T>() / std::declval<U>())> operator/(const U& other) const;

    template<SupportsDivisionFor<T> U>
    Vector& operator/=(const Vector<U>& other);

    template<ScalarDivisible<T> U>
    Vector& operator/=(const U& other);


private:
    std::shared_ptr<value_type[]> vals;

    static std::shared_ptr<value_type[]> _allocate(size_type s);

    static void checkSize(size_type s);

    void checkIndex(index_type i) const;

    void checkEqualSize(size_type s) const;

    template<typename U>
    Vector<decltype(std::declval<T>() * std::declval<U>())> calculate3DCrossProduct(const Vector<U>& other) const;

    template<typename U>
    Vector<decltype(std::declval<T>() * std::declval<U>())> calculate7DCrossProduct(const Vector<U>& other) const;
};

template<VectorElement T, ScalarSummable<T> U>
auto operator+(const U& l, const Vector<T>& r);

template<VectorElement T, ScalarMultipliable<T> U>
auto operator*(const U& l, const Vector<T>& r);

template<VectorElement T, ScalarSubtractable<T> U>
auto operator-(const U& l, const Vector<T>& r);

template<ConsoleVectorElement T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vec);

static_assert(ContainerType<Vector<int>>);

template<typename U>
Vector(std::initializer_list<U>) -> Vector<U>;

#include "Constructors.hpp"
#include "Vector.hpp"
#include "Operations.hpp"

#endif // VECTOR_H
