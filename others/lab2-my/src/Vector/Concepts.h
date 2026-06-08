#ifndef CONCEPTS_H
#define CONCEPTS_H

#include <concepts>
#include <iostream>
#include <type_traits>

template<typename T>
concept VectorElement = std::is_default_constructible_v<T> && std::is_copy_assignable_v<T>;

template<VectorElement T>
class Vector;

template<typename T>
struct IsVector : std::false_type {
};

template<typename T>
struct IsVector<Vector<T>> : std::true_type {
};

template<typename T>
concept Scalar = !IsVector<std::remove_cvref_t<T> >::value;

template<typename U, typename T>
concept SupportsSummationFor = requires(const T& t, const U& u) {
    { t + u };
};

template<typename U, typename T>
concept SupportsSubtractionFor = requires(const T& t, const U& u) {
    { t - u };
};

template<typename U, typename T>
concept SupportsMultiplicationFor = requires(const T& t, const U& u) {
    { t * u };
};

template<typename U, typename T>
concept SupportsDivisionFor = requires(const T& t, const U& u) {
    { t / u };
};

template<typename U, typename T>
concept SupportsSumMulFor = SupportsSummationFor<U, T> && SupportsMultiplicationFor<U, T>;

template<typename T>
concept Console = requires(std::ostream& s, const T& t) {
    { s << t } -> std::same_as<std::ostream&>;
};

template<typename U, typename T>
concept ConvertibleVectorElement = VectorElement<U> && std::convertible_to<U, T>;

template<typename Iter, typename T>
concept ConvertibleForwardIterator = std::forward_iterator<Iter> && std::convertible_to<std::iter_value_t<Iter>, T>;

template<typename Container, typename T>
concept ConvertibleForwardRange = std::ranges::forward_range<Container> &&
                                  std::convertible_to<std::ranges::range_value_t<Container>, T> &&
                                  !IsVector<std::remove_cvref_t<Container>>::value;

template<typename Container, typename T>
concept ConvertibleInputRange = std::ranges::input_range<Container> &&
                                std::convertible_to<std::ranges::range_value_t<Container>, T> &&
                                !IsVector<std::remove_cvref_t<Container>>::value;

template<typename U, typename T>
concept ScalarSummable = Scalar<U> && SupportsSummationFor<U, T>;

template<typename U, typename T>
concept ScalarSubtractable = Scalar<U> && SupportsSubtractionFor<U, T>;

template<typename U, typename T>
concept ScalarMultipliable = Scalar<U> && SupportsMultiplicationFor<U, T>;

template<typename U, typename T>
concept ScalarDivisible = Scalar<U> && SupportsDivisionFor<U, T>;

template<typename U, typename T>
concept ConvertibleTo = std::convertible_to<U, T>;

template<typename T>
concept AssignableFromInt = std::assignable_from<T&, int>;

template<typename T>
concept ConsoleVectorElement = VectorElement<T> && Console<T>;

template<typename Container>
concept ContainerType = requires(Container c) {
    typename Container::value_type;
    typename Container::size_type;
    typename Container::iterator;
    typename Container::const_iterator;
    { c.size() } -> std::same_as<typename Container::size_type>;
    { c.begin() } -> std::same_as<typename Container::iterator>;
    { c.end() } -> std::same_as<typename Container::iterator>;
    { c.cbegin() } -> std::same_as<typename Container::const_iterator>;
    { c.cend() } -> std::same_as<typename Container::const_iterator>;
};

#endif // CONCEPTS_H
