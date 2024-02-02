#include <cstdint>
#include <vector>
#include <deque>
#include <iostream>

const uint32_t BUCKET_A = 5;
const uint32_t BUCKET_B = 3;
const uint32_t TARGET = 4;

enum class Action
{
    FillA,
    FillB,
    EmptyA,
    EmptyB,
    PourA,
    PourB
};

struct State
{
    std::vector<Action> history;
    uint32_t a;
    uint32_t b;

    State modify(const Action action) const
    {
        State state = *this;
        state.history.push_back(action);

        switch (action)
        {
        case Action::FillA:
            state.a = BUCKET_A;
            break;
        case Action::FillB:
            state.b = BUCKET_B;
            break;
        case Action::EmptyA:
            state.a = 0;
            break;
        case Action::EmptyB:
            state.b = 0;
            break;
        case Action::PourA:
        {
            uint32_t to_pour = std::min(state.a, BUCKET_B - state.b);
            state.a -= to_pour;
            state.b += to_pour;
        }
        break;
        case Action::PourB:
        {
            uint32_t to_pour = std::min(state.b, BUCKET_A - state.a);
            state.b -= to_pour;
            state.a += to_pour;
        }
        break;
        }

        return state;
    }
};

std::string action_to_string(const Action action)
{
    switch (action)
    {
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

int main()
{
    State s;
    std::deque<State> queue = {s};

    while (!queue.empty())
    {
        auto state = queue.front();
        if (state.a == TARGET || state.b == TARGET)
            break;

        queue.pop_front();
        for (int i = 0; i < 6; i++)
        {
            auto action = static_cast<Action>(i);
            State new_state = state.modify(action);
            queue.push_back(new_state);
        }
    }

    std::cout << "[*] Solution: " << std::endl;

    State state;
    for (auto action : queue.front().history)
    {
        state = state.modify(action);
        std::cout << " |  " << action_to_string(action) << "\t(" << state.a << ", " << state.b << ")" << std::endl;
    }

    return 0;
}
