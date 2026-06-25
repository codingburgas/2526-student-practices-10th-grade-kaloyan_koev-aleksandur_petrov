#include "TextBox.h"

TextBox::TextBox(
    float x,
    float y,
    float width,
    float height
)
    : bounds{ x, y, width, height },
    active(false)
{
}

void TextBox::SetPosition(float x, float y)
{
    bounds.x = x;
    bounds.y = y;
}

void TextBox::SetActive(bool isActive)
{
    active = isActive;
}

bool TextBox::IsActive() const
{
    return active;
}

void TextBox::Update()
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        active = CheckCollisionPointRec(
            GetMousePosition(),
            bounds
        );
    }

    if (active)
    {
        int key = GetCharPressed();

        while (key > 0)
        {
            if (key >= 32 && key <= 125)
            {
                text += (char)key;
            }

            key = GetCharPressed();
        }

        if (
            IsKeyPressed(KEY_BACKSPACE)
            && !text.empty()
            )
        {
            text.pop_back();
        }
    }
}

void TextBox::Draw(
    const char* placeholder,
    bool hideText
) const
{
    DrawRectangleRounded(
        bounds,
        0.15f,
        10,
        active
        ? Color{ 70, 70, 90, 255 }
        : Color{ 50, 50, 70, 255 }
    );

    DrawRectangleLinesEx(
        bounds,
        2,
        active ? SKYBLUE : GRAY
    );

    std::string hiddenText(
        text.length(),
        '*'
    );

    const char* displayText =
        text.empty()
        ? placeholder
        : hideText
        ? hiddenText.c_str()
        : text.c_str();

    DrawText(
        displayText,
        bounds.x + 15,
        bounds.y + 15,
        24,
        RAYWHITE
    );
}

std::string TextBox::GetText() const
{
    return text;
}

void TextBox::Clear()
{
    text.clear();
}
