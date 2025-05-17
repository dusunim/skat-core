#pragma once

#include <iterator>
#include <stdexcept>
#include <tuple>

namespace cupix::foundation::detail {
template <typename T, size_t Size>
class Tuplet {
 public:
  using value_type = T;
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  using pointer = value_type*;
  using const_pointer = const value_type*;
  using reference = value_type&;
  using const_reference = const value_type&;

  using iterator = pointer;
  using const_iterator = const_pointer;

  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

 public:
  constexpr const_pointer data() const { return reinterpret_cast<const_pointer>(this); }

  constexpr pointer data() { return reinterpret_cast<pointer>(this); }

  constexpr const_iterator begin() const noexcept { return data(); }

  constexpr const_iterator end() const noexcept { return data() + Size; }

  constexpr iterator begin() noexcept { return data(); }

  constexpr iterator end() noexcept { return data() + Size; }

  constexpr const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }

  constexpr const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }

  constexpr reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }

  constexpr reverse_iterator rend() noexcept { return reverse_iterator(begin()); }

  const_iterator cbegin() const noexcept { return begin(); }

  const_iterator cend() const noexcept { return end(); }

  const_reverse_iterator crbegin() const noexcept { return rbegin(); }

  const_reverse_iterator crend() const noexcept { return rend(); }

  constexpr size_type size() const noexcept { return Size; }

  constexpr size_type max_size() const noexcept { return Size; }

  constexpr bool empty() const noexcept { return false; }

  constexpr const T& operator[](size_t index) const { return data()[index]; }

  constexpr T& operator[](size_t index) { return data()[index]; }

  reference at(size_type pos) {
    if (Size <= pos) {
      throwRangeException_();
    }
    return data()[pos];
  }

  const_reference at(size_type pos) const {
    if (Size <= pos) {
      throwRangeException_();
    }
    return data()[pos];
  }

 public:
  template <size_t Index>
  [[nodiscard]] constexpr const T& get() const& noexcept {
    static_assert(Index < Size, "the specified index is out of bounds");
    return data()[Index];
  }

  template <size_t Index>
  [[nodiscard]] constexpr T& get() & noexcept {
    static_assert(Index < Size, "the specified index is out of bounds");
    return data()[Index];
  }

  template <size_t Index>
  [[nodiscard]] constexpr T&& get() && noexcept {
    static_assert(Index < Size, "the specified index is out of bounds");
    return std::move(data()[Index]);
  }

 protected:
  [[noreturn]] void throwRangeException_() const {
    throw std::out_of_range("invalid Tuplet<T, N> subscript.");
  }

  template <size_t Position, typename U>
  constexpr void assignAt_(const Tuplet<U, Size>& rhs) noexcept {
    data()[Position] = rhs.data()[Position];
    if constexpr (Position + 1 < Size) {
      assignAt_<Position + 1, U>(rhs);
    }
  }

  template <size_t Position, typename U>
  constexpr void assignForceAt_(const Tuplet<U, Size>& rhs) noexcept {
    data()[Position] = static_cast<const T&>(rhs.data()[Position]);
    if constexpr (Position + 1 < Size) {
      assignAt_<Position + 1, U>(rhs);
    }
  }

  template <size_t Position>
  constexpr bool equalAt_(const Tuplet& rhs) const noexcept {
    if constexpr (Position + 1 == Size) {
      return data()[Position] == rhs.data()[Position];
    } else {
      return data()[Position] == rhs.data()[Position] && equalAt_<Position + 1>(rhs);
    }
  }

  template <size_t Position>
  constexpr bool notEqualAt_(const Tuplet& rhs) const noexcept {
    if constexpr (Position + 1 == Size) {
      return data()[Position] != rhs.data()[Position];
    } else {
      return data()[Position] != rhs.data()[Position] || notEqualAt_<Position + 1>(rhs);
    }
  }

  template <size_t N = Size, std::enable_if_t<N == 1, int> = 0>
  constexpr bool lessThan_(const Tuplet<T, N>& rhs) const noexcept {
    return data()[0] < rhs.data()[0];
  }

  template <size_t N = Size, std::enable_if_t<N == 2, int> = 0>
  constexpr bool lessThan_(const Tuplet<T, N>& rhs) const noexcept {
    return std::tie(data()[0], data()[1]) < std::tie(rhs.data()[0], rhs.data()[1]);
  }

  template <size_t N = Size, std::enable_if_t<N == 3, int> = 0>
  constexpr bool lessThan_(const Tuplet<T, N>& rhs) const noexcept {
    return std::tie(data()[0], data()[1], data()[2]) <
           std::tie(rhs.data()[0], rhs.data()[1], rhs.data()[2]);
  }

  template <size_t N = Size, std::enable_if_t<N == 4, int> = 0>
  constexpr bool lessThan_(const Tuplet<T, N>& rhs) const noexcept {
    return std::tie(data()[0], data()[1], data()[2], data()[3]) <
           std::tie(rhs.data()[0], rhs.data()[1], rhs.data()[2], rhs.data()[3]);
  }

  template <size_t Position>
  constexpr void swapAt_() noexcept {
    if constexpr (Position + Position + 1 < Size) {
      std::swap(data()[Position], data()[Size - Position - 1]);
      swapAt_<Position + 1>();
    }
  }

  template <size_t Position, size_t N = Size, std::enable_if_t<N == 1, int> = 0>
  constexpr void swappedCopyAt_(Tuplet& rhs) const noexcept {
    rhs.data()[0] = data()[0];
  }

  template <size_t Position, size_t N = Size, std::enable_if_t<N >= 2, int> = 0>
  constexpr void swappedCopyAt_(Tuplet& rhs) const noexcept {
    if constexpr (Position + Position < Size) {
      rhs.data()[Position] = data()[Size - Position - 1];
      rhs.data()[Size - Position - 1] = data()[Position];
      swappedCopyAt_<Position + 1>(rhs);
    }
  }

  template <size_t Position>
  constexpr bool every_(const value_type& x) const noexcept {
    if constexpr (Position + 1 == Size) {
      return data()[Position] == x;
    } else {
      return data()[Position] == x && contains_<Position + 1>(x);
    }
  }

  template <size_t Position>
  constexpr bool contains_(const value_type& x) const noexcept {
    if constexpr (Position + 1 == Size) {
      return data()[Position] == x;
    } else {
      return data()[Position] == x || contains_<Position + 1>(x);
    }
  }

  template <size_t Position>
  constexpr auto indexof_(const value_type& x) const noexcept {
    if constexpr (Position == Size) {
      return Size;
    } else {
      return data()[Position] == x ? Position : indexof_<Position + 1>(x);
    }
  }

  constexpr auto& moduloAt_(size_t pos) noexcept { return data()[pos - (pos < Size ? 0 : Size)]; }

  constexpr auto& moduloAt_(size_t pos) const noexcept {
    return data()[pos - (pos < Size ? 0 : Size)];
  }

  constexpr auto& prevAt_(size_t pos) noexcept { return moduloAt_(pos + Size - 1); }

  constexpr auto& prevAt_(size_t pos) const noexcept { return moduloAt_(pos + Size - 1); }

  constexpr auto& nextAt_(size_t pos) noexcept { return moduloAt_(pos + 1); }

  constexpr auto& nextAt_(size_t pos) const noexcept { return moduloAt_(pos + 1); }
};
}  // namespace cupix::foundation::detail

