#include <array>
#include <cstdint>

using Num = double;

namespace vector {
template <size_t N> class Vector {
  public:
    std::array<Num, N> data;

    /// @brief Creates a new vector at the origin.
    static Vector empty() {
        Vector result;
        for (size_t i = 0; i < N; i++)
            result.data[i] = 0;
        return result;
    }

    /// @brief Creates a new vector from an array.
    static Vector from(std::array<Num, N> data) {
        Vector result;
        for (size_t i = 0; i < N; i++)
            result.data[i] = data[i];
        return result;
    }

    /// @brief  Makes a copy of a vector.
    Vector clone() const {
        Vector result;
        for (size_t i = 0; i < N; i++)
            result.data[i] = data[i];
        return result;
    }

    /// @brief Computes the cross product of two vectors.
    Vector cross(Vector<N> other) const {
        Vector result;
        for (size_t i = 0; i < N; i++)
            result.data[i] = data[(i + 1) % N] * other.data[(i + 2) % N] -
                             data[(i + 2) % N] * other.data[(i + 1) % N];
        return result;
    }

    /// @brief Computes the hadamard product of two vectors. (component-wise
    /// multiplication)
    Vector hadamard_product(Vector<N> other) const {
        Vector result;
        for (size_t i = 0; i < N; i++)
            result.data[i] = data[i] * other.data[i];
        return result;
    }

    /// @brief Computes the dot product of two vectors.
    Num dot(Vector<N> other) const {
        auto acc = 0.0;
        for (size_t i = 0; i < N; i++)
            acc += data[i] * other.data[i];
        return acc;
    }

    /// @brief Adds two vectors.
    Vector operator+(const Vector &other) const {
        Vector result;
        for (size_t i = 0; i < N; i++)
            result.data[i] = data[i] + other.data[i];
        return result;
    }

    /// @brief Subtracts two vectors
    Vector operator-(const Vector &other) const {
        Vector result;
        for (size_t i = 0; i < N; i++)
            result.data[i] = data[i] - other.data[i];
        return result;
    }

    /// @brief Negates a vector. (Inverts the sign of all components)
    Vector operator-() const {
        Vector result;
        for (size_t i = 0; i < N; i++)
            result.data[i] = -data[i];
        return result;
    }

    /// @brief Scales a vector by a scalar. (Multiplies all components by a
    /// scalar)
    Vector operator*(const Num &scalar) const {
        Vector result;
        for (size_t i = 0; i < N; i++)
            result.data[i] = data[i] * scalar;
        return result;
    }

    /// @brief Scales a vector by a scalar. (Multiplies all components by a
    /// scalar)
    friend Vector operator*(const Num &scalar, const Vector &vec) {
        return vec * scalar;
    }

    /// @brief Generates a string representation of a vector in the format: `[a,
    /// b, c ...]`.
    std::string to_string() const {
        std::string result = "[";
        for (size_t i = 0; i < N; i++) {
            result += std::to_string(data[i]);
            if (i < N - 1)
                result += ", ";
        }
        result += "]";
        return result;
    }

    /// @brief Overloads the `<<` operator to allow for easy printing of
    /// vectors.
    friend std::ostream &operator<<(std::ostream &os, const Vector &vec) {
        os << vec.to_string();
        return os;
    }
};
} // namespace vector