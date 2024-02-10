#include <cstdint>
#include <array>

using Num = double;

namespace vector
{
    template <size_t N>
    class Vector
    {
    public:
        std::array<Num, N> data;

        static Vector empty()
        {
            Vector result;
            for (size_t i = 0; i < N; i++)
                result.data[i] = 0;
            return result;
        }

        static Vector from(std::array<Num, N> data)
        {
            Vector result;
            for (size_t i = 0; i < N; i++)
                result.data[i] = data[i];
            return result;
        }

        Vector<N> cross(Vector<N> other)
        {
            Vector<N> result;
            for (size_t i = 0; i < N; i++)
                result.data[i] = data[(i + 1) % N] * other.data[(i + 2) % N] - data[(i + 2) % N] * other.data[(i + 1) % N];
            return result;
        }

        std::string to_string()
        {
            std::string result = "[";
            for (size_t i = 0; i < N; i++)
            {
                result += std::to_string(data[i]);
                if (i < N - 1)
                    result += ", ";
            }
            result += "]";
            return result;
        }

        Vector operator+(const Vector &other)
        {
            Vector result;
            for (size_t i = 0; i < N; i++)
                result.data[i] = data[i] + other.data[i];
            return result;
        }

        Vector operator-(const Vector &other)
        {
            Vector result;
            for (size_t i = 0; i < N; i++)
                result.data[i] = data[i] - other.data[i];
            return result;
        }
    };
}