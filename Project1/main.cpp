#include "raylib.h"

#include "Button.h"
#include "Theme.h"
#include "ScreenState.h"

int main()
{
    const int screenWidth = 1600;
    const int screenHeight = 900;

    // Allow resizing/maximizing
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(screenWidth, screenHeight, "Cinema Booking System");

    // Prevent window from becoming too small
    SetWindowMinSize(1280, 720);

    // Start maximized
    MaximizeWindow();

    SetTargetFPS(60);

    bool darkMode = true;

    ScreenState currentScreen = ScreenState::Home;

    while (!WindowShouldClose())
    {
        int currentWidth = GetScreenWidth();
        int currentHeight = GetScreenHeight();

        Theme currentTheme = darkMode
            ? DarkTheme
            : LightTheme;

        // =========================
        // PANEL SETTINGS
        // =========================

        const int panelWidth = 700;
        const int panelHeight = 650;

        float panelX = (currentWidth - panelWidth) / 2.0f;
        float panelY = (currentHeight - panelHeight) / 2.0f;

        // =========================
        // BUTTON SETTINGS
        // =========================

        const int buttonWidth = 400;
        const int buttonHeight = 70;

        float buttonX = (currentWidth - buttonWidth) / 2.0f;

        Button bookingButton(
            buttonX,
            panelY + 170,
            buttonWidth,
            buttonHeight,
            "Book Tickets"
        );

        Button adminButton(
            buttonX,
            panelY + 280,
            buttonWidth,
            buttonHeight,
            "Admin Panel"
        );

        Button settingsButton(
            buttonX,
            panelY + 390,
            buttonWidth,
            buttonHeight,
            "Settings"
        );

        Button exitButton(
            buttonX,
            panelY + 500,
            buttonWidth,
            buttonHeight,
            "Exit"
        );

        Button themeButton(
            currentWidth - 240,
            30,
            200,
            50,
            darkMode ? "Light Mode" : "Dark Mode"
        );

        // =========================
        // BUTTON EVENTS
        // =========================

        // Toggle dark/light mode
        if (themeButton.IsClicked())
        {
            darkMode = !darkMode;
        }

        // Exit application
        if (exitButton.IsClicked())
        {
            break;
        }

        // =========================
        // DRAWING
        // =========================

        BeginDrawing();

        ClearBackground(currentTheme.background);

        // Main panel
        DrawRectangleRounded(
            {
                panelX,
                panelY,
                (float)panelWidth,
                (float)panelHeight
            },
            0.05f,
            10,
            currentTheme.panel
        );

        // =========================
        // TITLE
        // =========================

        const char* title = "ONLINE CINEMA BOOKING SYSTEM";

        int titleFontSize = 42;

        int titleWidth = MeasureText(title, titleFontSize);

        DrawText(
            title,
            currentWidth / 2 - titleWidth / 2,
            (int)panelY + 50,
            titleFontSize,
            currentTheme.accent
        );

        // =========================
        // SUBTITLE
        // =========================

        const char* subtitle = "Movie Ticket Reservation Platform";

        int subtitleFontSize = 24;

        int subtitleWidth = MeasureText(subtitle, subtitleFontSize);

        DrawText(
            subtitle,
            currentWidth / 2 - subtitleWidth / 2,
            (int)panelY + 110,
            subtitleFontSize,
            currentTheme.text
        );

        // =========================
        // DRAW BUTTONS
        // =========================

        bookingButton.Draw(currentTheme);
        adminButton.Draw(currentTheme);
        settingsButton.Draw(currentTheme);
        exitButton.Draw(currentTheme);

        themeButton.Draw(currentTheme);

        // =========================
        // FOOTER
        // =========================

        DrawText(
            "Cinema Booking System | raylib | C++",
            20,
            currentHeight - 35,
            20,
            currentTheme.text
        );

        EndDrawing();
    }

    CloseWindow();

    return 0;
}