#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <thread>
#include <windows.h>

#include "tui.hpp"

using time_point = std::chrono::system_clock::time_point;
using float32_t = float;

Point2i Point2i::create(int32_t x, int32_t y) {
    auto self = Point2i();
    self.x = x;
    self.y = y;
    return self;
}

Point2f Point2f::create(float32_t x, float32_t y) {
    auto self = Point2f();
    self.x = x;
    self.y = y;
    return self;
}

Point2i get_screen_size() {
    CONSOLE_SCREEN_BUFFER_INFO buffer_info;
    uint16_t columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &buffer_info);
    columns = buffer_info.srWindow.Right - buffer_info.srWindow.Left + 1;
    rows = buffer_info.srWindow.Bottom - buffer_info.srWindow.Top + 1;

    return Point2i::create(columns, rows);
}

Color Color::create(uint8_t r, uint8_t g, uint8_t b) {
    auto self = Color();
    self.r = r;
    self.g = g;
    self.b = b;
    return self;
}

Color Color::from_hsv(
    float32_t hew, float32_t saturation, float32_t lightness
) {
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

Style Style::unstyled() {
    auto self = Style();
    self.fg = Color::create(255, 255, 255);
    self.bg = Color::create(0, 0, 0);
    return self;
}

Style Style::create(Color fg, Color bg) {
    auto self = Style();
    self.fg = fg;
    self.bg = bg;
    return self;
}

Style Style::with_fg(Color fg) {
    auto self = Style();
    self.fg = fg;
    self.bg = bg;
    return self;
}

Style Style::with_bg(Color bg) {
    auto self = Style();
    self.fg = fg;
    self.bg = bg;
    return self;
}

size_t Gui::to_index(Point2i position) {
    return position.y * width + position.x;
}

void Gui::refresh_screen() {
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

Gui Gui::create() {
    auto self = Gui();
    self.refresh_screen();
    return self;
}

void Gui::set(char character, Point2i position, Style style) {
    auto index = to_index(position);
    if (index < 0 || index >= width * height)
        return;

    screen[index] = character;
    this->style[index] = style;
}

void Gui::draw_text(Point2i position, const std::string text, Style style) {
    size_t idx = 0;
    auto chr = text.begin();

    for (; chr != text.end(); idx++, chr++) {
        auto x = position.x + idx;
        auto y = position.y;

        if (x < 0 || x >= width || y < 0 || y >= height)
            continue;

        set(*chr, Point2i::create(x, y), style);
    }
}

// Modified From: Circle drawing algorithm in C
// https://dev.to/sjmulder/circle-drawing-algorithm-in-c-4057
void Gui::draw_circle(Point2i center, int32_t radius, char chr, Style style) {
    int32_t x, y;

    for (x = 0, y = radius; x < y; x++)
        for (; y >= 0; y--) {
            set(chr, Point2i::create(center.x + x * 2, center.y + y), style);
            set(chr, Point2i::create(center.x + x * 2, center.y - y), style);
            set(chr, Point2i::create(center.x - x * 2, center.y + y), style);
            set(chr, Point2i::create(center.x - x * 2, center.y - y), style);

            set(chr, Point2i::create(center.x + y * 2, center.y + x), style);
            set(chr, Point2i::create(center.x + y * 2, center.y - x), style);
            set(chr, Point2i::create(center.x - y * 2, center.y + x), style);
            set(chr, Point2i::create(center.x - y * 2, center.y - x), style);

            if (x * x + (y - 1) * (y - 1) < radius * radius)
                break;
        }
}

float32_t Gui::get_delta_time() { return delta_time; }

void Gui::update() {
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