#define __UseTupletDirectiveAliases(BaseAlias)                   \
 public:                                                         \
  using value_type = typename BaseAlias::value_type;             \
  using size_type = typename BaseAlias::size_type;               \
  using difference_type = typename BaseAlias::difference_type;   \
  using const_pointer = typename BaseAlias::const_pointer;       \
  using pointer = typename BaseAlias::pointer;                   \
  using const_reference = typename BaseAlias::const_reference;   \
  using reference = typename BaseAlias::reference;               \
                                                                 \
  using iterator = typename BaseAlias::iterator;                 \
  using const_iterator = typename BaseAlias::const_iterator;     \
  using reverse_iterator = typename BaseAlias::reverse_iterator; \
  using const_reverse_iterator = typename BaseAlias::const_reverse_iterator

#define __SupportTupleElementAccessors(Base)                               \
  namespace std {                                                          \
  template <size_t Index, typename T>                                      \
  [[nodiscard]] constexpr const auto& get(const Base<T>& tuple) noexcept { \
    return tuple.template get<Index>();                                    \
  }                                                                        \
                                                                           \
  template <size_t Index, typename T>                                      \
  [[nodiscard]] constexpr auto& get(Base<T>& tuple) noexcept {             \
    return tuple.template get<Index>();                                    \
  }                                                                        \
                                                                           \
  template <size_t Index, typename T>                                      \
  [[nodiscard]] constexpr auto&& get(Base<T>&& tuple) noexcept {           \
    return tuple.template get<Index>();                                    \
  }                                                                        \
  }

