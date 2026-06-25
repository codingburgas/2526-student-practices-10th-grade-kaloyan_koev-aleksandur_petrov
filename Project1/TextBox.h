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

    void SetActive(bool isActive);

    bool IsActive() const;

    void Update();

    void Draw(const char* placeholder, bool hideText = false) const;

    std::string GetText() const;

    void Clear();
};
