#include <cmath>
#include <string>
#include <windows.h>

#include "../tui_engine/tui.hpp"

int main() {
    auto gui = Gui::create().with_target_frame_rate(-1);

    auto paused = false;

    auto pos = Point2f::create(0, 0);
    auto vel = Point2f::create(10, 5);

    auto hue = 0.0;

    auto text = std::string("Hello, World!");
    auto text_len = text.length();

    for (;;) {
        paused ^= GetAsyncKeyState(VK_SPACE) & 0x01;
        if (GetAsyncKeyState(VK_ESCAPE))
            break;

        pos.x += vel.x * gui.get_delta_time() * !paused;
        pos.y += vel.y * gui.get_delta_time() * !paused;

        hue += gui.get_delta_time() / 5.0;
        if (hue > 1.0)
            hue -= 1.0;

        auto point = Point2i::create(std::lround(pos.x), std::lround(pos.y));
        if (point.x < 0 || point.x + text_len >= get_screen_size().x)
            vel.x *= -1;
        if (point.y < 0 || point.y >= get_screen_size().y)
            vel.y *= -1;

        gui.draw_text(
            point, text,
            Style::unstyled().with_fg(Color::from_hsv(hue, 1.0, 1.0))
        );

        if (paused)
            gui.draw_text(Point2i::create(0, 0), "Paused", Style::unstyled());

        gui.update();
    }

    gui.cleanup();
    return 0;
}