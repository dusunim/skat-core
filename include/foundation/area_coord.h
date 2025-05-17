#pragma once

#include <type_traits>
#include "type/tuple.h"

namespace cupix::foundation {
template <typename T>
class AreaCoord : public detail::Tuplet<T, 2> {
  static_assert(std::is_floating_point_v<T>, "Requires floating type");

  using Base = detail::Tuplet<T, 2>;
  __UseTupletDirectiveAliases(Base);

 public:
  [[nodiscard]] constexpr auto r() const noexcept { return 1 - (s + t); }

  template <typename U>
  [[nodiscard]] constexpr bool operator==(const AreaCoord<U>& rhs) const noexcept {
    return Base::template equalAt_<0>(rhs);
  }

  template <typename U>
  [[nodiscard]] constexpr bool operator!=(const AreaCoord<U>& rhs) const noexcept {
    return Base::template notEqualAt_<0>(rhs);
  }

  [[nodiscard]] bool valid() const noexcept { return std::isfinite(s) && std::isfinite(t); }

  constexpr bool isCorner() const noexcept { return (s == 1) || (t == 1) || (s == 0 && t == 0); }

  constexpr bool isSide() const noexcept { return (s == 0) || (t == 0) || (s + t == 1); }

 public:
  [[nodiscard]] constexpr bool inside() const noexcept {
    return (0 <= s) && (0 <= t) && (s + t <= 1);
  }

  [[nodiscard]] constexpr bool outside() const noexcept {
    return (s < 0) || (t < 0) || (1 < s + t);
  }

  void reset() noexcept { s = 0, t = 0; }

  void reflectOverDiagonal() noexcept { s = 1 - s, t = 1 - t; }

  template <typename Scalar>
  [[nodiscard]] constexpr auto interpolated(const Scalar tri[3]) const noexcept {
    return tri[0] * r() + tri[1] * s + tri[2] * t;
  }

  template <typename Scalar>
  [[nodiscard]] constexpr auto interpolated(const Triple<Scalar>& tri) const noexcept {
    return tri[0] * r() + tri[1] * s + tri[2] * t;
  }

  template <typename Scalar>
  [[nodiscard]] constexpr auto interpolated(const Scalar& tri0,
                                            const Scalar& tri1,
                                            const Scalar& tri2) const noexcept {
    return tri0 * r() + tri1 * s + tri2 * t;
  }

 public:
  [[nodiscard]] static constexpr AreaCoord zero() noexcept { return AreaCoord(0, 0); }

  [[nodiscard]] static constexpr AreaCoord centroid() noexcept {
    return AreaCoord(T(1) / 3, T(1) / 3);
  }

 public:
  constexpr AreaCoord() noexcept = default;

  constexpr AreaCoord(T s, T t) : s(s), t(t) {}

  constexpr AreaCoord(const AreaCoord&) noexcept = default;

  template <typename U>
  constexpr AreaCoord(const AreaCoord<U>& other) noexcept : s(other.s), t(other.t) {}

  AreaCoord& operator=(const AreaCoord&) noexcept = default;

  template <typename U>
  AreaCoord& operator=(const AreaCoord<U>& rhs) {
    s = T(rhs.s);
    t = T(rhs.t);
    return *this;
  }

 public:
  T s = NumericConstants<T>::infinity;
  T t = NumericConstants<T>::infinity;
};

using AreaCoordf = AreaCoord<float>;
using AreaCoordd = AreaCoord<double>;
}  // namespace cupix::foundation

__SupportTupleStructuredBinding(cupix::foundation::AreaCoord, 2)
