#pragma once

#include <cmath>
#include <type_traits>

template <typename T, int N> struct vec {
  T data[N]{};

  constexpr T &operator[](int i) { return data[i]; }
  constexpr const T &operator[](int i) const { return data[i]; }
  constexpr bool operator==(const vec &) const = default;
};

template <typename T> struct vec<T, 2> {
  T x{}, y{};

  constexpr T &operator[](int i) { return i == 0 ? x : y; }
  constexpr const T &operator[](int i) const { return i == 0 ? x : y; }
  constexpr bool operator==(const vec &) const = default;
};

template <typename T> struct vec<T, 3> {
  T x{}, y{}, z{};

  constexpr T &operator[](int i) { return i == 0 ? x : i == 1 ? y : z; }
  constexpr const T &operator[](int i) const {
    return i == 0 ? x : i == 1 ? y : z;
  }
  constexpr bool operator==(const vec &) const = default;
};

template <typename T> struct vec<T, 4> {
  T x{}, y{}, z{}, w{};

  constexpr T &operator[](int i) {
    return i == 0 ? x : i == 1 ? y : i == 2 ? z : w;
  }
  constexpr const T &operator[](int i) const {
    return i == 0 ? x : i == 1 ? y : i == 2 ? z : w;
  }
  constexpr bool operator==(const vec &) const = default;
};

template <typename T> using vec2 = vec<T, 2>;
template <typename T> using vec3 = vec<T, 3>;
template <typename T> using vec4 = vec<T, 4>;

template <typename T, int N>
constexpr vec<T, N> &operator+=(vec<T, N> &a, const vec<T, N> &b) {
  for (int i = 0; i < N; ++i)
    a[i] += b[i];
  return a;
}

template <typename T, int N>
constexpr vec<T, N> &operator-=(vec<T, N> &a, const vec<T, N> &b) {
  for (int i = 0; i < N; ++i)
    a[i] -= b[i];
  return a;
}

template <typename T, int N>
constexpr vec<T, N> &operator*=(vec<T, N> &a, const vec<T, N> &b) {
  for (int i = 0; i < N; ++i)
    a[i] *= b[i];
  return a;
}

template <typename T, int N>
constexpr vec<T, N> &operator/=(vec<T, N> &a, const vec<T, N> &b) {
  for (int i = 0; i < N; ++i)
    a[i] /= b[i];
  return a;
}

template <typename T, int N>
constexpr vec<T, N> &operator+=(vec<T, N> &a, std::type_identity_t<T> s) {
  for (int i = 0; i < N; ++i)
    a[i] += s;
  return a;
}

template <typename T, int N>
constexpr vec<T, N> &operator-=(vec<T, N> &a, std::type_identity_t<T> s) {
  for (int i = 0; i < N; ++i)
    a[i] -= s;
  return a;
}

template <typename T, int N>
constexpr vec<T, N> &operator*=(vec<T, N> &a, std::type_identity_t<T> s) {
  for (int i = 0; i < N; ++i)
    a[i] *= s;
  return a;
}

template <typename T, int N>
constexpr vec<T, N> &operator/=(vec<T, N> &a, std::type_identity_t<T> s) {
  for (int i = 0; i < N; ++i)
    a[i] /= s;
  return a;
}

template <typename T, int N>
constexpr vec<T, N> operator+(vec<T, N> a, const vec<T, N> &b) {
  return a += b;
}

template <typename T, int N>
constexpr vec<T, N> operator-(vec<T, N> a, const vec<T, N> &b) {
  return a -= b;
}

template <typename T, int N>
constexpr vec<T, N> operator*(vec<T, N> a, const vec<T, N> &b) {
  return a *= b;
}

template <typename T, int N>
constexpr vec<T, N> operator/(vec<T, N> a, const vec<T, N> &b) {
  return a /= b;
}

template <typename T, int N>
constexpr vec<T, N> operator+(vec<T, N> a, std::type_identity_t<T> s) {
  return a += s;
}

template <typename T, int N>
constexpr vec<T, N> operator-(vec<T, N> a, std::type_identity_t<T> s) {
  return a -= s;
}

template <typename T, int N>
constexpr vec<T, N> operator*(vec<T, N> a, std::type_identity_t<T> s) {
  return a *= s;
}

template <typename T, int N>
constexpr vec<T, N> operator/(vec<T, N> a, std::type_identity_t<T> s) {
  return a /= s;
}

template <typename T, int N>
constexpr vec<T, N> operator+(std::type_identity_t<T> s, vec<T, N> a) {
  return a += s;
}

template <typename T, int N>
constexpr vec<T, N> operator*(std::type_identity_t<T> s, vec<T, N> a) {
  return a *= s;
}

template <typename T, int N>
constexpr vec<T, N> operator-(std::type_identity_t<T> s, vec<T, N> a) {
  for (int i = 0; i < N; ++i)
    a[i] = s - a[i];
  return a;
}

template <typename T, int N>
constexpr vec<T, N> operator/(std::type_identity_t<T> s, vec<T, N> a) {
  for (int i = 0; i < N; ++i)
    a[i] = s / a[i];
  return a;
}

template <typename T, int N> constexpr vec<T, N> operator-(vec<T, N> a) {
  for (int i = 0; i < N; ++i)
    a[i] = -a[i];
  return a;
}

template <typename T, int N>
constexpr T dot(const vec<T, N> &a, const vec<T, N> &b) {
  T result{};
  for (int i = 0; i < N; ++i)
    result += a[i] * b[i];
  return result;
}

template <typename T, int N> auto magnitude(const vec<T, N> &v) {
  return std::sqrt(dot(v, v));
}

template <typename T, int N> vec<T, N> normalize(vec<T, N> v) {
  return v / static_cast<T>(magnitude(v));
}

template <typename T> constexpr vec3<T> cross(vec3<T> a, vec3<T> b) {
  return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}
