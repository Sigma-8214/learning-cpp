#include <cstdint>
#include <deque>
#include <iostream>
#include <vector>

const uint32_t BUCKET_A = 5;
const uint32_t BUCKET_B = 3;
const uint32_t TARGET = 4;

enum class Action { FillA, FillB, EmptyA, EmptyB, PourA, PourB };

struct State {
    std::vector<Action> history;
    uint32_t a;
    uint32_t b;

    void modify(const Action action) {
        history.push_back(action);

        switch (action) {
        case Action::FillA:
            a = BUCKET_A;
            break;
        case Action::FillB:
            b = BUCKET_B;
            break;
        case Action::EmptyA:
            a = 0;
            break;
        case Action::EmptyB:
            b = 0;
            break;
        case Action::PourA: {
            uint32_t to_pour = std::min(a, BUCKET_B - b);
            a -= to_pour;
            b += to_pour;
        } break;
        case Action::PourB: {
            uint32_t to_pour = std::min(b, BUCKET_A - a);
            b -= to_pour;
            a += to_pour;
        } break;
        }
    }
};

std::string action_to_string(const Action action) {
    switch (action) {
    case Action::FillA:
        return "Fill A";
    case Action::FillB:
        return "Fill B";
    case Action::EmptyA:
        return "Empty A";
    case Action::EmptyB:
        return "Empty B";
    case Action::PourA:
        return "Pour A";
    case Action::PourB:
        return "Pour B";
    default:
        return "Unknown";
    }
}

int main() {
    std::deque<State> queue = {State()};

    while (!queue.empty()) {
        auto state = queue.front();
        if (state.a == TARGET || state.b == TARGET)
            break;

        queue.pop_front();
        for (int i = 0; i < 6; i++) {
            auto action = static_cast<Action>(i);
            auto new_state = state;

            new_state.modify(action);
            queue.push_back(new_state);
        }
    }

    std::cout << "[*] Solution: " << std::endl;

    auto state = State{};
    for (auto action : queue.front().history) {
        state.modify(action);
        std::cout << " |  " << action_to_string(action) << "\t(" << state.a
                  << ", " << state.b << ")" << std::endl;
    }

    return 0;
}
