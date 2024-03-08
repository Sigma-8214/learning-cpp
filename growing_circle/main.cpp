#include <windows.h>

#include "../tui_engine/tui.hpp"

int main() {
    auto gui = Gui::create();

    auto size = 5;

    for (;;) {
        if (GetAsyncKeyState(VK_ESCAPE))
            break;

        if (GetAsyncKeyState(VK_UP) | GetAsyncKeyState('W') & 0x01)
            size++;
        if (GetAsyncKeyState(VK_DOWN) | GetAsyncKeyState('S') & 0x01)
            size--;
        size = std::max(size, 1);

        auto center =
            Point2i::create(get_screen_size().x / 2, get_screen_size().y / 2);

        gui.draw_circle(center, size, '*', Style::unstyled());
        gui.draw_text(center, std::to_string(size), Style::unstyled());

        gui.update();
    }

    return 0;
}