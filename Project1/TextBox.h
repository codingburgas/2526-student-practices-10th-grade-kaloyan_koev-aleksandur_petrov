#pragma once

#include "raylib.h"
#include <string>

class TextBox
{
private:
    Rectangle bounds;
    std::string text;
    bool active;

public:
    TextBox(
        float x,
        float y,
        float width,
        float height
    );

    void SetPosition(float x, float y);

    void Update();

    void Draw(const char* placeholder) const;

    std::string GetText() const;

    void Clear();
};