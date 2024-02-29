#include <algorithm>
#include <fstream>
#include <string>
#include <unordered_set>

const std::string input_path = "input.txt";
const std::string output_path = "output.txt";

std::string trim_punctuation(const std::string &word) {
    std::string result = word;
    while (!result.empty() && ispunct(result.front()))
        result.erase(result.begin());
    while (!result.empty() && ispunct(result.back()))
        result.pop_back();
    return result;
}

int main() {
    std::unordered_set<std::string> words = {};

    auto input = std::ifstream(input_path);
    std::string word;

    while (input >> word) {
        word = trim_punctuation(word);
        std::transform(
            word.begin(), word.end(), word.begin(),
            [](unsigned char c) { return std::tolower(c); }
        );
        if (word.size() > 3)
            words.insert(word);
    }

    input.close();

    auto output = std::ofstream(output_path);
    for (const auto &word : words)
        output << word << std::endl;
    output.close();

    return 0;
}
