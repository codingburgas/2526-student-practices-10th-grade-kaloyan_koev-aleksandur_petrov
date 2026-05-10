#include "raylib.h"

#include "Button.h"
#include "Theme.h"
#include "ScreenState.h"

int main()
{
    const int screenWidth = 1400;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "Cinema Booking System");

    SetTargetFPS(60);

    bool darkMode = true;

    ScreenState currentScreen = ScreenState::Home;

    Button bookingButton(500, 280, 400, 70, "Book Tickets");
    Button adminButton(500, 390, 400, 70, "Admin Panel");
    Button settingsButton(500, 500, 400, 70, "Settings");
    Button themeButton(1120, 40, 220, 50, "Toggle Theme");
    Button exitButton(500, 610, 400, 70, "Exit");

    while (!WindowShouldClose())
    {
        Theme currentTheme = darkMode
            ? DarkTheme
            : LightTheme;

        if (themeButton.IsClicked())
        {
            darkMode = !darkMode;
        }

        if (exitButton.IsClicked())
        {
            break;
        }

        BeginDrawing();

        ClearBackground(currentTheme.background);

        DrawRectangleRounded(
            { 350, 120, 700, 650 },
            0.05f,
            10,
            currentTheme.panel
        );

        DrawText(
            "ONLINE CINEMA BOOKING SYSTEM",
            380,
            170,
            42,
            currentTheme.accent
        );

        DrawText(
            "Movie Ticket Reservation Platform",
            500,
            220,
            24,
            currentTheme.text
        );

        bookingButton.Draw(currentTheme);
        adminButton.Draw(currentTheme);
        settingsButton.Draw(currentTheme);
        exitButton.Draw(currentTheme);

        themeButton.Draw(currentTheme);

        DrawText(
            "Visual Studio 2022 | raylib | C++",
            20,
            860,
            20,
            currentTheme.text
        );

        EndDrawing();
    }

    CloseWindow();

    return 0;
}