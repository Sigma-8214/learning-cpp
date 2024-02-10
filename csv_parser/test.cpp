#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "csv.hpp"

std::string read_to_string(std::string path) {
    std::ifstream file(path);
    std::string result;

    std::string line;
    while (std::getline(file, line))
        result += line + "\n";
    file.close();

    return result;
}

int main() {
    auto file = read_to_string("data.csv");
    auto records = csv::from_string(file);

    size_t box_width = 0;
    for (const auto &record : records)
        for (size_t i = 0; i < record.len(); i++)
            box_width = std::max(box_width, record.get(i).size() + 1);

    for (size_t i = 0; i < records.size(); i++) {
        auto record = records[i];
        auto row_len = (box_width + 2) * record.len() + 1;

        std::cout << std::string(row_len, '-') << std::endl;
        for (size_t i = 0; i < record.len(); i++) {
            auto val = record.get(i);
            std::cout << "| " << val
                      << std::string(box_width - val.size(), ' ');
        }
        std::cout << "|" << std::endl;
        if (i + 1 == records.size())
            std::cout << std::string(row_len, '-') << std::endl;
    }

    return 0;
}
