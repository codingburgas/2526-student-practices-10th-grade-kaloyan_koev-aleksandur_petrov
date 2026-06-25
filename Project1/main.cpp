#include "raylib.h"

#include "Button.h"
#include "Theme.h"
#include "ScreenState.h"
#include "TextBox.h"

#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

struct UserAccount
{
    std::string email;
    std::string password;
    std::string seat;
};

std::vector<UserAccount> LoadUsers()
{
    std::vector<UserAccount> users;

    std::ifstream file("users.txt");

    std::string line;

    while (getline(file, line))
    {
        size_t firstSeparator =
            line.find('|');

        if (firstSeparator == std::string::npos)
        {
            continue;
        }

        size_t secondSeparator =
            line.find('|', firstSeparator + 1);

        UserAccount user;

        user.email =
            line.substr(0, firstSeparator);

        if (secondSeparator == std::string::npos)
        {
            user.password =
                line.substr(firstSeparator + 1);

            user.seat = "";
        }
        else
        {
            user.password =
                line.substr(
                    firstSeparator + 1,
                    secondSeparator - firstSeparator - 1
                );

            user.seat =
                line.substr(secondSeparator + 1);
        }

        users.push_back(user);
    }

    file.close();

    return users;
}

void SaveUsers(const std::vector<UserAccount>& users)
{
    std::ofstream file("users.txt");

    for (const UserAccount& user : users)
    {
        file
            << user.email
            << "|"
            << user.password;

        if (!user.seat.empty())
        {
            file
                << "|"
                << user.seat;
        }

        file << "\n";
    }

    file.close();
}

std::string GetSeatForUser(const std::string& email)
{
    std::vector<UserAccount> users =
        LoadUsers();

    for (const UserAccount& user : users)
    {
        if (user.email == email)
        {
            return user.seat;
        }
    }

    return "";
}

bool IsSeatTakenByAnotherUser(
    const std::string& seat,
    const std::string& loggedInEmail
)
{
    std::vector<UserAccount> users =
        LoadUsers();

    for (const UserAccount& user : users)
    {
        if (user.email == loggedInEmail)
            continue;

        std::stringstream ss(user.seat);
        std::string token;
        while (std::getline(ss, token, ','))
        {
            if (token == seat)
                return true;
        }
    }

    return false;
}

