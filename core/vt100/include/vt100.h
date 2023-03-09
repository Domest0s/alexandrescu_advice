#pragma once

#include <string>
#include <cassert>

#define COL_RESET "\033[0m"
//<ESC>[30m Black(black)
#define COL_RED     "\033[31m"
#define COL_GREEN   "\033[32m"
#define COL_YELLOW  "\033[33m"
#define COL_BLUE    "\033[34m"
#define COL_MAGENTA "\033[35m"
#define COL_CYAN    "\033[36m"
#define COL_WHITE   "\033[37m"


// move the cursor up/down/forward/backward N lines
#define MOVE_UP(N)        "\033[" #N "A"
#define MOVE_DOWN(N)      "\033[" #N "B"
#define MOVE_FORWARD(N)   "\033[" #N "C"
#define MOVE_BACKWARD(N)  "\033[" #N "D"
#define CLEAR_LINE "\033[2K"

namespace vt100
{

enum class Color
{
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White
};

const char* color(Color col)
{
    switch (col)
    {
    case Color::Red:
        return COL_RED;
    case Color::Green:
        return COL_GREEN;
    case Color::Yellow:
        return COL_YELLOW;
    case Color::Blue:
        return COL_BLUE;
    case Color::Magenta:
        return COL_MAGENTA;
    case Color::Cyan:
        return COL_CYAN;
    case Color::White:
        return COL_WHITE;
    default:
        assert(false);
        return "";
    }
}

std::string move_up(unsigned int n)
{
    if (n == 0) { return ""; }
    return "\033[" + std::to_string(n) + "A";
}

std::string move_down(unsigned int n)
{
    if (n == 0) { return ""; }
    return "\033[" + std::to_string(n) + "B";
}

std::string move_forward(unsigned int n)
{
    if (n == 0) { return ""; }
    return "\033[" + std::to_string(n) + "C";
}

std::string move_backward(unsigned int n)
{
    if (n == 0) { return ""; }
    return "\033[" + std::to_string(n) + "D";
}

}
