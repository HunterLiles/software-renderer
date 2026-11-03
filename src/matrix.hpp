#pragma once

#include <type_traits>

#include "vector.hpp"

template <int R, int C, typename T = float> struct mat {
  T data[R][C]{};

  constexpr T *operator[](int row) { return data[row]; }
  constexpr const T *operator[](int row) const { return data[row]; }

  constexpr bool operator==(const mat &) const = default;
};

template <int R, int C, typename T>
constexpr mat<R, C, T> &operator+=(mat<R, C, T> &a, const mat<R, C, T> &b) {
  for (int r = 0; r < R; ++r)
    for (int c = 0; c < C; ++c)
      a[r][c] += b[r][c];
  return a;
}

template <int R, int C, typename T>
constexpr mat<R, C, T> &operator-=(mat<R, C, T> &a, const mat<R, C, T> &b) {
  for (int r = 0; r < R; ++r)
    for (int c = 0; c < C; ++c)
      a[r][c] -= b[r][c];
  return a;
}

template <int R, int C, typename T>
constexpr mat<R, C, T> &operator*=(mat<R, C, T> &a, std::type_identity_t<T> s) {
  for (int r = 0; r < R; ++r)
    for (int c = 0; c < C; ++c)
      a[r][c] *= s;
  return a;
}

template <int R, int C, typename T>
constexpr mat<R, C, T> &operator/=(mat<R, C, T> &a, std::type_identity_t<T> s) {
  for (int r = 0; r < R; ++r)
    for (int c = 0; c < C; ++c)
      a[r][c] /= s;
  return a;
}

template <int R, int C, typename T>
constexpr mat<R, C, T> operator+(mat<R, C, T> a, const mat<R, C, T> &b) {
  return a += b;
}

template <int R, int C, typename T>
constexpr mat<R, C, T> operator-(mat<R, C, T> a, const mat<R, C, T> &b) {
  return a -= b;
}

template <int R, int C, typename T>
constexpr mat<R, C, T> operator*(mat<R, C, T> a, std::type_identity_t<T> s) {
  return a *= s;
}

template <int R, int C, typename T>
constexpr mat<R, C, T> operator*(std::type_identity_t<T> s, mat<R, C, T> a) {
  return a *= s;
}

template <int R, int C, typename T>
constexpr mat<R, C, T> operator/(mat<R, C, T> a, std::type_identity_t<T> s) {
  return a /= s;
}

template <int R, int C, typename T>
constexpr mat<R, C, T> operator-(mat<R, C, T> a) {
  return a *= T(-1);
}

template <int R, int C, int K, typename T>
constexpr mat<R, K, T> operator*(const mat<R, C, T> &a, const mat<C, K, T> &b) {
  mat<R, K, T> result{};

  for (int r = 0; r < R; ++r)
    for (int c = 0; c < K; ++c)
      for (int k = 0; k < C; ++k)
        result[r][c] += a[r][k] * b[k][c];

  return result;
}

template <int R, int C, typename T>
constexpr vec<T, R> operator*(const mat<R, C, T> &a, const vec<T, C> &v) {
  vec<T, R> result{};

  for (int r = 0; r < R; ++r)
    for (int c = 0; c < C; ++c)
      result[r] += a[r][c] * v[c];

  return result;
}

template <int R, int C, typename T>
constexpr vec<T, C> operator*(const vec<T, R> &v, const mat<R, C, T> &a) {
  vec<T, C> result{};

  for (int c = 0; c < C; ++c)
    for (int r = 0; r < R; ++r)
      result[c] += v[r] * a[r][c];

  return result;
}

template <int N, typename T>
constexpr mat<N, N, T> &operator*=(mat<N, N, T> &a, const mat<N, N, T> &b) {
  return a = a * b;
}

template <int R, int C, typename T>
constexpr mat<C, R, T> transpose(const mat<R, C, T> &a) {
  mat<C, R, T> result{};

  for (int r = 0; r < R; ++r)
    for (int c = 0; c < C; ++c)
      result[c][r] = a[r][c];

  return result;
}

template <int N, typename T = float> constexpr mat<N, N, T> identity() {
  mat<N, N, T> result{};

  for (int i = 0; i < N; ++i)
    result[i][i] = T(1);

  return result;
}
