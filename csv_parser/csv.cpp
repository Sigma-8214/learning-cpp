#include <sstream>

#include "csv.hpp"

namespace csv
{
    Record Record::from_line(const std::string line)
    {
        Record result;

        size_t idx = 0;
        std::string working;
        bool in_quotes = false;

        while (idx < line.size())
        {
            char c = line[idx];

            if (c == '\'' || c == '"')
                in_quotes ^= true;
            else if (c == ',' && !in_quotes)
            {
                result.data.push_back(working);
                working.clear();
            }
            else if (c == '\\' && idx + 1 < line.size() && line[++idx] == 'n')
                working.push_back('\n');
            else
                working.push_back(c);

            idx++;
        }

        if (working.size() > 0)
            result.data.push_back(working);

        return result;
    }

    size_t Record::len() const
    {
        return data.size();
    }

    std::string Record::get(const size_t idx) const
    {
        return data[idx];
    }

    uint64_t Record::get_int(const size_t idx) const
    {
        return std::stoull(data[idx]);
    }

    double Record::get_double(const size_t idx) const
    {
        return std::stod(data[idx]);
    }

    std::vector<Record> from_string(const std::string data)
    {
        std::vector<Record> result;

        std::istringstream iss(data);
        for (std::string line; std::getline(iss, line);)
            result.push_back(Record::from_line(line));

        return result;
    }
}