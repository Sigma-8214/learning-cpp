#include <iostream>
#include <cstdint>
#include <vector>

bool search_matrix(std::vector<std::vector<int32_t>> &matrix, int32_t target)
{
    int32_t width = matrix[0].size();

    int32_t left = 0;
    int32_t right = matrix.size() * matrix[0].size() - 1;
    int32_t mid;

    while (left <= right)
    {
        mid = (right - left) / 2 + left;
        int32_t element = matrix[mid / width][mid % width];

        if (element == target)
            return true;
        else if (element < target)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return false;
}

int main()
{
    int32_t width, height, target;
    std::cin >> width >> height >> target;

    std::vector<std::vector<int32_t>> matrix(height, std::vector<int32_t>(width));
    for (size_t i = 0; i < height; i++)
        for (size_t j = 0; j < width; j++)
            std::cin >> matrix[i][j];

    auto result = search_matrix(matrix, target);
    std::cout << (result ? "true" : "false") << std::endl;
    return 0;
}