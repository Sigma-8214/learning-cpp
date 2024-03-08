// Program and animates and moves the word and fades its color, stopping on a
// keypress

#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <thread>
#include <windows.h>

using time_point = std::chrono::system_clock::time_point;
using float32_t = float;

class Point2i {
  public:
    int32_t x;
    int32_t y;

    static Point2i create(int32_t x, int32_t y) {
        auto self = Point2i();
        self.x = x;
        self.y = y;
        return self;
    }
};

class Point2f {
  public:
    float32_t x;
    float32_t y;

    static Point2f create(float32_t x, float32_t y) {
        auto self = Point2f();
        self.x = x;
        self.y = y;
        return self;
    }
};

Point2i get_screen_size() {
    CONSOLE_SCREEN_BUFFER_INFO buffer_info;
    uint16_t columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &buffer_info);
    columns = buffer_info.srWindow.Right - buffer_info.srWindow.Left + 1;
    rows = buffer_info.srWindow.Bottom - buffer_info.srWindow.Top + 1;

    return Point2i::create(columns, rows);
}

class Color {
  public:
    uint8_t r;
    uint8_t g;
    uint8_t b;

    static Color create(uint8_t r, uint8_t g, uint8_t b) {
        auto self = Color();
        self.r = r;
        self.g = g;
        self.b = b;
        return self;
    }

    static Color
    from_hsv(float32_t hew, float32_t saturation, float32_t lightness) {
        auto i = std::floor(hew * 6);
        auto f = hew * 6 - i;
        auto p = lightness * (1 - saturation);
        auto q = lightness * (1 - f * saturation);
        auto t = lightness * (1 - (1 - f) * saturation);

        switch (static_cast<int>(i) % 6) {
        case 0:
            return Color::create(lightness * 255, t * 255, p * 255);
        case 1:
            return Color::create(q * 255, lightness * 255, p * 255);
        case 2:
            return Color::create(p * 255, lightness * 255, t * 255);
        case 3:
            return Color::create(p * 255, q * 255, lightness * 255);
        case 4:
            return Color::create(t * 255, p * 255, lightness * 255);
        case 5:
            return Color::create(lightness * 255, p * 255, q * 255);
        }
    }
};

class Style {
  public:
    Color fg;
    Color bg;

    static Style unstyled() {
        auto self = Style();
        self.fg = Color::create(255, 255, 255);
        self.bg = Color::create(0, 0, 0);
        return self;
    }

    static Style create(Color fg, Color bg) {
        auto self = Style();
        self.fg = fg;
        self.bg = bg;
        return self;
    }

    Style with_fg(Color fg) {
        auto self = Style();
        self.fg = fg;
        self.bg = bg;
        return self;
    }

    Style with_bg(Color bg) {
        auto self = Style();
        self.fg = fg;
        self.bg = bg;
        return self;
    }
};

class Gui {
    uint16_t width;
    uint16_t height;

    Style *style;
    char *screen;

    time_point last_update;

    uint16_t frame_rate = 30;
    float32_t delta_time = 1.0f / frame_rate;

    size_t to_index(Point2i position) {
        return position.y * width + position.x;
    }

    void refresh_screen() {
        auto screen_size = get_screen_size();

        if (screen_size.x != width || screen_size.y != height) {
            width = screen_size.x;
            height = screen_size.y;

            delete[] style;
            delete[] screen;

            style = new Style[width * height];
            screen = new char[width * height];
        }

        for (auto y = 0; y < height; y++) {
            for (auto x = 0; x < width; x++) {
                auto index = to_index(Point2i::create(x, y));
                screen[index] = 0;
                style[index] = Style::unstyled();
            }
        }
    }

  public:
    static Gui create() {
        auto self = Gui();
        self.refresh_screen();
        return self;
    }

    void drawText(Point2i position, const std::string text, Style style) {
        size_t idx = 0;
        auto chr = text.begin();

        for (; chr != text.end(); idx++, chr++) {
            auto x = position.x + idx;
            auto y = position.y;

            if (x < 0 || x >= width || y < 0 || y >= height)
                continue;

            auto index = to_index(Point2i::create(x, y));
            screen[index] = *chr;
            this->style[index] = style;
        }
    }

    float32_t get_delta_time() { return delta_time; }

    void update() {
        auto next_update =
            last_update + std::chrono::milliseconds(1000 / frame_rate);
        delta_time =
            std::chrono::duration<float32_t>(next_update - last_update).count();
        std::this_thread::sleep_until(next_update);
        last_update = std::chrono::system_clock::now();

        auto out = std::string();
        auto last_attr = 0;

        for (auto y = 0; y < height; y++) {
            for (auto x = 0; x < width; x++) {
                auto index = to_index(Point2i::create(x, y));
                auto style = this->style[index];
                auto fg = style.fg;
                auto bg = style.bg;

                auto color = RGB(fg.r, fg.g, fg.b);
                auto background = RGB(bg.r, bg.g, bg.b);
                auto style_attr = background << 4 | color;

                if (style_attr != last_attr) {
                    last_attr = style_attr;

                    out += "\x1b[38;2;";
                    out += std::to_string(fg.r) + ";";
                    out += std::to_string(fg.g) + ";";
                    out += std::to_string(fg.b) + "m";

                    out += "\x1b[48;2;";
                    out += std::to_string(bg.r) + ";";
                    out += std::to_string(bg.g) + ";";
                    out += std::to_string(bg.b) + "m";
                }

                if (screen[index] == 0)
                    out += " ";
                else
                    out += screen[index];
            }
            out += "\n";
        }

        out.pop_back();
        std::cout << "\x1b[H" << out << std::flush;

        refresh_screen();
    }
};

int main() {
    auto gui = Gui::create();

    auto paused = false;

    auto pos = Point2f::create(0, 0);
    auto vel = Point2f::create(10, 5);

    auto hue = 0.0;
    auto red = 0;

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

        gui.drawText(
            point, text,
            Style::unstyled().with_fg(Color::from_hsv(hue, 1.0, 1.0))
        );

        if (paused)
            gui.drawText(Point2i::create(0, 0), "Paused", Style::unstyled());

        gui.update();
    }

    return 0;
}