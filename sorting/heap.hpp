#pragma once

#include <cinttypes>

#include "../list/list.hpp"

namespace heap {
template <size_t N> void heap_sort(list::ArrayList<int> &list);
}

#include "heap.cpp"