void SaveSeatForUser(
    const std::string& email,
    const std::string& seat
)
{
    std::vector<UserAccount> users =
        LoadUsers();

    for (UserAccount& user : users)
    {
        if (user.email == email)
        {
            user.seat = seat;

            break;
        }
    }

    SaveUsers(users);
}

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

    std::vector<std::string> selectedSeats;

    ScreenState currentScreen =
        ScreenState::Home;

    // =========================
    // PERSISTENT TEXTBOXES
    // =========================

    TextBox emailBox(0, 0, 400, 60);

    TextBox passwordBox(0, 0, 400, 60);

    TextBox confirmPasswordBox(0, 0, 400, 60);

    int activeTextBoxIndex = 0;

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
            panelY + 110,
            buttonWidth,
            buttonHeight,
            loggedInEmail.empty()
            ? "Log in / Sign up"
            : loggedInEmail
        );

        Button bookingButton(
            buttonX,
            panelY + 210,
            buttonWidth,
            buttonHeight,
            "Book Tickets"
        );

        Button homeBookedSeatsButton(
            buttonX,
            panelY + 310,
            buttonWidth,
            buttonHeight,
            "Booked Seats"
        );

        Button adminButton(
            buttonX,
            panelY + 410,
            buttonWidth,
            buttonHeight,
            "Admin Panel"
        );

        Button settingsButton(
            buttonX,
            panelY + 510,
            buttonWidth,
            buttonHeight,
            "Settings"
        );

        Button exitButton(
            buttonX,
            panelY + 610,
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

        Button loginSubmitButton(
            currentWidth / 2 - 150,
            panelY + 500,
            300,
            70,
            "Login"
        );

        Button signUpSubmitButton(
            currentWidth / 2 - 150,
            panelY + 590,
            300,
            70,
            "Create Account"
        );

        Button loggedInBookButton(
            currentWidth / 2 - 150,
            currentHeight / 2 + 100,
            300,
            70,
            "Book Tickets"
        );

        Button viewBookedSeatsButton(
            currentWidth / 2 - 150,
            currentHeight / 2 + 190,
            300,
            70,
            "Booked Seats"
        );

        // =========================
        // VIEW BOOKED SEATS SCREEN
        // =========================

        if (currentScreen ==
            ScreenState::ViewBookedSeats)
        {
            const int vbRows = 6;
            const int vbCols = 10;
            const float vbSize = 56.0f;
            const float vbGap  = 14.0f;

            const float vbGridWidth =
                vbCols * vbSize + (vbCols - 1) * vbGap;

            const float vbStartX =
                currentWidth / 2.0f - vbGridWidth / 2.0f;

            const float vbStartY = panelY + 245.0f;

            std::string savedSeats = GetSeatForUser(loggedInEmail);

            std::vector<std::string> bookedList;
            {
                std::stringstream bss(savedSeats);
                std::string btoken;
                while (std::getline(bss, btoken, ','))
                    if (!btoken.empty()) bookedList.push_back(btoken);
            }

            // Title
            {
                const char* title = "Your Booked Seats";
                int tw = MeasureText(title, 42);
                DrawText(
                    title,
                    currentWidth / 2 - tw / 2,
                    panelY + 70,
                    42,
                    currentTheme.accent
                );
            }

            // Screen bar
            DrawRectangleRounded(
                {
                    currentWidth / 2.0f - 250.0f,
                    panelY + 155.0f,
                    500.0f,
                    28.0f
                },
                0.4f, 12,
                currentTheme.accent
            );
            {
                int sw = MeasureText("SCREEN", 24);
                DrawText(
                    "SCREEN",
                    currentWidth / 2 - sw / 2,
                    panelY + 190,
                    24,
                    currentTheme.text
                );
            }

            // Seat count label
            {
                std::string countLabel =
                    bookedList.empty()
                    ? "No seats booked yet"
                    : "Booked: " + std::to_string(bookedList.size()) + " seat(s)";
                int cw = MeasureText(countLabel.c_str(), 24);
                DrawText(
                    countLabel.c_str(),
                    currentWidth / 2 - cw / 2,
                    (int)(vbStartY - 30),
                    24,
                    currentTheme.text
                );
            }

            // Cinema grid
            for (int row = 0; row < vbRows; row++)
            {
                std::string rowLabel =
                    std::string(1, (char)('A' + row));

                DrawText(
                    rowLabel.c_str(),
                    (int)(vbStartX - 44),
                    (int)(vbStartY + row * (vbSize + vbGap) + 16),
                    24,
                    currentTheme.text
                );

                for (int col = 0; col < vbCols; col++)
                {
                    std::string seat =
                        rowLabel + std::to_string(col + 1);

                    Rectangle seatBounds =
                    {
                        vbStartX + col * (vbSize + vbGap),
                        vbStartY + row * (vbSize + vbGap),
                        vbSize,
                        vbSize
                    };

                    bool isBooked =
                        std::find(
                            bookedList.begin(),
                            bookedList.end(),
                            seat
                        ) != bookedList.end();

                    Color seatColor =
                        isBooked
                        ? Color{40, 170, 95, 255}
                        : currentTheme.button;

                    DrawRectangleRounded(
                        seatBounds, 0.18f, 8, seatColor
                    );

                    int tw = MeasureText(seat.c_str(), 20);
                    DrawText(
                        seat.c_str(),
                        (int)(seatBounds.x + seatBounds.width  / 2 - tw / 2),
                        (int)(seatBounds.y + seatBounds.height / 2 - 10),
                        20,
                        isBooked ? WHITE : currentTheme.text
                    );
                }
            }

            // Legend
            {
                const char* legend =
                    "Green = your booked seat";
                int lw = MeasureText(legend, 20);
                DrawText(
                    legend,
                    currentWidth / 2 - lw / 2,
                    (int)(vbStartY + vbRows * (vbSize + vbGap) + 10),
                    20,
                    currentTheme.text
                );
            }

            backButton.Draw(currentTheme);

            if (backButton.IsClicked())
            {
                currentScreen =
                    ScreenState::LoggedIn;
            }
        }

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

            if (bookingButton.IsClicked())
            {
                if (loggedInEmail.empty())
                {
                    currentScreen =
                        ScreenState::AuthMenu;
                }
                else
                {
                    {
                        selectedSeats.clear();
                        std::string seatStr = GetSeatForUser(loggedInEmail);
                        std::stringstream ss(seatStr);
                        std::string token;
                        while (std::getline(ss, token, ','))
                            if (!token.empty()) selectedSeats.push_back(token);
                    }

                    currentScreen =
                        ScreenState::BookTickets;
                }
            }

            if (homeBookedSeatsButton.IsClicked())
            {
                if (loggedInEmail.empty())
                {
                    currentScreen =
                        ScreenState::AuthMenu;
                }
                else
                {
                    currentScreen =
                        ScreenState::ViewBookedSeats;
                }
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

                emailBox.SetActive(true);

                passwordBox.SetActive(false);

                confirmPasswordBox.SetActive(false);

                activeTextBoxIndex = 0;

                loginFailed = false;

                currentScreen =
                    ScreenState::Login;
            }

            if (signUpButton.IsClicked())
            {
                emailBox.Clear();

                passwordBox.Clear();

                confirmPasswordBox.Clear();

                emailBox.SetActive(true);

                passwordBox.SetActive(false);

                confirmPasswordBox.SetActive(false);

                activeTextBoxIndex = 0;

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

            if (emailBox.IsActive())
            {
                activeTextBoxIndex = 0;
            }
            else if (passwordBox.IsActive())
            {
                activeTextBoxIndex = 1;
            }
            else if (confirmPasswordBox.IsActive())
            {
                activeTextBoxIndex = 2;
            }

            if (IsKeyPressed(KEY_TAB))
            {
                int direction =
                    IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)
                    ? -1
                    : 1;

                activeTextBoxIndex =
                    (activeTextBoxIndex + direction + 3) % 3;

                emailBox.SetActive(activeTextBoxIndex == 0);

                passwordBox.SetActive(activeTextBoxIndex == 1);

                confirmPasswordBox.SetActive(activeTextBoxIndex == 2);
            }

            if (
                IsKeyPressed(KEY_ENTER)
                || signUpSubmitButton.IsClicked()
                )
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
                        << "|"
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

            if (emailBox.IsActive())
            {
                activeTextBoxIndex = 0;
            }
            else if (passwordBox.IsActive())
            {
                activeTextBoxIndex = 1;
            }

            if (IsKeyPressed(KEY_TAB))
            {
                int direction =
                    IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)
                    ? -1
                    : 1;

                activeTextBoxIndex =
                    (activeTextBoxIndex + direction + 2) % 2;

                emailBox.SetActive(activeTextBoxIndex == 0);

                passwordBox.SetActive(activeTextBoxIndex == 1);

                confirmPasswordBox.SetActive(false);
            }

            if (
                IsKeyPressed(KEY_ENTER)
                || loginSubmitButton.IsClicked()
                )
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

                    if (separator == std::string::npos)
                    {
                        continue;
                    }

                    size_t secondSeparator =
                        line.find('|', separator + 1);

                    std::string email =
                        line.substr(
                            0,
                            separator
                        );

                    std::string password =
                        secondSeparator == std::string::npos
                        ? line.substr(separator + 1)
                        : line.substr(
                            separator + 1,
                            secondSeparator - separator - 1
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

                        {
                            selectedSeats.clear();
                            std::string seatStr = GetSeatForUser(loggedInEmail);
                            std::stringstream ss(seatStr);
                            std::string token;
                            while (std::getline(ss, token, ','))
                                if (!token.empty()) selectedSeats.push_back(token);
                        }

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

            homeBookedSeatsButton.Draw(currentTheme);

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

            passwordBox.Draw("Password", true);

            confirmPasswordBox.Draw(
                "Verify Password",
                true
            );

            signUpSubmitButton.Draw(currentTheme);

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

            passwordBox.Draw("Password", true);

            loginSubmitButton.Draw(currentTheme);

            if (loginFailed)
            {
                DrawText(
                    "Invalid email or password",
                    currentWidth / 2 - 190,
                    panelY + 645,
                    24,
                    RED
                );
            }

            backButton.Draw(currentTheme);
        }

        // =========================
        // BOOK TICKETS SCREEN
        // =========================

        if (currentScreen ==
            ScreenState::BookTickets)
        {
            const int rows = 6;

            const int columns = 10;

            const float seatSize = 56.0f;

            const float seatGap = 14.0f;

            const float gridWidth =
                columns * seatSize
                + (columns - 1) * seatGap;

            const float gridStartX =
                currentWidth / 2.0f
                - gridWidth / 2.0f;

            const float gridStartY =
                panelY + 245.0f;

            Vector2 mousePosition =
                GetMousePosition();

            for (int row = 0; row < rows; row++)
            {
                for (int column = 0; column < columns; column++)
                {
                    std::string seat =
                        std::string(1, (char)('A' + row))
                        + std::to_string(column + 1);

                    Rectangle seatBounds =
                    {
                        gridStartX + column * (seatSize + seatGap),
                        gridStartY + row * (seatSize + seatGap),
                        seatSize,
                        seatSize
                    };

                    bool isTaken =
                        IsSeatTakenByAnotherUser(
                            seat,
                            loggedInEmail
                        );

                    if (
                        !isTaken
                        &&
                        CheckCollisionPointRec(
                            mousePosition,
                            seatBounds
                        )
                        &&
                        IsMouseButtonPressed(MOUSE_LEFT_BUTTON)
                        )
                    {
                        auto it = std::find(
                            selectedSeats.begin(),
                            selectedSeats.end(),
                            seat
                        );

                        if (it != selectedSeats.end())
                            selectedSeats.erase(it);
                        else
                            selectedSeats.push_back(seat);
                    }
                }
            }

            if (backButton.IsClicked())
            {
                currentScreen =
                    ScreenState::LoggedIn;
            }
        }

        // =========================
        // LOGGED IN SCREEN
        // =========================

        if (currentScreen ==
            ScreenState::LoggedIn)
        {
            {
                const char* msg = "Successfully Logged In";
                int mw = MeasureText(msg, 42);
                DrawText(
                    msg,
                    currentWidth / 2 - mw / 2,
                    currentHeight / 2 - 40,
                    42,
                    GREEN
                );
            }

            {
                int ew = MeasureText(loggedInEmail.c_str(), 30);
                DrawText(
                    loggedInEmail.c_str(),
                    currentWidth / 2 - ew / 2,
                    currentHeight / 2 + 30,
                    30,
                    currentTheme.text
                );
            }

            backButton.Draw(currentTheme);

            if (backButton.IsClicked())
            {
                currentScreen =
                    ScreenState::Home;
            }

            loggedInBookButton.Draw(currentTheme);

            if (loggedInBookButton.IsClicked())
            {
                {
                    selectedSeats.clear();
                    std::string seatStr = GetSeatForUser(loggedInEmail);
                    std::stringstream ss(seatStr);
                    std::string token;
                    while (std::getline(ss, token, ','))
                        if (!token.empty()) selectedSeats.push_back(token);
                }

                currentScreen =
                    ScreenState::BookTickets;
            }

            viewBookedSeatsButton.Draw(currentTheme);

            if (viewBookedSeatsButton.IsClicked())
            {
                currentScreen =
                    ScreenState::ViewBookedSeats;
            }
        }

        // =========================
        // BOOK TICKETS SCREEN
        // =========================

        if (currentScreen ==
            ScreenState::BookTickets)
        {
            const int rows = 6;

            const int columns = 10;

            const float seatSize = 56.0f;

            const float seatGap = 14.0f;

            const float gridWidth =
                columns * seatSize
                + (columns - 1) * seatGap;

            const float gridStartX =
                currentWidth / 2.0f
                - gridWidth / 2.0f;

            const float gridStartY =
                panelY + 245.0f;

            DrawText(
                "Choose Your Seat",
                currentWidth / 2 - 175,
                panelY + 70,
                42,
                currentTheme.accent
            );

            DrawRectangleRounded(
                {
                    currentWidth / 2.0f - 250.0f,
                    panelY + 155.0f,
                    500.0f,
                    28.0f
                },
                0.4f,
                12,
                currentTheme.accent
            );

            DrawText(
                "SCREEN",
                currentWidth / 2 - 48,
                panelY + 190,
                24,
                currentTheme.text
            );

            Vector2 mousePosition =
                GetMousePosition();

            for (int row = 0; row < rows; row++)
            {
                std::string rowLabel =
                    std::string(1, (char)('A' + row));

                DrawText(
                    rowLabel.c_str(),
                    (int)(gridStartX - 44),
                    (int)(gridStartY + row * (seatSize + seatGap) + 16),
                    24,
                    currentTheme.text
                );

                for (int column = 0; column < columns; column++)
                {
                    std::string seat =
                        rowLabel
                        + std::to_string(column + 1);

                    Rectangle seatBounds =
                    {
                        gridStartX + column * (seatSize + seatGap),
                        gridStartY + row * (seatSize + seatGap),
                        seatSize,
                        seatSize
                    };

                    bool isTaken =
                        IsSeatTakenByAnotherUser(
                            seat,
                            loggedInEmail
                        );

                    bool isSelected =
                        std::find(selectedSeats.begin(), selectedSeats.end(), seat) != selectedSeats.end();

                    bool isHovered =
                        CheckCollisionPointRec(
                            mousePosition,
                            seatBounds
                        );

                    Color seatColor =
                        currentTheme.button;

                    if (isTaken)
                    {
                        seatColor =
                            {120, 55, 55, 255};
                    }
                    else if (isSelected)
                    {
                        seatColor =
                            {40, 170, 95, 255};
                    }
                    else if (isHovered)
                    {
                        seatColor =
                            currentTheme.buttonHover;
                    }

                    DrawRectangleRounded(
                        seatBounds,
                        0.18f,
                        8,
                        seatColor
                    );

                    int textWidth =
                        MeasureText(seat.c_str(), 20);

                    DrawText(
                        seat.c_str(),
                        (int)(seatBounds.x + seatBounds.width / 2 - textWidth / 2),
                        (int)(seatBounds.y + seatBounds.height / 2 - 10),
                        20,
                        currentTheme.text
                    );
                }
            }

            std::string seatMessage;
            if (selectedSeats.empty())
            {
                seatMessage = "No seats selected";
            }
            else
            {
                seatMessage = "Selected: ";
                for (int i = 0; i < (int)selectedSeats.size(); i++)
                {
                    if (i > 0) seatMessage += ", ";
                    seatMessage += selectedSeats[i];
                }
            }

            DrawText(
                seatMessage.c_str(),
                currentWidth / 2 - 300,
                panelY + 700,
                24,
                currentTheme.text
            );

            DrawText(
                "Red = booked  |  Green = your selection  |  Click to toggle",
                currentWidth / 2 - 310,
                panelY + 730,
                20,
                currentTheme.text
            );

            Button confirmButton(
                currentWidth / 2 - 150,
                panelY + 760,
                300,
                60,
                "Confirm Selection"
            );

            confirmButton.Draw(currentTheme);

            if (confirmButton.IsClicked() || IsKeyPressed(KEY_ENTER))
            {
                std::string seatStr = "";
                for (int i = 0; i < (int)selectedSeats.size(); i++)
                {
                    if (i > 0) seatStr += ",";
                    seatStr += selectedSeats[i];
                }

                SaveSeatForUser(loggedInEmail, seatStr);

                currentScreen = ScreenState::Home;
            }

            backButton.Draw(currentTheme);
        }

        // =========================
        // VIEW BOOKED SEATS SCREEN
        // =========================

        if (currentScreen ==
            ScreenState::ViewBookedSeats)
        {
            const int vbRows = 6;
            const int vbCols = 10;
            const float vbSize = 56.0f;
            const float vbGap  = 14.0f;

            const float vbGridWidth =
                vbCols * vbSize + (vbCols - 1) * vbGap;

            const float vbStartX =
                currentWidth / 2.0f - vbGridWidth / 2.0f;

            const float vbStartY = panelY + 245.0f;

            std::string savedSeats = GetSeatForUser(loggedInEmail);

            std::vector<std::string> bookedList;
            {
                std::stringstream bss(savedSeats);
                std::string btoken;
                while (std::getline(bss, btoken, ','))
                    if (!btoken.empty()) bookedList.push_back(btoken);
            }

            // Title
            {
                const char* title = "Your Booked Seats";
                int tw = MeasureText(title, 42);
                DrawText(
                    title,
                    currentWidth / 2 - tw / 2,
                    panelY + 70,
                    42,
                    currentTheme.accent
                );
            }

            // Screen bar
            DrawRectangleRounded(
                {
                    currentWidth / 2.0f - 250.0f,
                    panelY + 155.0f,
                    500.0f,
                    28.0f
                },
                0.4f, 12,
                currentTheme.accent
            );
            {
                int sw = MeasureText("SCREEN", 24);
                DrawText(
                    "SCREEN",
                    currentWidth / 2 - sw / 2,
                    panelY + 190,
                    24,
                    currentTheme.text
                );
            }

            // Seat count label
            {
                std::string countLabel =
                    bookedList.empty()
                    ? "No seats booked yet"
                    : "Booked: " + std::to_string(bookedList.size()) + " seat(s)";
                int cw = MeasureText(countLabel.c_str(), 24);
                DrawText(
                    countLabel.c_str(),
                    currentWidth / 2 - cw / 2,
                    (int)(vbStartY - 30),
                    24,
                    currentTheme.text
                );
            }

            // Cinema grid
            for (int row = 0; row < vbRows; row++)
            {
                std::string rowLabel =
                    std::string(1, (char)('A' + row));

                DrawText(
                    rowLabel.c_str(),
                    (int)(vbStartX - 44),
                    (int)(vbStartY + row * (vbSize + vbGap) + 16),
                    24,
                    currentTheme.text
                );

                for (int col = 0; col < vbCols; col++)
                {
                    std::string seat =
                        rowLabel + std::to_string(col + 1);

                    Rectangle seatBounds =
                    {
                        vbStartX + col * (vbSize + vbGap),
                        vbStartY + row * (vbSize + vbGap),
                        vbSize,
                        vbSize
                    };

                    bool isBooked =
                        std::find(
                            bookedList.begin(),
                            bookedList.end(),
                            seat
                        ) != bookedList.end();

                    Color seatColor =
                        isBooked
                        ? Color{40, 170, 95, 255}
                        : currentTheme.button;

                    DrawRectangleRounded(
                        seatBounds, 0.18f, 8, seatColor
                    );

                    int tw = MeasureText(seat.c_str(), 20);
                    DrawText(
                        seat.c_str(),
                        (int)(seatBounds.x + seatBounds.width  / 2 - tw / 2),
                        (int)(seatBounds.y + seatBounds.height / 2 - 10),
                        20,
                        isBooked ? WHITE : currentTheme.text
                    );
                }
            }

            // Legend
            {
                const char* legend =
                    "Green = your booked seat";
                int lw = MeasureText(legend, 20);
                DrawText(
                    legend,
                    currentWidth / 2 - lw / 2,
                    (int)(vbStartY + vbRows * (vbSize + vbGap) + 10),
                    20,
                    currentTheme.text
                );
            }

            backButton.Draw(currentTheme);

            if (backButton.IsClicked())
            {
                currentScreen =
                    ScreenState::LoggedIn;
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
