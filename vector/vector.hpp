#pragma once

#include <array>
#include <cstdint>

using Num = double;

namespace vector {
template <size_t N> class Vector {
  public:
    std::array<Num, N> data;

    /// @brief Creates a new vector at the origin.
    static Vector<N> empty();

    /// @brief Creates a new vector from an array.
    static Vector<N> from(std::array<Num, N> data);

    /// @brief  Makes a copy of a vector.
    Vector<N> clone() const;

    /// @brief Computes the cross product of two vectors.
    Vector<N> cross(Vector<N> other) const;

    /// @brief Computes the hadamard product of two vectors. (component-wise
    /// multiplication)
    Vector<N> hadamard_product(Vector<N> other) const;

    /// @brief Computes the dot product of two vectors.
    Num dot(Vector<N> other) const;

    /// @brief Adds two vectors.
    Vector<N> operator+(const Vector<N> &other) const;

    /// @brief Subtracts two vectors
    Vector<N> operator-(const Vector<N> &other) const;

    /// @brief Negates a vector. (Inverts the sign of all components)
    Vector<N> operator-() const;

    /// @brief Scales a vector by a scalar. (Multiplies all components by a
    /// scalar)
    Vector<N> operator*(const Num &scalar) const;

    bool operator==(const Vector<N> &other) const;

    bool operator!=(const Vector<N> &other) const;

    /// @brief Scales a vector by a scalar. (Multiplies all components by a
    /// scalar)
    template <size_t K>
    friend Vector<K> operator*(const Num &scalar, const Vector<K> &vec);

    /// @brief Generates a string representation of a vector in the format: `[a,
    /// b, c ...]`.
    std::string to_string() const;

    /// @brief Overloads the `<<` operator to allow for easy printing of
    /// vectors.
    template <size_t K>
    friend std::ostream &operator<<(std::ostream &os, const Vector<K> &vec);
};
} // namespace vector

#include "vector.cpp"