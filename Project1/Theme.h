#pragma once

#include "raylib.h"

struct Theme
{
    Color background;
    Color panel;
    Color button;
    Color buttonHover;
    Color text;
    Color accent;
};

extern Theme LightTheme;
extern Theme DarkTheme;