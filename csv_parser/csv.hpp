#include <cstdint>
#include <string>
#include <vector>

namespace csv {
class Record {
    std::vector<std::string> data;

  public:
    static Record from_line(const std::string line);

    size_t len() const;
    std::string get(const size_t idx) const;
    uint64_t get_int(const size_t idx) const;
    double get_double(const size_t idx) const;
};

std::vector<Record> from_string(const std::string data);
} // namespace csv