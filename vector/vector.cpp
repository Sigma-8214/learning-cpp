#include <array>
#include <cstdint>
#include <ostream>
#include <string>

#include "vector.hpp"

namespace vector {
template <size_t N> Vector<N> Vector<N>::empty() {
    Vector result;
    for (size_t i = 0; i < N; i++)
        result.data[i] = 0;
    return result;
}

template <size_t N> Vector<N> Vector<N>::from(std::array<Num, N> data) {
    Vector result;
    for (size_t i = 0; i < N; i++)
        result.data[i] = data[i];
    return result;
}

template <size_t N> Vector<N> Vector<N>::clone() const {
    Vector result;
    for (size_t i = 0; i < N; i++)
        result.data[i] = data[i];
    return result;
}

template <size_t N> Vector<N> Vector<N>::cross(Vector<N> other) const {
    Vector result;
    for (size_t i = 0; i < N; i++)
        result.data[i] = data[(i + 1) % N] * other.data[(i + 2) % N] -
                         data[(i + 2) % N] * other.data[(i + 1) % N];
    return result;
}

template <size_t N>
Vector<N> Vector<N>::hadamard_product(Vector<N> other) const {
    Vector result;
    for (size_t i = 0; i < N; i++)
        result.data[i] = data[i] * other.data[i];
    return result;
}

template <size_t N> Num Vector<N>::dot(Vector<N> other) const {
    auto acc = 0.0;
    for (size_t i = 0; i < N; i++)
        acc += data[i] * other.data[i];
    return acc;
}

template <size_t N>
Vector<N> Vector<N>::operator+(const Vector<N> &other) const {
    Vector result;
    for (size_t i = 0; i < N; i++)
        result.data[i] = data[i] + other.data[i];
    return result;
}

template <size_t N>
Vector<N> Vector<N>::operator-(const Vector<N> &other) const {
    Vector result;
    for (size_t i = 0; i < N; i++)
        result.data[i] = data[i] - other.data[i];
    return result;
}

template <size_t N> Vector<N> Vector<N>::operator-() const {
    Vector result;
    for (size_t i = 0; i < N; i++)
        result.data[i] = -data[i];
    return result;
}

template <size_t N> Vector<N> Vector<N>::operator*(const Num &scalar) const {
    Vector result;
    for (size_t i = 0; i < N; i++)
        result.data[i] = data[i] * scalar;
    return result;
}

template <size_t N> bool Vector<N>::operator==(const Vector<N> &other) const {
    for (size_t i = 0; i < N; i++)
        if (data[i] != other.data[i])
            return false;
    return true;
}

template <size_t N> bool Vector<N>::operator!=(const Vector<N> &other) const {
    return !(*this == other);
}

template <size_t N>
Vector<N> operator*(const Num &scalar, const Vector<N> &vec) {
    return vec * scalar;
}

template <size_t N> std::string Vector<N>::to_string() const {
    std::string result = "[";
    for (size_t i = 0; i < N; i++) {
        result += std::to_string(data[i]);
        if (i < N - 1)
            result += ", ";
    }
    result += "]";
    return result;
}

template <size_t N>
std::ostream &operator<<(std::ostream &os, const Vector<N> &vec) {
    os << vec.to_string();
    return os;
}
} // namespace vector