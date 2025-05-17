#pragma once

#include "detail/tuplet.h"

namespace cupix::foundation {
template <typename T, size_t Size>
class Tuple : public detail::Tuplet<T, Size> {
  using Base = detail::Tuplet<T, Size>;

  __UseTupletDirectiveAliases(Base);

 public:
  constexpr auto contains(const value_type& x) const noexcept {
    return Base::template contains_<0>(x);
  }

  constexpr auto every(const value_type& x) const noexcept { return Base::template every_<0>(x); }

  constexpr auto indexof(const value_type& x) const noexcept {
    return Base::template indexof_<0>(x);
  }

 public:
  constexpr bool operator==(const Tuple& rhs) const noexcept {
    return Base::template equalAt_<0>(rhs);
  }

  constexpr bool operator!=(const Tuple& rhs) const noexcept {
    return Base::template notEqualAt_<0>(rhs);
  }

  constexpr bool operator<(const Tuple& rhs) const noexcept {
    return Base::template lessThan_<Size>(rhs);
  }

  constexpr void reverse() noexcept { Base::template swapAt_<0>(); }

  [[nodiscard]] constexpr Tuple reversed() const noexcept {
    Tuple rhs;
    Base::template swappedCopyAt_<0>(rhs);
    return rhs;
  }

 public:
  constexpr Tuple() = default;

  constexpr Tuple(const Tuple& rhs) = default;

  template <typename U>
  constexpr explicit Tuple(const Tuple<U, Size>& rhs) noexcept {
    Base::template assignForceAt_<0, U>(rhs);
  }

  template <size_t N = Size, std::enable_if_t<N == 1, int> = 0>
  constexpr Tuple(const T& v0) : data_{v0} {}

  template <size_t N = Size, std::enable_if_t<N == 2, int> = 0>
  constexpr Tuple(const T& v0, const T& v1) : data_{v0, v1} {}

  template <size_t N = Size, std::enable_if_t<N == 3, int> = 0>
  constexpr Tuple(const T& v0, const T& v1, const T& v2) : data_{v0, v1, v2} {}

  template <size_t N = Size, std::enable_if_t<N == 4, int> = 0>
  constexpr Tuple(const T& v0, const T& v1, const T& v2, const T& v3) : data_{v0, v1, v2, v3} {}

  template <size_t N = Size, std::enable_if_t<N == 5, int> = 0>
  constexpr Tuple(const T& v0, const T& v1, const T& v2, const T& v3, const T& v4)
      : data_{v0, v1, v2, v3, v4} {}

  template <size_t N = Size, std::enable_if_t<N == 6, int> = 0>
  constexpr Tuple(const T& v0, const T& v1, const T& v2, const T& v3, const T& v4, const T& v5)
      : data_{v0, v1, v2, v3, v4, v5} {}

  template <size_t N = Size, std::enable_if_t<N == 7, int> = 0>
  constexpr Tuple(const T& v0,
                  const T& v1,
                  const T& v2,
                  const T& v3,
                  const T& v4,
                  const T& v5,
                  const T& v6)
      : data_{v0, v1, v2, v3, v4, v5, v6} {}

  template <size_t N = Size, std::enable_if_t<N == 8, int> = 0>
  constexpr Tuple(const T& v0,
                  const T& v1,
                  const T& v2,
                  const T& v3,
                  const T& v4,
                  const T& v5,
                  const T& v6,
                  const T& v7)
      : data_{v0, v1, v2, v3, v4, v5, v6, v7} {}

  // Tuple(std::initializer_list<value_type> ilist) : Tuple() {
  //   auto first = data_, last = data_ + Size;
  //   for (auto it = ilist.begin(); it != ilist.end() && first != last; ++it, ++first) {
  //     *first = *it;
  //   }
  // }

  // template <typename U, std::enable_if_t<std::is_convertible_v<U, value_type>, bool> = true>
  // Tuple(std::initializer_list<U> ilist) : Tuple() {
  //   auto first = data_, last = data_ + Size;
  //   for (auto it = ilist.begin(); it != ilist.end() && first != last; ++it, ++first) {
  //     *first = value_type(*it);
  //   }
  // }

  constexpr Tuple& operator=(const Tuple& rhs) = default;

  template <typename U>
  constexpr Tuple& operator=(const Tuple<U, Size>& rhs) noexcept {
    Base::template assignAt_<0, U>(rhs);
    return *this;
  }

  template <typename U, std::enable_if_t<std::is_convertible_v<U, value_type>, bool> = true>
  Tuple& operator=(std::initializer_list<U> ilist) {
    auto first = data_, last = data_ + Size;
    for (auto it = ilist.begin(); it != ilist.end() && first != last; ++it, ++first) {
      *first = *it;
    }

    while (first != last) {
      *(first++) = value_type();
    }

    return *this;
  }

 private:
  T data_[Size] = {};
};

template <typename T>
using Single = Tuple<T, 1>;

template <typename T>
using Pair = Tuple<T, 2>;

template <typename T>
using Triple = Tuple<T, 3>;

template <typename T>
using Quad = Tuple<T, 4>;

template <typename T1, typename T2>
auto makePair(T1&& v1, T2&& v2) {
  return Pair<std::common_type_t<std::decay_t<T1>, std::decay_t<T2>>>(v1, v2);
}

template <typename T1, typename T2, typename T3>
auto makeTriple(T1&& v1, T2&& v2, T3&& v3) {
  return Triple<std::common_type_t<std::decay_t<T1>, std::decay_t<T2>, std::decay_t<T3>>>(v1, v2,
                                                                                          v3);
}

template <typename T1, typename T2, typename T3, typename T4>
auto makeQuad(T1&& v1, T2&& v2, T3&& v3, T4&& v4) {
  return Quad<
      std::common_type_t<std::decay_t<T1>, std::decay_t<T2>, std::decay_t<T3>, std::decay_t<T4>>>(
      v1, v2, v3, v4);
}

template <typename... Args>
auto makeTuple(Args&&... args) {
  return Tuple<std::common_type_t<std::decay_t<Args>...>, sizeof...(Args)>(
      std::forward<Args>(args)...);
}
}  // namespace cupix::foundation

// support structured bindings
namespace std {
template <size_t Index, typename T, size_t Size>
[[nodiscard]] constexpr const T& get(const cupix::foundation::Tuple<T, Size>& tuple) noexcept {
  return tuple.template get<Index>();
}

template <size_t Index, typename T, size_t Size>
[[nodiscard]] constexpr T& get(cupix::foundation::Tuple<T, Size>& tuple) noexcept {
  return tuple.template get<Index>();
}

template <size_t Index, typename T, size_t Size>
[[nodiscard]] constexpr T&& get(cupix::foundation::Tuple<T, Size>&& tuple) noexcept {
  return tuple.template get<Index>();
}

template <typename T, size_t Size>
struct tuple_size<cupix::foundation::Tuple<T, Size>> : std::integral_constant<size_t, Size> {};

template <typename T, size_t Size>
struct tuple_element<0, cupix::foundation::Tuple<T, Size>> {
  using type = T;
};

template <typename T, size_t Size>
struct tuple_element<1, cupix::foundation::Tuple<T, Size>> {
  using type = T;
};

template <typename T, size_t Size>
struct tuple_element<2, cupix::foundation::Tuple<T, Size>> {
  using type = T;
};

template <typename T, size_t Size>
struct tuple_element<3, cupix::foundation::Tuple<T, Size>> {
  using type = T;
};
}  // namespace std
