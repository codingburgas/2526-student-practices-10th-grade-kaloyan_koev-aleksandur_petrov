#pragma once

#include "raylib.h"
#include <string>

#include "Theme.h"

class Button
{
private:
    Rectangle bounds;
    std::string text;

public:
    Button(float x, float y, float width, float height, const std::string& text);

    bool IsHovered() const;

    bool IsClicked() const;

    void Draw(const Theme& theme) const;
};