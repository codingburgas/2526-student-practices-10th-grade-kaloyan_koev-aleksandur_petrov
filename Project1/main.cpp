#include "raylib.h"

#include "Button.h"
#include "Theme.h"
#include "ScreenState.h"
#include "TextBox.h"

#include <fstream>
#include <string>

int main()
{
    const int screenWidth = 1600;
    const int screenHeight = 900;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(
        screenWidth,
        screenHeight,
        "Cinema Booking System"
    );

    SetWindowMinSize(1280, 720);

    MaximizeWindow();

    SetTargetFPS(60);

    bool darkMode = true;

    bool loginFailed = false;

    std::string loggedInEmail = "";

    ScreenState currentScreen =
        ScreenState::Home;

    // =========================
    // PERSISTENT TEXTBOXES
    // =========================

    TextBox emailBox(0, 0, 400, 60);

    TextBox passwordBox(0, 0, 400, 60);

    TextBox confirmPasswordBox(0, 0, 400, 60);

    while (!WindowShouldClose())
    {
        int currentWidth = GetScreenWidth();

        int currentHeight = GetScreenHeight();

        Theme currentTheme =
            darkMode
            ? DarkTheme
            : LightTheme;

        // =========================
        // PANEL
        // =========================

        const float panelWidth = 950.0f;

        const float panelHeight = 760.0f;

        float panelX =
            (currentWidth - panelWidth) / 2.0f;

        float panelY =
            (currentHeight - panelHeight) / 2.0f;

        // =========================
        // DYNAMIC TEXTBOX POSITIONING
        // =========================

        float textBoxX =
            currentWidth / 2.0f - 200;

        emailBox.SetPosition(
            textBoxX,
            panelY + 280
        );

        passwordBox.SetPosition(
            textBoxX,
            panelY + 390
        );

        confirmPasswordBox.SetPosition(
            textBoxX,
            panelY + 500
        );

        // =========================
        // BUTTON SETTINGS
        // =========================

        const float buttonWidth = 500.0f;

        const float buttonHeight = 80.0f;

        float buttonX =
            currentWidth / 2.0f
            - buttonWidth / 2.0f;

        // =========================
        // HOME BUTTONS
        // =========================

        Button loginButton(
            buttonX,
            panelY + 180,
            buttonWidth,
            buttonHeight,
            "Login"
        );

        Button bookingButton(
            buttonX,
            panelY + 300,
            buttonWidth,
            buttonHeight,
            "Book Tickets"
        );

        Button adminButton(
            buttonX,
            panelY + 420,
            buttonWidth,
            buttonHeight,
            "Admin Panel"
        );

        Button settingsButton(
            buttonX,
            panelY + 540,
            buttonWidth,
            buttonHeight,
            "Settings"
        );

        Button exitButton(
            buttonX,
            panelY + 660,
            buttonWidth,
            buttonHeight,
            "Exit"
        );

        // =========================
        // AUTH BUTTONS
        // =========================

        Button authLoginButton(
            currentWidth / 2 - 150,
            panelY + 280,
            300,
            70,
            "Login"
        );

        Button signUpButton(
            currentWidth / 2 - 150,
            panelY + 390,
            300,
            70,
            "Sign Up"
        );

        Button backButton(
            30,
            30,
            150,
            50,
            "Back"
        );

        // =========================
        // THEME BUTTON
        // =========================

        Button themeButton(
            currentWidth - 240,
            30,
            200,
            50,
            darkMode
            ? "Light Mode"
            : "Dark Mode"
        );

        // =========================
        // EVENTS
        // =========================

        if (themeButton.IsClicked())
        {
            darkMode = !darkMode;
        }

        // =========================
        // HOME SCREEN
        // =========================

        if (currentScreen ==
            ScreenState::Home)
        {
            if (loginButton.IsClicked())
            {
                emailBox.Clear();

                passwordBox.Clear();

                confirmPasswordBox.Clear();

                currentScreen =
                    ScreenState::AuthMenu;
            }

            if (exitButton.IsClicked())
            {
                break;
            }
        }

        // =========================
        // AUTH MENU
        // =========================

        if (currentScreen ==
            ScreenState::AuthMenu)
        {
            if (authLoginButton.IsClicked())
            {
                emailBox.Clear();

                passwordBox.Clear();

                loginFailed = false;

                currentScreen =
                    ScreenState::Login;
            }

            if (signUpButton.IsClicked())
            {
                emailBox.Clear();

                passwordBox.Clear();

                confirmPasswordBox.Clear();

                currentScreen =
                    ScreenState::SignUp;
            }

            if (backButton.IsClicked())
            {
                currentScreen =
                    ScreenState::Home;
            }
        }

        // =========================
        // SIGN UP SCREEN
        // =========================

        if (currentScreen ==
            ScreenState::SignUp)
        {
            emailBox.Update();

            passwordBox.Update();

            confirmPasswordBox.Update();

            if (IsKeyPressed(KEY_ENTER))
            {
                if (
                    passwordBox.GetText() ==
                    confirmPasswordBox.GetText()
                    )
                {
                    std::ofstream file(
                        "users.txt",
                        std::ios::app
                    );

                    file
                        << emailBox.GetText()
                        << "|"
                        << passwordBox.GetText()
                        << "\n";

                    file.close();

                    emailBox.Clear();

                    passwordBox.Clear();

                    confirmPasswordBox.Clear();

                    currentScreen =
                        ScreenState::AuthMenu;
                }
            }

            if (backButton.IsClicked())
            {
                emailBox.Clear();

                passwordBox.Clear();

                confirmPasswordBox.Clear();

                currentScreen =
                    ScreenState::AuthMenu;
            }
        }

        // =========================
        // LOGIN SCREEN
        // =========================

        if (currentScreen ==
            ScreenState::Login)
        {
            emailBox.Update();

            passwordBox.Update();

            if (IsKeyPressed(KEY_ENTER))
            {
                std::ifstream file(
                    "users.txt"
                );

                std::string line;

                bool success = false;

                while (getline(file, line))
                {
                    size_t separator =
                        line.find('|');

                    std::string email =
                        line.substr(
                            0,
                            separator
                        );

                    std::string password =
                        line.substr(
                            separator + 1
                        );

                    if (
                        email ==
                        emailBox.GetText()
                        &&
                        password ==
                        passwordBox.GetText()
                        )
                    {
                        success = true;

                        loggedInEmail = email;

                        break;
                    }
                }

                file.close();

                if (success)
                {
                    loginFailed = false;

                    currentScreen =
                        ScreenState::LoggedIn;
                }
                else
                {
                    loginFailed = true;
                }
            }

            if (backButton.IsClicked())
            {
                emailBox.Clear();

                passwordBox.Clear();

                currentScreen =
                    ScreenState::AuthMenu;
            }
        }

        // =========================
        // DRAWING
        // =========================

        BeginDrawing();

        ClearBackground(
            currentTheme.background
        );

        DrawRectangleRounded(
            {
                panelX,
                panelY,
                panelWidth,
                panelHeight
            },
            0.03f,
            10,
            currentTheme.panel
        );

        // =========================
        // HOME SCREEN
        // =========================

        if (currentScreen ==
            ScreenState::Home)
        {
            DrawText(
                "ONLINE CINEMA BOOKING SYSTEM",
                currentWidth / 2 - 360,
                panelY + 60,
                42,
                currentTheme.accent
            );

            loginButton.Draw(currentTheme);

            bookingButton.Draw(currentTheme);

            adminButton.Draw(currentTheme);

            settingsButton.Draw(currentTheme);

            exitButton.Draw(currentTheme);
        }

        // =========================
        // AUTH MENU
        // =========================

        if (currentScreen ==
            ScreenState::AuthMenu)
        {
            DrawText(
                "Authentication",
                currentWidth / 2 - 150,
                panelY + 150,
                42,
                currentTheme.accent
            );

            authLoginButton.Draw(currentTheme);

            signUpButton.Draw(currentTheme);

            backButton.Draw(currentTheme);
        }

        // =========================
        // SIGN UP SCREEN
        // =========================

        if (currentScreen ==
            ScreenState::SignUp)
        {
            DrawText(
                "Create Account",
                currentWidth / 2 - 170,
                panelY + 180,
                42,
                currentTheme.accent
            );

            emailBox.Draw("Email");

            passwordBox.Draw("Password");

            confirmPasswordBox.Draw(
                "Verify Password"
            );

            DrawText(
                "Press ENTER to register",
                currentWidth / 2 - 170,
                panelY + 650,
                24,
                currentTheme.text
            );

            backButton.Draw(currentTheme);
        }

        // =========================
        // LOGIN SCREEN
        // =========================

        if (currentScreen ==
            ScreenState::Login)
        {
            DrawText(
                "Login",
                currentWidth / 2 - 70,
                panelY + 180,
                42,
                currentTheme.accent
            );

            emailBox.Draw("Email");

            passwordBox.Draw("Password");

            DrawText(
                "Press ENTER to login",
                currentWidth / 2 - 150,
                panelY + 560,
                24,
                currentTheme.text
            );

            if (loginFailed)
            {
                DrawText(
                    "Invalid email or password",
                    currentWidth / 2 - 190,
                    panelY + 620,
                    24,
                    RED
                );
            }

            backButton.Draw(currentTheme);
        }

        // =========================
        // LOGGED IN SCREEN
        // =========================

        if (currentScreen ==
            ScreenState::LoggedIn)
        {
            DrawText(
                "Successfully Logged In",
                currentWidth / 2 - 260,
                currentHeight / 2 - 40,
                42,
                GREEN
            );

            DrawText(
                loggedInEmail.c_str(),
                currentWidth / 2 - 150,
                currentHeight / 2 + 30,
                30,
                currentTheme.text
            );

            backButton.Draw(currentTheme);

            if (backButton.IsClicked())
            {
                currentScreen =
                    ScreenState::Home;
            }
        }

        // =========================
        // THEME BUTTON
        // =========================

        themeButton.Draw(currentTheme);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}