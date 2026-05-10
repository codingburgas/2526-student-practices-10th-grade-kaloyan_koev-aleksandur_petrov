#include "Button.h"

Button::Button(float x, float y, float width, float height, const std::string& text)
    : bounds{ x, y, width, height }, text(text)
{
}

bool Button::IsHovered() const
{
    return CheckCollisionPointRec(GetMousePosition(), bounds);
}

bool Button::IsClicked() const
{
    return IsHovered() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

void Button::Draw(const Theme& theme) const
{
    Color buttonColor =
        IsHovered()
        ? theme.buttonHover
        : theme.button;

    DrawRectangleRounded(
        bounds,
        0.2f,
        10,
        buttonColor
    );

    int fontSize = 28;

    int textWidth =
        MeasureText(text.c_str(), fontSize);

    DrawText(
        text.c_str(),
        (int)(bounds.x + bounds.width / 2 - textWidth / 2),
        (int)(bounds.y + bounds.height / 2 - fontSize / 2),
        fontSize,
        theme.text
    );
}