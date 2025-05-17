#pragma once

#include <iterator>
#include <type_traits>

namespace cupix::foundation {
namespace detail {
// a method to identify whether a supplied type is range-based iterable.
// taken from:
// https://stackoverflow.com/questions/33379122/is-there-a-way-to-write-a-sfinae-test-of-for-eachability-of-a-type
template <typename Type>
auto is_range_based_iterable(...) -> std::false_type;

template <typename Type,
          typename Iter = typename std::decay<decltype(std::declval<Type>().begin())>::type>
auto is_range_based_iterable(int)
    -> decltype(std::declval<Type>().begin(),
                std::declval<Type>().end(),
                ++std::declval<Iter&>(),
                void(),
                std::integral_constant<
                    bool,
                    std::is_convertible<decltype(std::declval<Iter&>() != std::declval<Iter&>()),
                                        bool>::value &&
                        !std::is_void<decltype(*std::declval<Iter&>())>::value &&
                        std::is_copy_constructible<Iter>::value>{});

template <typename Type,
          typename Iter = typename std::decay<decltype(begin(std::declval<Type>()))>::type>
auto is_range_based_iterable(char)
    -> decltype(std::begin(std::declval<Type>()),
                std::end(std::declval<Type>()),
                ++std::declval<Iter&>(),
                void(),
                std::integral_constant<
                    bool,
                    std::is_convertible<decltype(std::declval<Iter&>() != std::declval<Iter&>()),
                                        bool>::value &&
                        !std::is_void<decltype(*std::declval<Iter&>())>::value &&
                        std::is_copy_constructible<Iter>::value>{});

template <typename From, typename To, typename = void>
struct is_narrowing : std::false_type {};

template <typename From, typename To>
struct is_narrowing<From, To, std::void_t<decltype(static_cast<To>(std::declval<From>()))>>
    : std::integral_constant<bool,
                             std::is_arithmetic_v<From> && std::is_arithmetic_v<To> &&
                                 ((std::is_floating_point_v<To> < std::is_floating_point_v<From>) ||
                                  (sizeof(To) < sizeof(From)))> {};

template <typename T, typename Enable = void>
struct safe_make_signed {
  using type = T;
};

template <typename T>
struct safe_make_signed<T, std::enable_if_t<std::is_integral_v<T>>> {
  using type = std::make_signed_t<T>;
};
}  // namespace detail

// a helper struct to check if a type is an iterator.
template <typename Iterator>
using iterator_value_t = typename std::iterator_traits<Iterator>::value_type;

template <typename Iterator>
using iterator_category_t = typename std::iterator_traits<Iterator>::iterator_category;

template <typename Iterator, typename = void>
struct is_iterator : std::false_type {};

template <typename Iterator>
struct is_iterator<Iterator,
                   typename std::enable_if_t<!std::is_same_v<iterator_value_t<Iterator>, void>>>
    : std::true_type {};

template <typename Iterator, typename = void>
struct is_random_access_iterator : std::false_type {};

template <typename Iterator>
struct is_random_access_iterator<
    Iterator,
    typename std::enable_if_t<
        !std::is_same_v<iterator_category_t<Iterator>, std::random_access_iterator_tag>,
        void>> : std::true_type {};

template <typename Iterator>
static constexpr bool is_iterator_v = is_iterator<Iterator>::value;

template <typename Iterator>
static constexpr bool is_random_access_iterator_v = is_random_access_iterator<Iterator>::value;

template <typename T>
struct is_range_based_iterable : decltype(detail::is_range_based_iterable<T>(0)) {};

template <typename T>
constexpr bool is_range_based_iterable_v = is_range_based_iterable<T>::value;

// a helper struct to check if a container has a reserve method.
template <typename Container, typename = void>
struct reservable : std::false_type {};

template <typename Container>
struct reservable<Container, std::void_t<decltype(Container::reserve)>> : std::true_type {};

template <typename Container>
static constexpr bool reservable_v = reservable<Container>::value;

// a value to check the first given type is the same as one of the rest.
template <typename T, typename... Args>
constexpr bool is_any_of_v = std::disjunction_v<std::is_same<T, Args>...>;

// a value to check the conversion from one type to another is narrowing.
template <typename From, typename To>
constexpr bool is_narrowing_v = detail::is_narrowing<From, To>::value;

template <typename T>
using safe_make_signed_t = typename detail::safe_make_signed<T>::type;
}  // namespace cupix::foundation