#define __SupportTupleSizeAccessor1(Base)                            \
  namespace std {                                                    \
  template <typename T>                                              \
  struct tuple_element<0, Base<T>> {                                 \
    using type = typename Base<T>::value_type;                       \
  };                                                                 \
  template <typename T>                                              \
  struct tuple_size<Base<T>> : std::integral_constant<size_t, 1> {}; \
  }

#define __SupportTupleSizeAccessor2(Base)                            \
  namespace std {                                                    \
  template <typename T>                                              \
  struct tuple_element<0, Base<T>> {                                 \
    using type = typename Base<T>::value_type;                       \
  };                                                                 \
                                                                     \
  template <typename T>                                              \
  struct tuple_element<1, Base<T>> {                                 \
    using type = typename Base<T>::value_type;                       \
  };                                                                 \
                                                                     \
  template <typename T>                                              \
  struct tuple_size<Base<T>> : std::integral_constant<size_t, 2> {}; \
  }

#define __SupportTupleSizeAccessor3(Base)                            \
  namespace std {                                                    \
  template <typename T>                                              \
  struct tuple_element<0, Base<T>> {                                 \
    using type = typename Base<T>::value_type;                       \
  };                                                                 \
                                                                     \
  template <typename T>                                              \
  struct tuple_element<1, Base<T>> {                                 \
    using type = typename Base<T>::value_type;                       \
  };                                                                 \
                                                                     \
  template <typename T>                                              \
  struct tuple_element<2, Base<T>> {                                 \
    using type = typename Base<T>::value_type;                       \
  };                                                                 \
                                                                     \
  template <typename T>                                              \
  struct tuple_size<Base<T>> : std::integral_constant<size_t, 3> {}; \
  }

#define __SupportTupleSizeAccessor4(Base)                            \
  namespace std {                                                    \
  template <typename T>                                              \
  struct tuple_element<0, Base<T>> {                                 \
    using type = typename Base<T>::value_type;                       \
  };                                                                 \
                                                                     \
  template <typename T>                                              \
  struct tuple_element<1, Base<T>> {                                 \
    using type = typename Base<T>::value_type;                       \
  };                                                                 \
                                                                     \
  template <typename T>                                              \
  struct tuple_element<2, Base<T>> {                                 \
    using type = typename Base<T>::value_type;                       \
  };                                                                 \
                                                                     \
  template <typename T>                                              \
  struct tuple_element<3, Base<T>> {                                 \
    using type = typename Base<T>::value_type;                       \
  };                                                                 \
                                                                     \
  template <typename T>                                              \
  struct tuple_size<Base<T>> : std::integral_constant<size_t, 4> {}; \
  }

#define __SupportTupleStructuredBinding(Base, N) \
  __SupportTupleElementAccessors(Base) __SupportTupleSizeAccessor##N(Base)
